from __future__ import annotations

import numpy as np
from tabulate import tabulate

from data.corpus import CORPUS, QUERIES
from embedders import Embedder


def _metrics(doc_vecs: np.ndarray, query_vecs: np.ndarray, relevant: list[list[int]]) -> dict:
    sims = query_vecs @ doc_vecs.T  # (Q, D), both already L2-normalized
    ranking = np.argsort(-sims, axis=1)

    recall_at = {1: 0.0, 5: 0.0, 10: 0.0}
    mrr = 0.0
    n = len(relevant)
    for i, rels in enumerate(relevant):
        ranked = ranking[i].tolist()
        positions = [ranked.index(r) for r in rels if r in ranked]
        if not positions:
            continue
        best = min(positions)
        mrr += 1.0 / (best + 1)
        for k in recall_at:
            if any(p < k for p in positions):
                recall_at[k] += 1.0

    return {
        "mrr": mrr / n,
        "recall@1": recall_at[1] / n,
        "recall@5": recall_at[5] / n,
        "recall@10": recall_at[10] / n,
    }


def run(embedders: list[Embedder]) -> dict:
    rels = [q.relevant_ids for q in QUERIES]
    q_texts = [q.text for q in QUERIES]

    results: dict = {}
    rows = []
    for m in embedders:
        docs = m.encode(CORPUS)
        qs = m.encode(q_texts)
        r = _metrics(docs, qs, rels)
        results[m.name] = r
        rows.append(
            [
                m.name,
                f"{r['mrr']:.3f}",
                f"{r['recall@1']:.3f}",
                f"{r['recall@5']:.3f}",
                f"{r['recall@10']:.3f}",
            ]
        )

    print("\n=== retrieval ===")
    print(
        tabulate(
            rows,
            headers=["model", "MRR", "Recall@1", "Recall@5", "Recall@10"],
            tablefmt="github",
        )
    )
    return results


if __name__ == "__main__":
    from embedders import load_all

    run(load_all())
