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

# 결과: outputs/lumina-image-2-0_2026-08-13_00-09-41.png (모델명_생성시각 YYYY-MM-DD_hh-mm-ss)
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

### 여러 장 생성 (프롬프트당 N개)

`-n`(또는 `--count`) 옵션으로 프롬프트 하나당 여러 장을 생성할 수 있습니다.
`--seed` 지정 시 이미지마다 시드가 자동으로 증가하며(42, 43, 44 ...), 미지정 시
매번 랜덤 시드를 사용합니다. 파일명에 `_000`, `_001` ... 인덱스가 붙습니다.

```bash
# 프롬프트 하나로 3장 생성 (시드 42, 43, 44)
.venv/bin/python generate_image.py \
  --prompt "a cute corgi puppy sitting on a grassy hill" \
  -n 3 \
  --seed 42 \
  --offline

# 결과: outputs/lumina-image-2-0_2026-08-13_00-10-51_000.png
#       outputs/lumina-image-2-0_2026-08-13_00-10-51_001.png
#       outputs/lumina-image-2-0_2026-08-13_00-10-51_002.png
```

```bash
# 시드 미지정: 매번 다른 이미지 (사용된 시드는 로그로 출력)
.venv/bin/python generate_image.py --prompt "a cute corgi puppy" --offline
# [info] seed=1234567890
```

인터랙티브 모드에서도 프롬프트마다 N장씩 생성합니다:

```bash
.venv/bin/python generate_image.py --offline -i -n 3
# prompt> a cute cat on a sofa  -> 3장 생성
```

### 인터랙티브 모드 (모델 1회 로드 + 프롬프트 반복 입력)

스크립트 실행 시마다 모델을 다시 로딩하는 비용(약 30초)을 없애고 싶다면
`-i`(또는 `--interactive`) 옵션으로 모델을 한 번만 로드한 뒤 프롬프트를
계속 입력받을 수 있습니다. 시드는 `--seed` 지정 시 매 프롬프트마다 자동으로 증가하고,
미지정 시 매번 랜덤 시드를 사용합니다.
출력은 `outputs/모델명_YYYY-MM-DD_hh-mm-ss_카운터.png`
(예: `lumina-image-2-0_2026-08-13_00-10-51_000.png`) 로 저장됩니다.

프롬프트 입력에는 readline 이 활성화되어 **화살표 위/아래로 이전 프롬프트
기록을 불러올 수** 있으며, 히스토리는 `outputs/.prompt_history` 에 저장되어
다음 실행에서도 유지됩니다 (gitignore 대상).

실행 시 사용 가능한 프롬프트 마커(`{realism}` 등)와 종료 방법 안내가
컬러로 표시되며, `help` 를 입력하면 언제든 다시 볼 수 있습니다.
(파이프/리다이렉트 사용 시에는 색상이 제거됩니다)

```bash
.venv/bin/python generate_image.py --offline -i

# [info] prompt markers (type 'help' to show this again):
#   {realism} -> raw photo, realistic skin pores, ...
#   exit or quit to stop
# prompt> a cute cat on a sofa, {realism}
# prompt> help  -> 마커/종료 안내 다시 표시
# prompt> exit  -> 종료
```

파이프/리다이렉트로 일괄 입력도 가능합니다:

