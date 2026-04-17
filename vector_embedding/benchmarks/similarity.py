from __future__ import annotations

import numpy as np
from scipy.stats import spearmanr
from tabulate import tabulate

from data.pairs import PAIRS
from embedders import Embedder


def cosine(a: np.ndarray, b: np.ndarray) -> np.ndarray:
    return np.sum(a * b, axis=1)


def run(embedders: list[Embedder]) -> dict:
    texts_a = [p.a for p in PAIRS]
    texts_b = [p.b for p in PAIRS]
    labels = np.array([p.label for p in PAIRS])

    results: dict = {"per_pair": [], "per_model": {}}

    model_sims: dict[str, np.ndarray] = {}
    for m in embedders:
        va = m.encode(texts_a)
        vb = m.encode(texts_b)
        sims = cosine(va, vb)
        model_sims[m.name] = sims
        rho, _ = spearmanr(sims, labels)
        results["per_model"][m.name] = {
            "spearman": float(rho),
            "mean_abs_err": float(np.mean(np.abs(sims - labels))),
        }

    # per-pair table
    rows = []
    for i, p in enumerate(PAIRS):
        row = [p.tag, p.label, f"{p.a[:30]}…" if len(p.a) > 30 else p.a]
        for m in embedders:
            row.append(f"{model_sims[m.name][i]:.3f}")
        rows.append(row)
        results["per_pair"].append(
            {
                "tag": p.tag,
                "label": p.label,
                "a": p.a,
                "b": p.b,
                **{m.name: float(model_sims[m.name][i]) for m in embedders},
            }
        )

    headers = ["tag", "label", "sentence_a"] + [m.name for m in embedders]
    print("\n=== similarity per pair ===")
    print(tabulate(rows, headers=headers, tablefmt="github"))

    print("\n=== similarity summary ===")
    summary_rows = []
    for m in embedders:
        r = results["per_model"][m.name]
        summary_rows.append([m.name, f"{r['spearman']:.3f}", f"{r['mean_abs_err']:.3f}"])
    print(
        tabulate(
            summary_rows,
            headers=["model", "spearman(sim, label)", "mean_abs_err"],
            tablefmt="github",
        )
    )
    return results


if __name__ == "__main__":
    from embedders import load_all

    run(load_all())
