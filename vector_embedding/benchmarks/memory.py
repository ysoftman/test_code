from __future__ import annotations

import gc
import os

import psutil
from tabulate import tabulate

from data.corpus import CORPUS


def _rss_mb() -> float:
    return psutil.Process(os.getpid()).memory_info().rss / (1024 * 1024)


def run() -> dict:
    """Measure per-model RSS delta. Loads each model in isolation."""
    from embedders import BGEM3Embedder, Qwen3Embedder, pick_device

    device = pick_device()
    results: dict = {}
    rows = []

    for name, cls in [("bge-m3", BGEM3Embedder), ("qwen3-0.6b", Qwen3Embedder)]:
        gc.collect()
        base = _rss_mb()
        model = cls(device=device)
        after_load = _rss_mb()
        model.encode(CORPUS, batch_size=16)
        after_infer = _rss_mb()

        results[name] = {
            "load_mb": after_load - base,
            "peak_mb": after_infer - base,
        }
        rows.append([name, f"{after_load - base:.0f}", f"{after_infer - base:.0f}"])

        del model
        gc.collect()

    print("\n=== memory (RSS delta, MB) ===")
    print(tabulate(rows, headers=["model", "after load", "after inference"], tablefmt="github"))
    return results


if __name__ == "__main__":
    run()