```bash
printf 'cat\nsunset\nquit\n' | .venv/bin/python generate_image.py --offline -i --steps 30 --output outputs/batch.png
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
| `--negative-prompt` | 없음 | 이미지에 포함하지 않을 내용 (미지정 시 얼굴 변형/아티팩트 방지 프리셋 자동 적용) |
| `--width` / `--height` | `1024` / `1024` | 생성 이미지 크기 (**8의 배수 필수**, VAE 다운샘플 배수) |
| `--steps` | `50` | 노이즈 제거 스텝 수 (클수록 품질↑, 시간↑) |
| `--guidance` | `4.0` | 가이던스 스케일 (클수록 프롬프트 충실도↑) |
| `--cfg-trunc-ratio` | `0.25` | Lumina2 의 CFG 절단 비율 |
| `--seed` | `random` | 재현용 시드 (미지정 시 매번 랜덤, 사용된 시드는 로그와 PNG 메타데이터에 기록) |
| `-n` / `--count` | `1` | 프롬프트당 생성할 이미지 수 (각기 다른 시드, 파일명에 `_000`... 인덱스 추가) |
| `--output` | 없음 | 출력 경로. 기본은 `outputs/<모델명>_<YYYY-MM-DD_hh-mm-ss>.png` (인터랙티브: `_카운터` 추가) |
| `--device` | `auto` | `cuda` / `mps` / `cpu` 자동 선택 |
| `--cpu-offload` | off | VRAM 부족 시 CPU 오프로드 (accelerate 필요) |
| `--offline` | off | 로컬 캐시만 사용 (네트워크 차단) |
| `--timing` | off | 로딩/생성 소요 시간 출력 |
| `-i` / `--interactive` | off | 모델 1회 로드 후 프롬프트 반복 입력 (Ctrl-C 또는 `exit`/`quit`로 종료) |

## 참고 사항

- **PNG 메타데이터**: 생성에 사용한 프롬프트(원본/확장), 시드, steps, guidance,
  해상도, device, dtype 등이 이미지 파일에 함께 저장됩니다. `--seed` 를 다시
  지정하면 동일한 이미지를 재현할 수 있습니다.

  ```bash
  # 확인 방법 (PIL)
  .venv/bin/python -c "from PIL import Image; print(Image.open('outputs/xxx.png').info)"
  ```

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

## 실사 품질 개선 가이드 (클라우드 vs 로컬)

Lumina 공식 클라우드 서비스 대비 로컬(M1 Max) 실행 결과가 인물 묘사 품질이
떨어지거나 인공적(AI 느낌)으로 보이는 이유는 크게 네 가지입니다.

1. 클라우드는 입력 프롬프트를 내부 LLM/캡셔너(예: UniCap)가 이미지 생성에
   최적화된 상세 프롬프트로 자동 확장(Expansion)합니다.
2. 클라우드는 H100/A100 수준 GPU에서 원본 정밀도(BF16/FP16)로 추론합니다.
   로컬에서 8-bit/4-bit 양자화 웨이트를 쓰면 디테일이 손실됩니다.
3. 샘플링 파라미터(스텝 수, CFG, shift) 차이에 따라 질감 감도가 달라집니다.
4. 클라우드는 생성 후 자동으로 얼굴 보정(Face Restoration)과
   업스케일(Hi-Res) 후처리를 수행합니다.

### 1. 프롬프트 상세 묘사 (가장 큰 차이)

로컬은 입력한 텍스트가 그대로 디퓨전 모델에 전달되므로 피부 질감, 미세한 조명,
눈동자 디테일이 생략됩니다. 이 프로젝트는 프롬프트에 마커(`{realism}` 등)를
넣으면 아래 프리셋 키워드로 자동 확장합니다 (직접 명시도 가능).

| 마커 | 확장 키워드 (요약) |
| --- | --- |
| `{realism}` | raw photo, realistic skin pores, subsurface scattering, 85mm, f/1.8, 8k |
| `{portrait}` | professional portrait, 85mm f/1.8, shallow depth of field, studio lighting |
| `{cinematic}` | cinematic still, film grain, anamorphic lens, color grading, 35mm film |
| `{landscape}` | wide angle, golden hour, dramatic sky, HDR, professional photography |
| `{product}` | commercial product photo, studio lighting, softbox, clean background |
| `{anime}` | anime illustration, clean line art, vibrant colors, detailed eyes |
| `{macro}` | macro photography, extreme close-up, shallow depth of field |

여러 마커를 함께 쓸 수도 있으며, 같은 키워드 세트를 직접 붙여 넣어도 됩니다.

```text
# {realism} 마커가 확장하는 실제 키워드
raw photo, realistic skin pores, fine wrinkles, subsurface scattering,
natural soft lighting, shot on 85mm lens, f/1.8, subtle imperfections, 8k resolution
```

사용 예시:

```bash
# 마커 없이 간단한 프롬프트
.venv/bin/python generate_image.py --prompt "portrait of a young woman, natural light" --offline

# {realism} 마커로 실사 키워드 자동 확장
.venv/bin/python generate_image.py \
  --prompt "portrait of a young woman, natural light, {realism}" \
  --offline
```

인터랙티브 모드에서도 동일하게 마커를 사용할 수 있습니다:

LLM 확장 대체 방법: Ollama/MLX 등 로컬 LLM에 "다음 문장을 실사 인물 생성을 위한
세부 디퓨전 프롬프트로 확장해줘" 시스템 프롬프트를 거친 결과를 입력해도 효과적입니다.

### 2. 정밀도(Precision) 확인

- 클라우드는 BF16/FP16 원본 정밀도로 추론하며, 양자화 웨이트는 피부의 부드러운
  음영이나 눈동자 반사 디테일을 잃어 "플라스틱 같은" AI 느낌을 강화합니다.
- 이 프로젝트는 MPS에서 자동으로 **float16**을 사용하므로 이미 권장 수준입니다
  (M1 Max 는 통합 메모리 32GB + 400 GB/s 대역폭으로 fp16 로딩에 충분).
- ComfyUI 사용 시 `--highvram` 옵션과 MPS(Metal) 설정에서 정밀도 다운스케일링이
  적용되어 있지 않은지 확인하세요.

### 3. 샘플링 파라미터 최적화

| 파라미터 | 권장값 | 설명 |
| --- | --- | --- |
| Steps | 30~50 | 기본 20스텝보다 높여 디테일 형성 (이 프로젝트 기본값 50) |
| CFG Scale | 4.0 ~ 6.0 | 너무 높으면 피부가 매끄럽고 인공적 색감 (기본값 4.0) |
| Sampler / Scheduler | Euler / DPM++ 2M 계열 | 디테일과 자연스러움 균형 |

### 4. 얼굴 보정 + 업스케일 파이프라인 (ComfyUI)

클라우드는 생성 후 자동으로 후처리하므로, 로컬(ComfyUI)에서는 다음을 추가하세요.

- **Face Detailer** (Impact Pack / ReActor): 파이프라인 후단에 연결해 얼굴 영역만
  고해상도로 재합성(Inpaint) — 눈동자, 속눈썹, 입술 질감이 크게 개선됩니다.
- **Hi-Res Fix / Tile Upscale**: 1차 생성 이미지(예: 1024x1024)에 Denoise 0.3~0.4 로
  1.5x~2x 업스케일 — 피부 솜털이나 모공 디테일이 추가됩니다.

### 요약 (M1 Max 실사 품질 추천 세팅)

```bash
# 프롬프트의 {realism} 마커가 실사 키워드로 자동 확장됨
.venv/bin/python generate_image.py \
  --prompt "portrait of a young woman, natural light, {realism}" \
  --steps 50 --guidance 4.0 \
  --device mps --offline
```

- 프롬프트에 `{realism}` 마커로 실사 텍스처 키워드(raw photo, skin pores, natural lighting, 85mm) 자동 추가
- Steps 35 이상, CFG 5.0 이하로 설정
- M1 Max 메모리가 허용하는 한 BF16/FP16 원본 정밀도 (MPS 는 float16, 이미 적용됨)
- ComfyUI 로 Face Detailer + Upscale 파이프라인 구축
