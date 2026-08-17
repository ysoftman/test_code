#!/usr/bin/env python3
"""Generate an image with Alpha-VLLM/Lumina-Image-2.0 using Hugging Face Diffusers."""

import argparse
import contextlib
import io
import random
import re
import sys
import textwrap
import time
from datetime import datetime
from pathlib import Path

import torch
from diffusers import Lumina2Pipeline
from PIL import Image
from PIL.PngImagePlugin import PngInfo

DEFAULT_OUTPUT = Path("outputs/lumina2_demo.png")
HISTORY_FILE = Path("outputs/.prompt_history")
DEFAULT_NEGATIVE_PROMPT = (
    ""  # official recommendation for Lumina-Image-2.0 (empty string)
)
C_RESET = "\033[0m"
C_BOLD = "\033[1m"
C_CYAN = "\033[36m"
C_GREEN = "\033[32m"
C_YELLOW = "\033[33m"


def c(text: str, *codes: str) -> str:
    if not sys.stdout.isatty():
        return text
    return "".join(codes) + text + C_RESET


# Lumina-2 was trained on UniCap's long descriptive captions, so the markers are
# written as sentences rather than comma-separated tags.
PROMPT_MARKERS = {
    "realism": (
        "Shot as a raw, unretouched photograph on an 85mm lens at f/1.8. The skin "
        "shows visible pores, fine lines and the soft translucency of subsurface "
        "scattering under gentle natural light, with small imperfections left in."
    ),
    "portrait": (
        "A portrait photograph taken on an 85mm lens at f/1.8, the background "
        "falling away into soft bokeh while the eyes stay sharp. Skin tones are "
        "natural and the light is soft and directional."
    ),
    "cinematic": (
        "A cinematic still shot on 35mm film through an anamorphic lens, with "
        "dramatic directional lighting, muted colour grading, a shallow plane of "
        "focus and fine grain."
    ),
    "landscape": (
        "A wide-angle landscape photograph taken in golden hour light, with a "
        "dramatic sky, rich fine detail across the frame and natural colour held "
        "in both the highlights and the shadows."
    ),
    "product": (
        "A commercial product photograph lit by a large softbox against a clean, "
        "seamless background, every surface detail sharp and evenly exposed."
    ),
    "anime": (
        "An anime illustration with clean line art, vibrant flat colours and "
        "carefully detailed eyes, in the style of a high-quality studio "
        "animation frame."
    ),
    "macro": (
        "A macro photograph taken extremely close to the subject, with a "
        "razor-thin plane of focus, natural light and fine surface texture "
        "filling the frame."
    ),
}

PROMPT_TIPS = (
    "Write in English. UniCap captioned the training data in English and Chinese "
    "only, so Korean conditions the model far more weakly.",
    "Describe the whole scene in sentences, not comma-separated tags. Lumina-2 was "
    "trained on long captions and effectively gains capacity from longer ones.",
    "Say where the light comes from and what it does. Directional light is most of "
    "what separates a photograph from an AI-looking render.",
    "Name specific imperfections - uneven skin, freckles, stray hair, stubble. "
    "Flawless faces are what read as artificial.",
    "Skip {product} for people: its clean advertising look fights the skin texture "
    "{realism} and {portrait} ask for.",
)

BAD_EXAMPLE = (
    "한국 20대 여성, 단발머리, 화장없이, 자연스러운, raw photo, 8k, {realism}{product}"
)

GOOD_EXAMPLE = (
    "A quiet photograph of a Korean woman in her mid-twenties, shoulder-length dark "
    "hair cut in a soft bob and tucked behind one ear, a few strands loose across "
    "her forehead. Her face is bare, no makeup at all, and her skin is slightly "
    "uneven across the cheeks. She looks straight into the lens with a calm, "
    "closed-mouth expression. Cool overcast light from a large window on her right "
    "wraps softly around her face and leaves the left side in gentle shadow. Plain "
    "pale wall behind her, slightly out of focus. {realism}"
)

