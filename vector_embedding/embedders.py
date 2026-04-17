from __future__ import annotations

import time
from abc import ABC, abstractmethod
from dataclasses import dataclass

import numpy as np


@dataclass
class EncodeResult:
    vectors: np.ndarray
    elapsed_s: float


class Embedder(ABC):
    name: str
    dim: int

    @abstractmethod
    def encode(self, texts: list[str], batch_size: int = 32) -> np.ndarray: ...

    def encode_timed(self, texts: list[str], batch_size: int = 32) -> EncodeResult:
        t0 = time.perf_counter()
        vecs = self.encode(texts, batch_size=batch_size)
        return EncodeResult(vectors=vecs, elapsed_s=time.perf_counter() - t0)


class BGEM3Embedder(Embedder):
    name = "bge-m3"
    dim = 1024

    def __init__(self, device: str = "mps", use_fp16: bool = True):
        from FlagEmbedding import BGEM3FlagModel

        fp16 = use_fp16 and device != "cpu"
        self.model = BGEM3FlagModel("BAAI/bge-m3", use_fp16=fp16, device=device)

    def encode(self, texts: list[str], batch_size: int = 32) -> np.ndarray:
        out = self.model.encode(
            texts,
            batch_size=batch_size,
            max_length=512,
            return_dense=True,
            return_sparse=False,
            return_colbert_vecs=False,
        )
        vecs = np.asarray(out["dense_vecs"], dtype=np.float32)
        norms = np.linalg.norm(vecs, axis=1, keepdims=True)
        return vecs / np.clip(norms, 1e-12, None)


class Qwen3Embedder(Embedder):
    name = "qwen3-0.6b"
    dim = 1024

    def __init__(self, device: str = "mps"):
        from sentence_transformers import SentenceTransformer

        self.model = SentenceTransformer("Qwen/Qwen3-Embedding-0.6B", device=device)

    def encode(self, texts: list[str], batch_size: int = 32) -> np.ndarray:
        vecs = self.model.encode(
            texts,
            batch_size=batch_size,
            normalize_embeddings=True,
            convert_to_numpy=True,
            show_progress_bar=False,
        )
        return vecs.astype(np.float32)


def pick_device() -> str:
    import torch

    if torch.backends.mps.is_available():
        return "mps"
    if torch.cuda.is_available():
        return "cuda"
    return "cpu"


def load_all(device: str | None = None) -> list[Embedder]:
    device = device or pick_device()
    return [BGEM3Embedder(device=device), Qwen3Embedder(device=device)]
