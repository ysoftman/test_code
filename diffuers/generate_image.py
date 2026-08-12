#!/usr/bin/env python3
"""Generate an image with Alpha-VLLM/Lumina-Image-2.0 using Hugging Face Diffusers."""

import argparse
import contextlib
import io
import time
from pathlib import Path

import torch
from diffusers import Lumina2Pipeline


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
        "--device", choices=["auto", "cuda", "mps", "cpu"], default="auto"
    )
    parser.add_argument("--output", type=Path, default=Path("outputs/lumina2_demo.png"))
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
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    device = resolve_device(args.device)
    dtype = resolve_dtype(device)
    print(f"[info] device={device} dtype={dtype} model={args.model}")

    if args.width % 8 != 0 or args.height % 8 != 0:
        raise SystemExit(
            "[error] width/height must be a multiple of 8 (VAE downscale factor)"
        )

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

    generator = torch.Generator("cpu").manual_seed(args.seed)
    with contextlib.redirect_stdout(io.StringIO()):
        t1 = time.perf_counter()
        image = pipe(
            prompt=args.prompt,
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

    args.output.parent.mkdir(parents=True, exist_ok=True)
    image.save(args.output)
    print(f"[info] generation took {gen_time:.1f}s -> saved to {args.output}")
    if args.timing:
        print(
            f"[timing] load={load_time:.1f}s generate={gen_time:.1f}s total={load_time + gen_time:.1f}s"
        )


if __name__ == "__main__":
    main()