# Prompt templates from the Lumina-Image-2.0 paper; the pipeline's own default is
# "superior". Pass a preset name or any free-form string to --system-prompt.
SYSTEM_PROMPTS = {
    "aesthetics": (
        "You are an assistant designed to generate high-quality images with "
        "highest degree of aesthetics based on user prompts."
    ),
    "alignment": (
        "You are an assistant designed to generate high-quality images with the "
        "highest degree of image-text alignment based on textual prompts."
    ),
    "superior": (
        "You are an assistant designed to generate superior images with the "
        "superior degree of image-text alignment based on textual prompts or "
        "user prompts."
    ),
}

try:
    import readline

    try:
        readline.read_history_file(HISTORY_FILE)
    except OSError:
        pass
except ImportError:
    readline = None  # no arrow-key history on platforms without readline


def resolve_device(device: str) -> torch.device:
    if device == "cuda":
        return torch.device("cuda")
    if device == "mps":
        return torch.device("mps")
    if device == "cpu":
        return torch.device("cpu")
    if torch.cuda.is_available():
        return torch.device("cuda")
    if torch.backends.mps.is_available():
        return torch.device("mps")
    return torch.device("cpu")


def resolve_dtype(device: torch.device) -> torch.dtype:
    if device.type == "cuda":
        return torch.bfloat16
    if device.type == "mps":
        return torch.float16
    return torch.float32


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate an image with Alpha-VLLM/Lumina-Image-2.0 (Hugging Face Diffusers)",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "--model",
        default="Alpha-VLLM/Lumina-Image-2.0",
        help="Hugging Face repo id or a local model directory (e.g. a snapshot dir)",
    )
    parser.add_argument(
        "--prompt",
        default=(
            "A serene photograph capturing the golden reflection of the sun on a vast expanse of water. "
            "The sun is positioned at the top center, casting a brilliant, shimmering trail of light "
            "across the rippling surface. The water is textured with gentle waves. "
            "Golden hour, photorealistic, peaceful, visually harmonious."
        ),
        help="Text prompt for image generation",
    )
    parser.add_argument(
        "--negative-prompt",
        default=None,
        help="Negative prompt (default: empty string, the official recommendation for Lumina-Image-2.0)",
    )
    parser.add_argument(
        "--system-prompt",
        default="aesthetics",
        help=f"Preset name ({', '.join(SYSTEM_PROMPTS)}) or a free-form system prompt",
    )
    parser.add_argument("--width", type=int, default=1024)
    parser.add_argument("--height", type=int, default=1024)
    parser.add_argument(
        "--steps", type=int, default=50, help="Number of inference steps"
    )
    parser.add_argument("--guidance", type=float, default=4.0, help="Guidance scale")
    parser.add_argument("--cfg-trunc-ratio", type=float, default=0.25)
    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="Seed for reproducibility (default: random)",
    )
    parser.add_argument(
        "-n",
        "--count",
        type=int,
        default=1,
        help="Number of images to generate per prompt (each with a different seed)",
    )
    parser.add_argument(
        "--device", choices=["auto", "cuda", "mps", "cpu"], default="auto"
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=None,
        help="Output image path (default: outputs/<model>_<timestamp>.png)",
    )
    parser.add_argument(
        "--cpu-offload",
        action="store_true",
        help="Offload models to CPU to save VRAM (requires accelerate)",
    )
    parser.add_argument(
        "--offline",
        action="store_true",
        help="Use only the locally cached model files (HF_HUB_OFFLINE=1)",
    )
    parser.add_argument(
        "--timing", action="store_true", help="Print load/generate timing"
    )
    parser.add_argument(
        "-i",
        "--interactive",
        action="store_true",
        help="Keep the pipeline loaded and accept prompts repeatedly from stdin",
    )
    return parser.parse_args()


def timestamp() -> str:
    return datetime.now().strftime("%Y-%m-%d_%H-%M-%S")


def model_short_name(model: str) -> str:
    name = Path(model).name or model
    return re.sub(r"[^A-Za-z0-9]+", "-", name).strip("-").lower()


def expand_prompt(prompt: str) -> str:
    for name, sentences in PROMPT_MARKERS.items():
        prompt = prompt.replace(f"{{{name}}}", f" {sentences} ")
    return re.sub(r"\s+", " ", prompt).strip()


