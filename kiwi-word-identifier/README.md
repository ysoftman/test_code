# Kiwi 오타 교정 사용법 (macOS arm64)

[Kiwi](https://github.com/bab2min/Kiwi)는 한국어 형태소 분석기로, 0.13.0 버전부터 오타 교정 기능을 지원한다.

## 1. 다운로드 및 CLI로 오타 교정 실행

```bash
# 바이너리: `kiwi_mac_arm64_v0.23.2.tgz`
wget https://github.com/bab2min/Kiwi/releases/download/v0.23.2/kiwi_mac_arm64_v0.23.2.tgz

# 모델: `kiwi_model_v0.23.2_base.tgz` (base 모델만 제공)
wget https://github.com/bab2min/Kiwi/releases/download/v0.23.2/kiwi_model_v0.23.2_base.tgz

tar xzf kiwi_mac_arm64_v0.23.2.tgz
tar xzf kiwi_model_v0.23.2_base.tgz
```

`kiwi-cli`의 오타 교정 관련 옵션:

- `--typo <float>`: 오타 비용 가중치. 0보다 크면 교정 활성화 (기본값 0 = 비활성)
- `--btypo`: 기본 오타 세트 (`--typo`만 주고 이 옵션들을 생략하면 자동 활성화)
- `--ctypo`: 연철 오타 세트
- `--ltypo`: 장음화 오타 세트

```bash
./bin/kiwi-cli-* -m <모델_경로> --typo 1 -o output.txt input.txt
```

실행 예시: 위치 인자는 파일 경로만 받으므로, 문장을 바로 넘길 때는 프로세스 치환 `<(echo ...)` 을 쓴다. `echo ... |` 로 stdin 에 넘겨도 되지만 대화형 프롬프트 `>> ` 가 출력에 섞인다.

```bash
$ ./bin/kiwi-cli-0.23.2 -m models/cong/base --typo 1 <(echo "외않되? 서버 재시작 햇는데 안됀다고 하잔아")
Kiwi v0.23.2
Typo Correction Cost Weight: 1
왜/MAG	안/MAG	되/VV	어/EF	?/SF	서버/NNG	재/XPN	시작/NNG	하/XSV	었/EP	는데/EC	안/MAG	되/VV	ᆫ다고/EC	하/VV	잖아/EF
```

- 출력은 교정된 문장이 아니라 `형태소/품사` 열이고, 교정은 그 안에 반영된다. `외않되` → `왜 안 되어`, `햇는데` → `하였는데`, `안됀다고` → `안 된다고`, `하잔아` → `하잖아`.
- **`kiwi-cli` 로는 교정 결과(문장)만 뽑아낼 수 없다.** 형태소 열을 다시 문장으로 조립하는 옵션이 없기 때문이다. 교정 문장만 필요하면 2절의 `kiwipiepy` 를 사용한다.
- 가중치를 올리면 교정이 보수적으로 바뀐다. `--typo 6` 에서는 `안됀다고`, `하잔아` 만 교정되고 `외않되/NNG`, `엇/EP` 는 그대로 남는다. `--typo 0`(기본) 은 교정 없음.
- 반대로 가중치가 낮으면 오교정이 생길 수 있다. `쉘 재시작` 은 `--typo 1` 에서 `제시/NNG 작/NNG` 으로 잘못 바뀐다 (`--typo 6` 에서는 정상). 위 문장의 `서버 재시작` 은 문맥 덕에 `--typo 1` 에서도 정상 분석된다.

## 2. Python(kiwipiepy)으로 교정 문장만 출력

`kiwi-cli` 는 형태소 열만 출력하고 문장 복원 옵션이 없다. 교정된 문장만 보려면 Python 바인딩 `kiwipiepy` 로 `tokenize` 한 뒤, 교정된 `(형태, 품사)` 튜플을 `join` 으로 다시 조립한다.

```bash
uv run --with kiwipiepy python - <<'EOF'
from kiwipiepy import Kiwi
kiwi = Kiwi(model_path="models/cong/base")
toks = kiwi.tokenize("외않되? 서버 재시작 햇는데 안됀다고 하잔아", typos="basic")
print(kiwi.join([(t.form, t.tag) for t in toks]))
EOF
# 왜 안 돼? 서버 재시작햇는데 안 된다고 하잖아
```

- `join` 에 Token 을 그대로 넣으면 원문 표면형이 복원되어 원문이 그대로 나온다. 반드시 `(t.form, t.tag)` 튜플로 바꿔 넘긴다.
- 띄어쓰기는 `join` 이 다시 결정한다 (`재시작 햇는데` → `재시작햇는데`). 원문 띄어쓰기 보존 옵션은 없다.
- CLI `--typo 1` 보다 보수적이다. `햇는데` 는 교정되지 않고 `typo_cost_threshold` 를 2.5 → 6.0 으로 올려도 같다. `Kiwi()` 에는 CLI `--typo` 에 해당하는 가중치 인자가 없다 (0.23.2 기준). 대신 `쉘 재시작` 오교정은 생기지 않는다.
- 어떤 토큰이 교정됐는지 보려면 `t.typo_cost > 0` 인 토큰을 확인한다.
- `typos=` 를 `Kiwi()` 생성자에 주면 0.23.0 부터 deprecated 경고가 나므로 `tokenize` 인자로 준다.
