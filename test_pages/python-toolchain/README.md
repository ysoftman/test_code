# Python Toolchain

pyenv, uv, mise 가 맡는 역할과 겹치는 기능, 그리고 hyperfine 으로 측정한 속도를 [`index.html`](index.html) 한 페이지로 정리한다. 측정값은 페이지 안의 `CHARTS` 에 직접 넣어 두어 정적 파일만으로 열린다.

## 측정

```bash
UV=$(command -v uv) MISE=/opt/homebrew/bin/mise zsh bench.sh
python3 gen_charts.py
bunx prettier --write index.html
```

`bench.sh` 는 결과를 `out/*.json` 에, 단계별 시작 시각과 load average 를 `out/load.txt` 에 기록한다. `gen_charts.py` 는 `out/` 을 읽어 `index.html` 의 `CHARTS` 블록과 측정 조건 문장(`#load-note`)을 다시 만든다. 결론 문장의 배수와 차이도 여기서 계산하므로 `index.html` 의 숫자를 손으로 고치지 않는다. 필요한 도구는 uv, mise, hyperfine, jq, git 이고, pyenv 소스 빌드에는 Xcode Command Line Tools 와 Homebrew 의 openssl@3, readline, xz 가 필요하다.

pyenv 는 설치돼 있지 않아도 된다. 임시 디렉터리에 `PYENV_REF` 를 받아, 측정용 Python 을 `bench` 라는 버전 이름으로 연결해 pyenv shim 을 잰다. mise shim 은 mise 바이너리를 `python3` 이름으로 링크해서 잰다.

| 변수 | 기본값 | 설명 |
| --- | --- | --- |
| `BENCH_TMP` | `$TMPDIR/python-toolchain-bench` | 임시 작업 디렉터리 |
| `UV` | PATH 의 `uv` | 측정할 uv 바이너리 |
| `MISE` | PATH 의 `mise` | 측정할 mise 바이너리. 비대화형 셸에서는 다른 mise 가 잡힐 수 있으므로 지정을 권한다 |
| `PY` | `$MISE which python3` | 세 도구가 공통으로 실행할 Python |
| `PYENV_REF` | `v2.8.13` | 받을 pyenv 버전(git 태그) |
| `ROUNDS` | `5` | 네트워크가 섞이는 측정을 번갈아 반복하는 횟수 |
