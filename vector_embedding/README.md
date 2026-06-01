# Korean Embedding Benchmark: bge-m3 vs qwen3-embedding-0.6b

한국어 중심 문장 임베딩 모델 비교 벤치마크. Mac M1 (MPS) 환경에서 품질 / 속도 / 메모리 / 검색 성능을 측정한다.

## 비교 대상

| 모델                          | 차원   | 용도                  |
|-------------------------------|-------|------------------------|
| `BAAI/bge-m3`                 | 1024 | 다국어 dense embedding |
| `Qwen/Qwen3-Embedding-0.6B`   | 1024 | 다국어 dense embedding |

## 프로젝트 구조

```text
vector_embedding/
├── pyproject.toml
├── embedders.py              # Embedder 추상 클래스 + 두 모델 구현, MPS 자동 선택
├── data/
│   ├── pairs.py              # 라벨링된 한국어 문장쌍 (패러프레이즈/교차언어/관련/무관)
│   └── corpus.py             # 검색 벤치마크용 코퍼스 + 쿼리
├── benchmarks/
│   ├── similarity.py         # 코사인 유사도 + Spearman 상관계수
│   ├── speed.py              # 단건 latency + 배치 throughput
│   ├── memory.py             # 모델별 RSS delta (psutil)
│   └── retrieval.py          # MRR, Recall@1/5/10
├── run_all.py                # 전체 실행 + results/report.json 저장
└── results/                  # 실행 결과 (gitignore)
```

## 요구 사항

- Python 3.10+
- [uv](https://docs.astral.sh/uv/) (권장)
- Mac M1/M2/M3 (MPS) / Linux CUDA / CPU 모두 지원 (자동 감지)

## 설치

```bash
uv sync
```

`uv sync`는 `pyproject.toml` + `uv.lock` 을 기준으로 `.venv`를 만들고 의존성을 설치한다.

## 패키지 업그레이드

```bash
# 1. 업그레이드 가능한(outdated) 패키지 목록 확인
uv pip list --outdated

# 2. pyproject.toml 제약 범위 내에서 모든 패키지를 최신으로 lock 갱신
uv lock --upgrade

# 3. 갱신된 lock 대로 .venv 동기화
uv sync
```

- 특정 패키지만 갱신: `uv lock --upgrade-package <name>`
- 버전 제약 자체를 올리려면 `uv add "<name>>=<ver>"` (또는 `pyproject.toml` 편집 후 `uv lock && uv sync`)

## 실행

### 전체 벤치마크

```bash
uv run python run_all.py
```

옵션:

- `--device cpu | mps | cuda` — 디바이스 강제 지정 (기본: 자동)
- `--skip-memory` — 메모리 측정 건너뛰기
- `--out results/report.json` — 결과 JSON 저장 경로

### 개별 벤치마크

```bash
uv run python -m benchmarks.similarity
uv run python -m benchmarks.retrieval
uv run python -m benchmarks.speed
uv run python -m benchmarks.memory
```

## 평가 지표

| 범주    | 지표                                                    |
|---------|--------------------------------------------------------|
| 품질    | Spearman(예측 유사도, 사람 라벨), 평균 절대 오차         |
| 검색    | MRR, Recall@1/5/10                                     |
| 속도    | 단건 latency(ms), 배치 throughput(sentences/sec)        |
| 메모리  | 모델 로드 후 RSS, 추론 중 피크 RSS                       |

### MRR (Mean Reciprocal Rank)

검색 결과에서 정답 문서의 순위 역수의 평균.

- 1.0 = 항상 1위로 검색됨
- 0.5 = 평균 2위
- 0.0 = 정답을 못 찾음

## 결과 예시 (Mac M1, MPS)

### 유사도 품질 (한국어 라벨 25쌍)

| model      | Spearman | mean_abs_err |
|------------|----------|--------------|
| bge-m3     | 0.809    | 0.197        |
| qwen3-0.6b | 0.596    | 0.252        |

### 속도

| model      | single (ms) | batch (sent/s) |
|------------|-------------|----------------|
| bge-m3     | 31.6        | 209.6          |
| qwen3-0.6b | 31.8        | 108.4          |

### 메모리 (RSS delta, MB)

| model      | load | peak  |
|------------|------|-------|
| bge-m3     | 278  | 1172  |
| qwen3-0.6b | 505  | 531   |

### 검색 성능

22개 문서, 18개 쿼리 기준 두 모델 모두 MRR/Recall 1.0 → 코퍼스가 작고 쉬움. 더 큰 코퍼스에서 재측정 필요.

## 관찰된 특징

- **한국어 패러프레이즈 / 교차언어 (한↔영)**: bge-m3가 일관되게 높은 유사도를 부여한다.
- **부정문 처리**: 두 모델 모두 약점. "좋아한다" vs "좋아하지 않는다"를 유사하다고 판단하는 경향이 있다.
- **메모리 특성**: qwen3-0.6b는 파라미터가 많아 로드 시 RSS가 크지만, 추론 중 증가폭은 bge-m3보다 훨씬 작다.

## 라이선스

테스트 / 학습용 프로젝트.
