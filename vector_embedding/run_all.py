"""Run all benchmarks end-to-end.

Usage:
    uv run python run_all.py
    # or
    python run_all.py
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from benchmarks import memory as mem_bench
from benchmarks import retrieval, similarity, speed
from embedders import load_all, pick_device


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--device", default=None, help="mps | cpu | cuda (auto if omitted)")
    parser.add_argument("--skip-memory", action="store_true")
    parser.add_argument("--out", default="results/report.json")
    args = parser.parse_args()

    device = args.device or pick_device()
    print(f"device: {device}")

    embedders = load_all(device=device)
    report: dict = {"device": device}

    report["similarity"] = similarity.run(embedders)
    report["retrieval"] = retrieval.run(embedders)
    report["speed"] = speed.run(embedders)

    # memory needs a fresh process-local load per model, so run last.
    if not args.skip_memory:
        del embedders
        report["memory"] = mem_bench.run()

    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(json.dumps(report, ensure_ascii=False, indent=2))
    print(f"\nsaved: {out_path}")


if __name__ == "__main__":
    main()
