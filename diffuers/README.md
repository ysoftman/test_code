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

실행 시 사용 가능한 프롬프트 마커(`{realism}` 등), 프롬프트 작성 요령, 나쁜/좋은
프롬프트 예시, 종료 방법이 컬러로 표시되며 `help` 를 입력하면 언제든 다시 볼 수
있습니다. (파이프/리다이렉트 사용 시에는 색상이 제거됩니다)

```bash
.venv/bin/python generate_image.py --offline -i

# [info] prompt markers (type 'help' to show this again):
#   {realism}
#       Shot as a raw, unretouched photograph on an 85mm lens at f/1.8. The skin
#       shows visible pores, fine lines and the soft translucency of subsurface
#       scattering under gentle natural light, with small imperfections left in.
#   ... ({portrait} {cinematic} {landscape} {product} {anime} {macro})
#   exit or quit to stop
#
# [info] how to write a prompt:
#   - Write in English. UniCap captioned the training data in English and
#     Chinese only, so Korean conditions the model far more weakly.
#   - Describe the whole scene in sentences, not comma-separated tags. ...
#   - Say where the light comes from and what it does. ...
#   - Name specific imperfections - uneven skin, freckles, stray hair, stubble. ...
#   - Skip {product} for people. ...
#
# [info] bad - comma-separated tags, Korean:
#     한국 20대 여성, 단발머리, 화장없이, 자연스러운, raw photo, 8k, {realism}{product}
# [info] good - English, whole scene described:
#     A quiet photograph of a Korean woman in her mid-twenties, shoulder-length
#     dark hair cut in a soft bob and tucked behind one ear, ... Cool overcast
#     light from a large window on her right wraps softly around her face and
#     leaves the left side in gentle shadow. ... {realism}
#
# prompt> help  -> 안내 다시 표시
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
| `--negative-prompt` | 없음 | 이미지에 포함하지 않을 내용 (미지정 시 빈 문자열 — Lumina-2.0 공식 권장, 부정 프롬프트는 효과가 제한적) |
| `--system-prompt` | `aesthetics` | 논문 프롬프트 템플릿 (`aesthetics` / `alignment` / `superior`) 또는 임의 문장 |
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

## 실사 품질 개선 가이드 (인물이 "AI 티" 날 때)

인물 생성 결과가 인공적으로 보이는 원인은 **거의 전부 프롬프트**입니다. 모델
차이나 정밀도 문제가 아닙니다. 같은 체크포인트·같은 시드(592831894)·같은
파라미터(1024x1024, 30스텝, guidance 4.0, cfg_trunc 0.25, MPS float16)로
프롬프트만 바꿔 확인한 결과입니다.

| 프롬프트 | 결과 |
| --- | --- |
| 한국어 + 쉼표 태그 나열 | 매끈한 플라스틱 피부, 회색 무배경, 어색한 표정 |
| 영어 번역 + 쉼표 태그 나열 | 머릿결/표정이 개선되나 여전히 스톡사진 느낌 |
| 영어 **서술형 캡션** | 방향성 있는 광선, 실제 그림자, 필름 톤 — 사진처럼 보임 |

### 1. 영어로 쓴다 (가장 큰 차이)

[Lumina-Image 2.0 논문](https://arxiv.org/abs/2503.21758)에 따르면 학습 캡션
(UniCap)은 **영어와 중국어로만** 생성됐고, 그 외 언어는 Gemma2 텍스트 인코더의
다국어 능력에서 파생된 것(emergent)입니다. 논문이 예로 든 언어는 독일어·일본어·
러시아어이며 **한국어는 없습니다**.

게다가 Gemma 토크나이저는 한국어를 음절 단위로 쪼갭니다.

```text
'백','인','▁모델',',','▁','푸','른','▁눈','동','자',',','▁갈','색','▁머','리' ...  → 49 토큰
동일 의미의 영어 문장                                                            → 26 토큰
```

토큰 수는 두 배인데 의미 신호는 더 약합니다. 한국어가 섞이면 스크립트가 경고를
출력합니다.

### 2. 태그 나열 대신 서술형 문장으로 쓴다

논문은 캡션이 정밀하고 상세할수록 수렴이 빨라지며, text-image attention 이
dynamic FFN 처럼 동작해 **캡션 길이가 곧 모델 capacity** 라고 설명합니다.
Lumina-2 는 UniCap 의 긴 서술형 캡션으로 학습됐으므로, Stable Diffusion 1.5
시절의 `raw photo, skin pores, 85mm, f/1.8, 8k` 같은 쉼표 태그 나열은 학습
분포 밖입니다.

나쁨:

```text
백인 모델, 푸른 눈동자, 갈색 머리, 화장하지 않은, 웃는, 20대, raw photo, skin pores, 8k
```

좋음:

```text
A candid photograph of a woman in her mid-twenties with fair skin, blue-grey eyes
and loosely curled chestnut hair falling over one shoulder. She wears no makeup;
a few freckles cross her nose. She glances just off camera with a small, unforced
smile. Late afternoon window light rakes across her face from the left, leaving
soft shadow under the jaw. Shot on 85mm at f/1.8, visible skin texture and fine
hair strands, muted colours, slight film grain.
```

### 3. 마커(`{realism}` 등)로 서술형 문장을 붙인다

프롬프트에 마커를 넣으면 아래 문장으로 자동 확장됩니다 (직접 써도 됩니다).
마커 앞뒤 공백은 자동으로 정리되므로 `귀여운{realism}` 처럼 붙여 써도 됩니다.

| 마커 | 확장되는 내용 |
| --- | --- |
| `{realism}` | 85mm f/1.8 무보정 사진, 모공·잔주름·subsurface scattering 이 보이는 피부 |
| `{portrait}` | 85mm f/1.8 인물사진, 배경은 보케로 흐려지고 눈은 선명 |
| `{cinematic}` | 아나모픽 렌즈 35mm 필름 스틸, 드라마틱한 방향광, 절제된 컬러 그레이딩 |
| `{landscape}` | 골든아워 광각 풍경, 드라마틱한 하늘, 하이라이트/섀도 디테일 유지 |
| `{product}` | 대형 소프트박스 + 심리스 배경의 광고용 제품컷 |
| `{anime}` | 깔끔한 선화, 선명한 플랫 컬러, 정교한 눈동자의 애니 일러스트 |
| `{macro}` | 극단적 접사, 매우 얇은 초점면, 자연광, 세밀한 표면 질감 |

**`{product}` 를 인물에 쓰지 마세요.** "clean background, evenly exposed
advertising shot" 은 `{realism}`/`{portrait}` 이 요청하는 피부 질감과 정면으로
충돌해, 회색 배경 광고컷 + 플라스틱 피부를 만듭니다. 이 조합을 쓰면 경고가
출력됩니다.

### 4. system prompt (부차적)

논문의 프롬프트 템플릿을 `--system-prompt` 로 고를 수 있습니다.
기본값은 인물에 약간 유리한 `aesthetics` 입니다.

| 값 | 내용 |
| --- | --- |
| `aesthetics` (기본) | 심미성 우선 |
| `alignment` | 프롬프트 충실도 우선 |
| `superior` | diffusers 파이프라인 자체 기본값 |

임의 문장을 직접 넘겨도 됩니다. 효과는 1~3번보다 작습니다.

### 사실이 아닌 통설

- **"클라우드는 LLM 으로 프롬프트를 자동 확장한다"** — 공식 `demo.py` 와
  Hugging Face Space `app.py` 모두 프롬프트를 그대로 전달합니다. UniCap 은
  **학습 데이터 캡셔닝**에 쓰인 것이고 추론 시 확장기가 아닙니다.
- **"클라우드는 얼굴 보정/업스케일 후처리를 한다"** — 두 데모 모두 후처리가
  없습니다.
- **"fp16 정밀도 때문에 플라스틱 피부가 된다"** — 측정으로 기각했습니다.
  Gemma2 텍스트 인코더를 fp32(CPU) 와 fp16(MPS) 로 같은 프롬프트를 인코딩해
  비교하면 토큰별 cosine 유사도 **1.0000**, 상대 L2 오차 **0.12%**, NaN/Inf
  **0개** 입니다.
- **"파라미터 세팅이 다르다"** — 공식 `demo.py` 기본값은 cfg 4.0,
  cfg_trunc 0.25, t_shift 6, 18스텝입니다. 이 프로젝트와 같은 계열이고 스텝은
  오히려 더 많습니다.

> 참고: Lumina-Image-2.0 은 2B 모델입니다. 프롬프트를 고쳐도 FLUX.1-dev(12B) 급
> 이나 상용 서비스의 인물 실사 품질에는 미치지 못합니다. 비교 대상이 Lumina
> 공식 데모가 아니라면 "같은 모델" 이라는 전제부터 확인하세요.

### 요약 (M1 Max 실사 품질 추천 세팅)

```bash
.venv/bin/python generate_image.py \
  --prompt "A candid photograph of a woman in her mid-twenties with fair skin and
loosely curled chestnut hair. She wears no makeup and glances just off camera with
a small, unforced smile. Late afternoon window light rakes across her face from the
left. {realism}" \
  --steps 50 --guidance 4.0 \
  --device mps --offline
```

- 영어로, 태그 나열이 아니라 서술형 문장으로
- 인물에는 `{realism}` 또는 `{portrait}`, `{product}` 는 제외
- Steps 30 이상, guidance 4.0~5.0
- 얼굴 디테일을 더 올리려면 ComfyUI 에서 Face Detailer + Hi-Res Fix
  (Denoise 0.3~0.4, 1.5x~2x) 를 후단에 추가 — 이 스크립트 범위 밖입니다