def warn_prompt(prompt: str) -> None:
    if re.search(r"[가-힣]", prompt):
        print(
            c(
                "[warn] Korean text in prompt. Lumina-2 was captioned in English and "
                "Chinese only, so Korean conditions the model far more weakly - "
                "an English prompt gives noticeably better results.",
                C_YELLOW,
            )
        )
    if "{product}" in prompt and ("{realism}" in prompt or "{portrait}" in prompt):
        print(
            c(
                "[warn] {product} asks for a clean advertising shot, which fights the "
                "skin texture {realism}/{portrait} ask for. Drop {product} for people.",
                C_YELLOW,
            )
        )


def resolve_negative_prompt(args: argparse.Namespace) -> str:
    if args.negative_prompt is not None:
        return args.negative_prompt
    return DEFAULT_NEGATIVE_PROMPT


def resolve_system_prompt(args: argparse.Namespace) -> str:
    return SYSTEM_PROMPTS.get(args.system_prompt, args.system_prompt)


def resolve_seed(base_seed: int | None, offset: int) -> int:
    if base_seed is None:
        return random.randint(0, 2**32 - 1)
    return base_seed + offset


def build_metadata(
    args: argparse.Namespace,
    raw_prompt: str,
    expanded_prompt: str,
    seed: int,
    gen_time: float,
    device: torch.device,
    dtype: torch.dtype,
) -> dict[str, str]:
    return {
        "model": args.model,
        "prompt": expanded_prompt,
        "prompt_raw": raw_prompt,
        "negative_prompt": resolve_negative_prompt(args),
        "system_prompt": resolve_system_prompt(args),
        "seed": str(seed),
        "steps": str(args.steps),
        "guidance": str(args.guidance),
        "cfg_trunc_ratio": str(args.cfg_trunc_ratio),
        "width": str(args.width),
        "height": str(args.height),
        "device": str(device),
        "dtype": str(dtype),
        "generated_at": timestamp(),
        "gen_time_s": f"{gen_time:.1f}",
    }


def generate_image(
    pipe: Lumina2Pipeline,
    prompt: str,
    args: argparse.Namespace,
    seed: int,
) -> tuple[Image.Image, float]:
    generator = torch.Generator("cpu").manual_seed(seed)
    with contextlib.redirect_stdout(io.StringIO()):
        t1 = time.perf_counter()
        image = pipe(
            prompt=prompt,
            negative_prompt=resolve_negative_prompt(args),
            system_prompt=resolve_system_prompt(args),
            height=args.height,
            width=args.width,
            guidance_scale=args.guidance,
            num_inference_steps=args.steps,
            cfg_trunc_ratio=args.cfg_trunc_ratio,
            cfg_normalization=True,
            generator=generator,
        ).images[0]
    gen_time = time.perf_counter() - t1
    return image, gen_time


def save_image(
    image: Image.Image,
    output: Path,
    gen_time: float,
    count: int,
    index: int,
    metadata: dict[str, str] | None = None,
) -> None:
    stem = f"{output.stem}_{index:03d}" if count > 1 else output.stem
    output = output.with_name(stem + output.suffix)
    output.parent.mkdir(parents=True, exist_ok=True)
    if metadata:
        pnginfo = PngInfo()
        for key, value in metadata.items():
            pnginfo.add_text(key, value)
        image.save(output, pnginfo=pnginfo)
    else:
        image.save(output)
    print(f"[info] generation took {gen_time:.1f}s -> saved to {output}")


def wrap(text: str, indent: int = 4) -> str:
    pad = " " * indent
    return textwrap.fill(
        text,
        width=78,
        initial_indent=pad,
        subsequent_indent=pad,
        break_on_hyphens=False,
    )


