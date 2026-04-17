from __future__ import annotations

import time

from tabulate import tabulate

from data.corpus import CORPUS
from embedders import Embedder


def run(embedders: list[Embedder], n_warmup: int = 2, n_repeat: int = 3) -> dict:
    single = ["대한민국의 수도는 서울이다."]
    batch = CORPUS * 4  # ~88 sentences

    results: dict = {}
    rows = []

    for m in embedders:
        # warmup
        for _ in range(n_warmup):
            m.encode(single)

        # single-sentence latency
        lat_ms: list[float] = []
        for _ in range(n_repeat):
            t0 = time.perf_counter()
            m.encode(single)
            lat_ms.append((time.perf_counter() - t0) * 1000)
        single_ms = sum(lat_ms) / len(lat_ms)

        # batch throughput
        throughputs: list[float] = []
        for _ in range(n_repeat):
            t0 = time.perf_counter()
            m.encode(batch, batch_size=32)
            elapsed = time.perf_counter() - t0
            throughputs.append(len(batch) / elapsed)
        qps = sum(throughputs) / len(throughputs)

        results[m.name] = {"single_ms": single_ms, "batch_qps": qps, "batch_size": len(batch)}
        rows.append([m.name, f"{single_ms:.1f}", f"{qps:.1f}", len(batch)])

    print("\n=== speed ===")
    print(
        tabulate(
            rows,
            headers=["model", "single latency (ms)", "batch throughput (sent/s)", "batch_size"],
            tablefmt="github",
        )
    )
    return results


if __name__ == "__main__":
    from embedders import load_all

    run(load_all())
