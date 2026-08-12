# Diffusers (Hugging Face) - Lumina-Image-2.0 예시

[Alpha-VLLM/Lumina-Image-2.0](https://huggingface.co/Alpha-VLLM/Lumina-Image-2.0) 모델을
[Hugging Face Diffusers](https://github.com/huggingface/diffusers) 파이프라인으로 로딩하고
텍스트 프롬프트로 이미지를 생성하는 예시입니다.

## Hugging Face Diffusers 란?

Diffusers 는 Hugging Face(허깅페이스) 팀이 만든, 파이토치(PyTorch) 기반의
**이미지/오디오/비디오 생성 모델을 손쉽게 사용하기 위한 오픈소스 라이브러리**입니다.

- Diffusion model(확산 모델)들 — Stable Diffusion, Flux, SDXL, Lumina 등 — 을
  통일된 API 로 다루며, 학습/추론 파이프라인을 공통 인터페이스로 제공합니다.
- `AutoPipeline` / `Pipeline.from_pretrained()` 같은 API 로 허깅페이스 Hub에 있는
  수십만 개의 사전학습(pre-trained) 모델을 몇 줄만으로 로딩할 수 있습니다.
- 주요 구성 요소:
  - **Pipeline**: `StableDiffusionPipeline`, `Lumina2Pipeline` 등 모델별로 조립된
    고수준 인터페이스 (text encodger → transformer → VAE decoding 을 한 번에 실행)
  - **Scheduler**: 노이즈 제거(denoising) 스케줄러 (`FlowMatchEulerDiscreteScheduler` 등)
  - **Components**: 각 구성 요소(text_encoder, tokenizer, transformer/vae)를 개별 로딩 가능
- 텍스트-투-이미지(text-to-image), 이미지-투-이미지(img2img), inpainting 등의
  태스크를 `pipeline(...)` 호출 한 번으로 수행합니다.

이 프로젝트에서 사용하는 `Lumina2Pipeline` 은 Alpha-VLLM 의
Lumina-Image-2.0 문서 참고: [arXiv](https://arxiv.org/abs/2503.21758),
[GitHub](https://github.com/Alpha-VLLM/Lumina-Image-2.0)

## 모델 정보

| 항목 | 값 |
| --- | --- |
| 모델 | Alpha-VLLM/Lumina-Image-2.0 |
| 종류 | Flow 기반 Diffusion Transformer (약 2B 파라미터) |
| 라이선스 | Apache-2.0 |
| 파이프라인 | `Lumina2Pipeline` (diffusers 0.33+) |
| 컴포넌트 | `Gemma2Model` (text encoder) + `Lumina2Transformer2DModel` + `AutoencoderKL` + `FlowMatchEulerDiscreteScheduler` |

## 프로젝트 구조

```text
diffuers/
├── generate_image.py   # 모델 로딩 + 이미지 생성 예시 스크립트
├── outputs/            # 생성된 이미지 저장 위치
└── README.md
```

## 환경 구성

Python 3.12 + [uv](https://docs.astral.sh/uv/) 기준입니다.

```bash
cd diffuers

# 1) pyproject.toml 기준으로 가상환경 생성 + 의존성 설치 (한 번에)
uv sync
# (수동으로 할 경우: uv venv --python 3.12 && uv pip install --python .venv/bin/python \
#   torch diffusers transformers accelerate sentencepiece)
```

## 모델 다운로드 (선택)

모델을 미리 내려받으려면 Hugging Face CLI(`hf`)를 사용합니다.
(이미 `hf download` 로 받았다면 별도 다운로드 없이 해당 캐시를 사용합니다)

```bash
# Hugging Face CLI 설치
uv tool install "huggingface_hub[cli]"

# 모델 다운로드 (공개 모델이라 로그인 불필요, 기본 캐시 경로에 저장)
hf download Alpha-VLLM/Lumina-Image-2.0

# 기본 캐시 경로: ~/.cache/huggingface/hub/models--Alpha-VLLM--Lumina-Image-2.0/
```

## 실행 방법

### 전체 스텝으로 이미지 생성 (기본)

```bash
# 로컬 캐시만 사용(오프라인) + 기본 파라미터(1024x1024, 50 스텝)
.venv/bin/python generate_image.py --offline

# 결과: outputs/lumina2_demo.png
```

### 옵션 지정 예시

```bash
.venv/bin/python generate_image.py \
  --prompt "a cute corgi puppy sitting on a grassy hill, blue sky, high quality" \
  --width 1024 --height 1024 \
  --steps 50 \
  --guidance 4.0 \
  --seed 42 \
  --device mps \
  --offline \
  --timing
```

### 스모크 테스트 (빠른 검증)

```bash
# 3 스텝, 256x256 으로 로딩/생성 동작만 빠르게 확인
.venv/bin/python generate_image.py --offline --steps 3 --width 256 --height 256 --output outputs/smoke.png
```

### 로컬 디렉토리에서 직접 로딩

캐시가 아닌 특정 디렉토리를 지정하고 싶으면 snapshot 경로를 넘깁니다.

```bash
.venv/bin/python generate_image.py --model ~/.cache/huggingface/hub/models--Alpha-VLLM--Lumina-Image-2.0/snapshots/<HASH>
```

## 파라미터 설명

| 파라미터 | 기본값 | 설명 |
| --- | --- | --- |
| `--model` | `Alpha-VLLM/Lumina-Image-2.0` | Hub repo id 또는 로컬 모델 경로 |
| `--prompt` | 샘플 프롬프트 | 생성할 이미지 설명 (영어 권장) |
| `--negative-prompt` | 없음 | 이미지에 포함하지 않을 내용 (선택) |
| `--width` / `--height` | `1024` / `1024` | 생성 이미지 크기 (**8의 배수 필수**, VAE 다운샘플 배수) |
| `--steps` | `50` | 노이즈 제거 스텝 수 (클수록 품질↑, 시간↑) |
| `--guidance` | `4.0` | 가이던스 스케일 (클수록 프롬프트 충실도↑) |
| `--cfg-trunc-ratio` | `0.25` | Lumina2 의 CFG 절단 비율 |
| `--seed` | `0` | 재현용 시드 |
| `--device` | `auto` | `cuda` / `mps` / `cpu` 자동 선택 |
| `--cpu-offload` | off | VRAM 부족 시 CPU 오프로드 (accelerate 필요) |
| `--offline` | off | 로컬 캐시만 사용 (네트워크 차단) |
| `--timing` | off | 로딩/생성 소요 시간 출력 |

## 참고 사항

- **dtype**: 자동으로 `cuda -> bfloat16`, `mps(Mac)-> float16`, `cpu -> float32` 로 설정합니다.
  (Mac MPS 는 bfloat16 미지원 이슈가 있어 float16 사용)
- **메모리**: 전체 모델 약 2B 파라미터. 16GB RAM/VRAM 부족 시 `--cpu-offload` 를 사용하세요.
  Mac(Apple Silicon, MPS)의 경우 통합 메모리 32GB 이상에서 권장 파라미터로 동작합니다.
- **오프라인**: `--offline` 옵션은 `HF_HUB_OFFLINE=1` 환경변수를 설정하며,
  Hub 접근 없이 `~/.cache/huggingface/hub/` 캐시에서만 로딩합니다.
- **문서**: Diffusers 공식 문서 <https://huggingface.co/docs/diffusers>

## Mac (Apple Silicon / M1 Max) 성능 가이드

**측정 환경**: MacBook Pro M1 Max (32GB 통합 메모리, Metal/MPS), torch 2.13

| 설정 | 1024x1024 기준 |
| --- | --- |
| 로딩 (캐시, fp16) | 약 30초 |
| 생성 속도 | 약 15초/스텝 (50스텝 ≈ 12분, 30스텝 ≈ 8분) |
| 768x768 + 30스텝 | 약 4분 |

## 이미 최적인 것들

- **MPS + float16**: macOS 에서 가장 빠른 조합 (bf16 미지원, CPU 는 더 느림)
- **메모리**: 모델이 fp16 기준 ~5GB 라 32GB 통합 메모리면 CPU 오프로드 불필요
  (`--cpu-offload` 는 오히려 느림)
- **해상도**: 1024x1024 까지 메모리 부담 없음

## 속도 최적화 팁 (품질과 시간 트레이드오프)

- `--steps 50 -> 30` 으로 줄이면 시간 절반, 품질 저하 미미
  (품질 최우선이면 공식 데모 기준 50 스텝 권장)
- `--width/height 1024 -> 768` 로 줄이면 픽셀 수 비례 단축
- CUDA GPU 대비 M1 Max 는 느리므로, 그 외 추가 최적화 여지(flash-attention,
  `torch.compile`)는 MPS 에서 지원되지 않음