def marker_guide() -> str:
    lines = [
        c("[info] prompt markers (type 'help' to show this again):", C_BOLD, C_CYAN)
    ]
    for name, sentences in PROMPT_MARKERS.items():
        lines.append(f"  {c(f'{{{name}}}', C_BOLD, C_YELLOW)}")
        lines.append(c(wrap(sentences, indent=6), C_GREEN))
    lines.append(
        f"  {c('exit', C_BOLD, C_YELLOW)} or {c('quit', C_BOLD, C_YELLOW)} to stop"
    )
    lines.append("")
    lines.append(c("[info] how to write a prompt:", C_BOLD, C_CYAN))
    for tip in PROMPT_TIPS:
        lines.append(f"  - {wrap(tip, indent=4).lstrip()}")
    lines.append("")
    lines.append(c("[info] bad - comma-separated tags, Korean:", C_BOLD, C_CYAN))
    lines.append(c(wrap(BAD_EXAMPLE), C_YELLOW))
    lines.append(c("[info] good - English, whole scene described:", C_BOLD, C_CYAN))
    lines.append(c(wrap(GOOD_EXAMPLE), C_GREEN))
    return "\n".join(lines)


def run_interactive(
    pipe: Lumina2Pipeline,
    args: argparse.Namespace,
    device: torch.device,
    dtype: torch.dtype,
) -> None:
    print(
        "[info] interactive mode - type a prompt and press Enter. "
        "empty line, 'exit' or 'quit' to stop."
    )
    print(marker_guide())
    counter = 0
    try:
        while True:
            try:
                prompt = input("prompt> ").strip()
            except EOFError:
                break
            if prompt.lower() == "help":
                print(marker_guide())
                continue
            if not prompt or prompt.lower() in ("exit", "quit", "q"):
                break
            warn_prompt(prompt)
            for i in range(args.count):
                seed = resolve_seed(args.seed, counter * args.count + i)
                print(f"[info] seed={seed}")
                expanded_prompt = expand_prompt(prompt)
                image, gen_time = generate_image(pipe, expanded_prompt, args, seed)
                base = args.output or DEFAULT_OUTPUT
                output = base.parent / (
                    f"{model_short_name(args.model)}_{timestamp()}_{counter:03d}"
                    f"{base.suffix}"
                )
                metadata = build_metadata(
                    args, prompt, expanded_prompt, seed, gen_time, device, dtype
                )
                save_image(image, output, gen_time, args.count, i, metadata)
            counter += 1
    except KeyboardInterrupt:
        print("\n[info] interrupted")
    if readline is not None:
        HISTORY_FILE.parent.mkdir(parents=True, exist_ok=True)
        readline.write_history_file(HISTORY_FILE)
    print("[info] bye")


def main() -> None:
    args = parse_args()

    device = resolve_device(args.device)
    dtype = resolve_dtype(device)
    print(f"[info] device={device} dtype={dtype} model={args.model}")

    if args.width % 8 != 0 or args.height % 8 != 0:
        raise SystemExit(
            "[error] width/height must be a multiple of 8 (VAE downscale factor)"
        )
    if args.count < 1:
        raise SystemExit("[error] --count must be >= 1")

    if args.offline:
        import os

        os.environ["HF_HUB_OFFLINE"] = "1"

    t0 = time.perf_counter()
    pipe = Lumina2Pipeline.from_pretrained(args.model, torch_dtype=dtype)
    load_time = time.perf_counter() - t0
    print(f"[info] loaded pipeline in {load_time:.1f}s")
    print(f"[info] components: {list(pipe.components.keys())}")

    if args.cpu_offload:
        pipe.enable_model_cpu_offload()
    else:
        pipe.to(device)

    if args.interactive:
        run_interactive(pipe, args, device, dtype)
        return

    warn_prompt(args.prompt)
    total_gen = 0.0
    for i in range(args.count):
        seed = resolve_seed(args.seed, i)
        print(f"[info] seed={seed}")
        expanded_prompt = expand_prompt(args.prompt)
        image, gen_time = generate_image(pipe, expanded_prompt, args, seed)
        output = args.output or Path("outputs") / (
            f"{model_short_name(args.model)}_{timestamp()}.png"
        )
        metadata = build_metadata(
            args, args.prompt, expanded_prompt, seed, gen_time, device, dtype
        )
        save_image(image, output, gen_time, args.count, i, metadata)
        total_gen += gen_time
    print(f"[info] total generation took {total_gen:.1f}s for {args.count} image(s)")
    if args.timing:
        print(
            f"[timing] load={load_time:.1f}s generate={total_gen:.1f}s "
            f"total={load_time + total_gen:.1f}s"
        )


if __name__ == "__main__":
    main()
