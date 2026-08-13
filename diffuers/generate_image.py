#!/usr/bin/env python3
"""Generate an image with Alpha-VLLM/Lumina-Image-2.0 using Hugging Face Diffusers."""

import argparse
import contextlib
import io
import re
import sys
import time
from datetime import datetime
from pathlib import Path

import torch
from diffusers import Lumina2Pipeline
from PIL import Image

DEFAULT_OUTPUT = Path("outputs/lumina2_demo.png")
HISTORY_FILE = Path("outputs/.prompt_history")
C_RESET = "\033[0m"
C_BOLD = "\033[1m"
C_CYAN = "\033[36m"
C_GREEN = "\033[32m"
C_YELLOW = "\033[33m"


def c(text: str, *codes: str) -> str:
    if not sys.stdout.isatty():
        return text
    return "".join(codes) + text + C_RESET


PROMPT_MARKERS = {
    "realism": (
        "raw photo, realistic skin pores, fine wrinkles, subsurface scattering, "
        "natural soft lighting, shot on 85mm lens, f/1.8, subtle imperfections, "
        "8k resolution"
    ),
    "portrait": (
        "professional portrait photography, 85mm lens, f/1.8, shallow depth of "
        "field, soft bokeh background, sharp focus on eyes, natural skin tones, "
        "studio lighting"
    ),
    "cinematic": (
        "cinematic still, film grain, anamorphic lens, dramatic lighting, "
        "cinematic color grading, moody atmosphere, shallow depth of field, "
        "35mm film"
    ),
    "landscape": (
        "wide angle landscape photography, golden hour, dramatic sky, rich "
        "detail, natural colors, high dynamic range, professional photography"
    ),
    "product": (
        "commercial product photography, studio lighting, softbox, high detail, "
        "clean background, professional advertising shot, sharp focus"
    ),
    "anime": (
        "anime illustration style, clean line art, vibrant colors, detailed "
        "eyes, studio quality animation, high quality anime artwork"
    ),
    "macro": (
        "macro photography, extreme close-up, shallow depth of field, fine "
        "detail, natural light, sharp focus on subject"
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
        help="Negative prompt (things to avoid in the image)",
    )
    parser.add_argument("--width", type=int, default=1024)
    parser.add_argument("--height", type=int, default=1024)
    parser.add_argument(
        "--steps", type=int, default=50, help="Number of inference steps"
    )
    parser.add_argument("--guidance", type=float, default=4.0, help="Guidance scale")
    parser.add_argument("--cfg-trunc-ratio", type=float, default=0.25)
    parser.add_argument("--seed", type=int, default=0)
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
    for name, keywords in PROMPT_MARKERS.items():
        prompt = prompt.replace(f"{{{name}}}", keywords)
    return prompt


def generate_image(
    pipe: Lumina2Pipeline,
    prompt: str,
    args: argparse.Namespace,
    seed: int,
) -> tuple[Image.Image, float]:
    prompt = expand_prompt(prompt)
    generator = torch.Generator("cpu").manual_seed(seed)
    with contextlib.redirect_stdout(io.StringIO()):
        t1 = time.perf_counter()
        image = pipe(
            prompt=prompt,
            negative_prompt=args.negative_prompt,
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
) -> None:
    stem = f"{output.stem}_{index:03d}" if count > 1 else output.stem
    output = output.with_name(stem + output.suffix)
    output.parent.mkdir(parents=True, exist_ok=True)
    image.save(output)
    print(f"[info] generation took {gen_time:.1f}s -> saved to {output}")


def marker_guide() -> str:
    lines = [
        c("[info] prompt markers (type 'help' to show this again):", C_BOLD, C_CYAN)
    ]
    for name, keywords in PROMPT_MARKERS.items():
        marker = c(f"{{{name}}}", C_BOLD, C_YELLOW)
        lines.append(f"  {marker} -> {c(keywords, C_GREEN)}")
    lines.append(
        f"  {c('exit', C_BOLD, C_YELLOW)} or {c('quit', C_BOLD, C_YELLOW)} to stop"
    )
    return "\n".join(lines)


def run_interactive(pipe: Lumina2Pipeline, args: argparse.Namespace) -> None:
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
            for i in range(args.count):
                image, gen_time = generate_image(
                    pipe,
                    prompt,
                    args,
                    args.seed + counter * args.count + i,
                )
                base = args.output or DEFAULT_OUTPUT
                output = base.parent / (
                    f"{model_short_name(args.model)}_{timestamp()}_{counter:03d}"
                    f"{base.suffix}"
                )
                save_image(image, output, gen_time, args.count, i)
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
        run_interactive(pipe, args)
        return

    total_gen = 0.0
    for i in range(args.count):
        image, gen_time = generate_image(pipe, args.prompt, args, args.seed + i)
        output = args.output or Path("outputs") / (
            f"{model_short_name(args.model)}_{timestamp()}.png"
        )
        save_image(image, output, gen_time, args.count, i)
        total_gen += gen_time
    print(f"[info] total generation took {total_gen:.1f}s for {args.count} image(s)")
    if args.timing:
        print(
            f"[timing] load={load_time:.1f}s generate={total_gen:.1f}s "
            f"total={load_time + total_gen:.1f}s"
        )


if __name__ == "__main__":
    main()
