"""out/ 의 측정 결과로 index.html 의 CHARTS 블록과 측정 조건 문장(#load-note)을 다시 만든다.

bench.sh 를 실행한 뒤 `python3 gen_charts.py` 로 실행하고, 이어서 prettier 로 포맷한다.
결론 문장의 수치(배수, 차이)도 여기서 계산하므로 index.html 의 숫자를 손으로 고치지 않는다.
"""

import json
import re
import statistics
from pathlib import Path

D = Path(__file__).resolve().parent
O = D / "out"


def load(name):
    return json.loads((O / f"{name}.json").read_text())


def hf(name):
    """hyperfine 2.0 export -> {이름: wall-clock 통계(ms)}"""
    out = {}
    for r in load(name)["results"]:
        t = r["summary"]["time_wall_clock"]
        out[r.get("name") or r["command"]] = {
            "mean": t["mean"] * 1000,
            "med": t["median"] * 1000,
            "sd": (t["stddev"] or 0) * 1000,
            "min": t["min"] * 1000,
            "max": t["max"] * 1000,
            "n": len(r["measurements"]),
        }
    return out


def cpu(name):
    """hyperfine 2.0 export -> {이름: 회차별 user + sys 통계(ms)}"""
    out = {}
    for r in load(name)["results"]:
        x = [
            (m["time_user"]["value"] + m["time_system"]["value"]) * 1000
            for m in r["measurements"]
        ]
        out[r.get("name") or r["command"]] = {
            "mean": statistics.mean(x),
            "med": statistics.median(x),
            "sd": statistics.stdev(x),
            "min": min(x),
            "max": max(x),
            "n": len(x),
        }
    return out


def alt(name):
    """bench.sh alt() 결과(ms). xs 는 바퀴 순서대로의 회차별 값"""
    return {r["name"]: r for r in load(name)}


def row(disp, tool, s, med=False):
    def f(v):
        return round(v, 1)

    parts = [f"name: {json.dumps(disp, ensure_ascii=False)}", f'tool: "{tool}"']
    if med:
        parts.append(f"med: {f(s['med'])}")
    parts.append(f"mean: {f(s['mean'])}")
    if s["n"] > 1:
        parts += [f"sd: {f(s['sd'])}", f"min: {f(s['min'])}", f"max: {f(s['max'])}"]
    parts.append(f"n: {s['n']}")
    return "{ " + ", ".join(parts) + " }"


def times(x):
    return f"{x:.1f}" if x < 10 else f"{x:.0f}"


def about(ms):
    return f"{round(ms, -1):.0f}" if ms >= 100 else f"{ms:.0f}"


def J(s):
    return json.dumps(s, ensure_ascii=False)


st, cp, ve = hf("startup"), cpu("startup"), hf("venv")
cold, warm, py = alt("install_cold"), hf("install_warm"), alt("pyinstall")
pb = hf("pyenv_build")["pyenv install"]
sizes = {}
for line in (O / "sizes.txt").read_text().splitlines():
    size, path = line.split()
    sizes[path.split("/")[0]] = size.replace("M", " MB")
loads = {}
for line in (O / "load.txt").read_text().splitlines():
    _, rest = line.split(" ", 1)
    stage, la = rest.rsplit("{", 1)
    loads[stage.strip()] = float(la.split()[0])

# 측정 조건
during = [v for k, v in loads.items() if k != "done"]
t_wall, t_cpu = st["프로세스 1회"], cp["프로세스 1회"]
load_note = (
    f"각 측정 단계를 시작할 때 기록한 load average(1분)는 {min(during):.1f}–{max(during):.1f} 사이였고, "
    f"마지막 pyenv 소스 컴파일 직후에는 {loads['done']:.1f} 정도였습니다. "
    f"아무 일도 하지 않는 <code>/usr/bin/true</code>도 실행에 {t_wall['min']:.0f}–{t_wall['max']:.0f} ms가 "
    f"걸렸지만 CPU 시간은 약 {t_cpu['mean']:.1f} ms였습니다. "
    + (
        "대부분이 기다린 시간이라, 짧은 명령은 CPU 시간 차트를 따로 실었습니다."
        if t_cpu["mean"] < t_wall["mean"] / 2
        else "짧은 명령은 CPU 시간 차트도 따로 실었습니다."
    )
)

# 인터프리터 시작: 중앙값 wall 차이로 쓰고, mise shim 대 uv run 은 wall 승률로 판정한 뒤 CPU 순서를 덧붙인다
base = st["python 직접 실행"]["med"]
dw = {
    k: st[k]["med"] - base for k in ("pyenv shim", "mise shim", "uv run (프로젝트 안)")
}
pe = st["pyenv shim"]


def walls(key):
    r = next(x for x in load("startup")["results"] if x.get("name") == key)
    return [m["time_wall_clock"]["value"] * 1000 for m in r["measurements"]]


# 명령마다 연달아 잰 값이라 회차 짝이 없으므로, 모든 값을 서로 견준 승률로 판정한다
mw, uw = walls("mise shim"), walls("uv run (프로젝트 안)")
p_uv = sum(x > y for x in mw for y in uw) / (len(mw) * len(uw))  # uv run 이 빠른 비율
gap = abs(int(about(dw["mise shim"])) - int(about(dw["uv run (프로젝트 안)"])))
if p_uv >= 0.9 or p_uv <= 0.1:
    fast_s, share = ("uv run", p_uv) if p_uv >= 0.5 else ("mise shim", 1 - p_uv)
    cpu_fast = (
        "uv run"
        if cp["uv run (프로젝트 안)"]["mean"] < cp["mise shim"]["mean"]
        else "mise shim"
    )
    pair = (
        f"mise shim과 uv run의 차이(약 {gap} ms)는 작지만, {len(mw)}회씩 잰 값을 서로 견주면 "
        f"{share * 100:.0f}%에서 {fast_s}이 빨랐습니다. "
        + (
            f"CPU 시간도 {fast_s}이 더 적게 썼습니다. "
            if cpu_fast == fast_s
            else f"CPU 시간은 반대로 {cpu_fast}이 더 적게 썼습니다. "
        )
    )
else:
    pair = f"mise shim과 uv run의 차이(약 {gap} ms)는 측정값이 서로 많이 겹쳐 의미 있게 보기 어렵습니다. "
startup_take = (
    f"python 직접 실행보다 pyenv shim은 약 {about(dw['pyenv shim'])} ms, mise shim은 약 "
    f"{about(dw['mise shim'])} ms, uv run은 약 {about(dw['uv run (프로젝트 안)'])} ms(중앙값 기준) "
    f"더 걸립니다. {pair}pyenv shim은 회차마다 {pe['min']:.0f}–{pe['max']:.0f} ms로 흔들림도 컸습니다. "
    "실제 걸린 시간에는 CPU를 쓰지 않고 기다린 시간도 들어 있으므로, CPU 시간은 다음 차트에서 따로 봅니다."
)
cbase = cp["python 직접 실행"]["mean"]
dc = {
    k: cp[k]["mean"] - cbase
    for k in ("pyenv shim", "mise shim", "uv run (프로젝트 안)")
}
wait_share = 1 - cp["pyenv shim"]["mean"] / st["pyenv shim"]["mean"]
cpu_take = (
    f"python 직접 실행보다 pyenv shim은 약 {about(dc['pyenv shim'])} ms, mise shim은 약 "
    f"{about(dc['mise shim'])} ms, uv run은 약 {about(dc['uv run (프로젝트 안)'])} ms의 CPU를 더 씁니다. "
    f"pyenv shim은 실제 걸린 시간(평균)의 약 {wait_share * 100:.0f}%가 CPU를 쓰지 않고 기다린 시간입니다. "
    "bash 스크립트가 하위 프로세스를 여러 번 띄우는데, 측정 당시 이 머신은 프로세스를 띄울 때마다 기다리는 "
    "시간이 길었습니다(원인은 확인하지 않았습니다). 프로세스 실행이 빠른 환경에서는 pyenv shim의 실제 시간이 "
    "훨씬 짧을 수 있습니다. mise를 기본 방식인 mise activate로 쓰면 PATH에 실제 설치 경로가 들어가 실행할 때 "
    "shim 비용이 붙지 않습니다(따로 재지는 않았고, 대신 프롬프트마다 mise hook-env가 실행됩니다). "
    "uv run에는 lockfile과 .venv 상태를 확인하는 시간이 들어 있습니다."
)

# venv
r_pip = ve["python -m venv"]["mean"] / ve["uv venv --seed"]["mean"]
r_nopip = ve["python -m venv --without-pip"]["mean"] / ve["uv venv"]["mean"]
venv_take = (
    f"pip을 넣을 때는 uv가 약 {times(r_pip)}배, pip 없이 만들 때는 약 {times(r_nopip)}배 빠릅니다. "
    "python -m venv는 pip을 venv 안에 새로 설치하고, uv는 캐시에 있는 pip을 복제해 넣습니다. "
    "uv venv는 기본으로 pip을 넣지 않습니다."
)

# 패키지 설치: 같은 pyc 조건끼리 짝
pairs = {
    ("cold", "nopyc"): (cold["pip --no-compile"], cold["uv pip"]),
    ("cold", "pyc"): (cold["pip"], cold["uv pip --compile-bytecode"]),
    ("warm", "nopyc"): (warm["pip --no-compile"], warm["uv pip"]),
    ("warm", "pyc"): (warm["pip"], warm["uv pip --compile-bytecode"]),
}
rr = {k: a["mean"] / b["mean"] for k, (a, b) in pairs.items()}
cr = sorted(v for (c, _), v in rr.items() if c == "cold")
wr = sorted(v for (c, _), v in rr.items() if c == "warm")
best = max(rr, key=lambda k: rr[k])
best_txt = {"cold": "캐시가 없고", "warm": "캐시가 있고"}[best[0]] + {
    "nopyc": " pyc를 만들지 않을 때",
    "pyc": " pyc를 만들 때",
}[best[1]]
pkg_take = (
    f"캐시가 없으면 uv가 {times(cr[0])}–{times(cr[1])}배, 캐시가 있으면 {times(wr[0])}–{times(wr[1])}배 "
    f"빠릅니다. 차이가 가장 큰 경우는 {best_txt}입니다. pip은 캐시가 있어도 매번 압축을 풀어 복사하지만, "
    "uv는 캐시에 풀어 둔 파일을 APFS clone으로 복제하기만 합니다. pyc를 미리 만들지 않으면 처음 import할 때 "
    "만들어지므로 그 시간이 사라지는 것은 아닙니다. 실제 uv 프로젝트는 lockfile이 있어 의존성 해석을 건너뛰는 "
    "uv sync를 쓰므로 이 측정과 조건이 다릅니다."
)

# 인터프리터 설치: 회차별 승패로 판단한다
u, m = py["uv python install"], py["mise install"]
n = len(u["xs"])
mise_wins = sum(a > b for a, b in zip(u["xs"], m["xs"], strict=True))
fast, k = ("mise", mise_wins) if mise_wins * 2 > n else ("uv", n - mise_wins)
diff = abs(u["mean"] - m["mean"]) / 1000
if k == n:
    order = f"번갈아 잰 {n}회 모두 {fast}가 빨랐지만(평균 {diff:.1f}초 차이) 원인은 확인하지 않았습니다. "
elif k >= 0.8 * n:
    order = f"번갈아 잰 {n}회 중 {k}회는 {fast}가 빨랐지만(평균 {diff:.1f}초 차이) 원인은 확인하지 않았습니다. "
else:
    order = f"번갈아 잰 {n}회 중 {k}회만 {fast}가 빨라 우열이 뚜렷하지 않습니다(평균 {diff:.1f}초 차이). "
mm, ss = divmod(round(pb["mean"] / 1000), 60)
py_take = (
    "uv와 mise는 python-build-standalone의 같은 미리 빌드된 파일(cpython-3.13.17+20261021 "
    "install_only_stripped)을 받아 풀기 때문에 몇 초면 끝나고, 설치 크기도 "
    f"{sizes['uvpy']}와 {sizes['mise']}로 거의 같습니다. {order}"
    "uv는 이 파일을 Astral 미러(releases.astral.sh)에서 받습니다. "
    f"pyenv는 CPython을 소스에서 컴파일해 {mm}분 {ss}초가 걸렸고 설치 크기는 {sizes['pyb']}였습니다. "
    f"컴파일 단계를 시작할 때 load average(1분)가 {loads['pyenv install']:.1f} 정도로 다른 작업도 CPU를 쓰고 "
    "있었으므로, 조용한 머신에서는 컴파일이 더 빨리 끝날 수 있습니다."
)

charts = f"""      // ms 단위. med 가 있으면 막대는 중앙값, 없으면 평균. gen_charts.py 가 out/*.json 에서 생성한다
      const CHARTS = [
        {{
          title: "인터프리터 시작: 실제 걸린 시간",
          desc: "아무것도 하지 않는 Python을 한 번 실행하는 데 걸린 wall-clock 시간입니다. 세 도구 모두 같은 Python 3.14.8을 실행합니다. 가끔 크게 튀는 회차의 영향을 줄이려고 막대는 평균 대신 중앙값으로 그렸습니다.",
          groups: [
            {{
              label: "",
              rows: [
                {row("프로세스 1회 (/usr/bin/true)", "base", st["프로세스 1회"], True)},
                {row("python 직접 실행", "base", st["python 직접 실행"], True)},
                {row("pyenv shim", "pyenv", st["pyenv shim"], True)},
                {row("mise shim", "mise", st["mise shim"], True)},
                {row("uv run (프로젝트 안)", "uv", st["uv run (프로젝트 안)"], True)},
              ],
            }},
          ],
          takeaway: {J(startup_take)},
        }},
        {{
          title: "인터프리터 시작: CPU 시간",
          desc: "같은 측정에서 프로세스와 그 하위 프로세스가 실제로 CPU를 쓴 시간(user + sys)입니다. 기다린 시간이 빠지므로 부하의 영향을 덜 받습니다.",
          groups: [
            {{
              label: "",
              rows: [
                {row("프로세스 1회 (/usr/bin/true)", "base", cp["프로세스 1회"])},
                {row("python 직접 실행", "base", cp["python 직접 실행"])},
                {row("pyenv shim", "pyenv", cp["pyenv shim"])},
                {row("mise shim", "mise", cp["mise shim"])},
                {row("uv run (프로젝트 안)", "uv", cp["uv run (프로젝트 안)"])},
              ],
            }},
          ],
          takeaway: {J(cpu_take)},
        }},
        {{
          title: "venv 생성",
          desc: "가상환경 하나를 새로 만드는 시간입니다. pip을 넣는지에 따라 짝을 지어 비교했고, 매 회 디렉터리를 지우고 다시 만들었습니다.",
          groups: [
            {{
              label: "pip 포함",
              rows: [
                {row("python -m venv", "base", ve["python -m venv"])},
                {row("uv venv --seed", "uv", ve["uv venv --seed"])},
              ],
            }},
            {{
              label: "pip 없음",
              rows: [
                {row("venv --without-pip", "base", ve["python -m venv --without-pip"])},
                {row("uv venv", "uv", ve["uv venv"])},
              ],
            }},
          ],
          takeaway: {J(venv_take)},
        }},
        {{
          title: "패키지 설치: requests rich pydantic httpx",
          desc: "빈 venv에 패키지 4개와 그 의존성을 설치하는 시간입니다. pyenv는 패키지를 다루지 않아 pyenv 환경에서는 pip이 이 일을 맡으므로 pip과 uv를 비교합니다. pip은 기본으로 .pyc 바이트코드를 만들고 uv는 만들지 않으므로, 같은 조건끼리 짝을 지었습니다.",
          groups: [
            {{
              label: "캐시 없음 · pyc 안 만듦",
              rows: [
                {row("pip --no-compile", "base", cold["pip --no-compile"])},
                {row("uv pip", "uv", cold["uv pip"])},
              ],
            }},
            {{
              label: "캐시 없음 · pyc 만듦",
              rows: [
                {row("pip", "base", cold["pip"])},
                {row("uv pip --compile-bytecode", "uv", cold["uv pip --compile-bytecode"])},
              ],
            }},
            {{
              label: "캐시 있음 · pyc 안 만듦",
              rows: [
                {row("pip --no-compile", "base", warm["pip --no-compile"])},
                {row("uv pip", "uv", warm["uv pip"])},
              ],
            }},
            {{
              label: "캐시 있음 · pyc 만듦",
              rows: [
                {row("pip", "base", warm["pip"])},
                {row("uv pip --compile-bytecode", "uv", warm["uv pip --compile-bytecode"])},
              ],
            }},
          ],
          takeaway: {J(pkg_take)},
        }},
        {{
          title: "인터프리터 설치: Python 3.13.17",
          desc: "Python 3.13.17을 새로 설치하는 시간입니다. uv와 mise는 같은 시간대에 번갈아 {n}회씩(짝수 회차는 순서를 뒤집어), pyenv는 소스 컴파일이라 1회만 쟀습니다. 매 회 설치 디렉터리와 캐시를 지웠습니다.",
          groups: [
            {{
              label: "",
              rows: [
                {row("uv python install", "uv", u)},
                {row("mise install", "mise", m)},
                {row("pyenv install (python-build)", "pyenv", pb)},
              ],
            }},
          ],
          takeaway: {J(py_take)},
        }},
      ];"""

page = D / "index.html"
s = page.read_text()
s, n1 = re.subn(
    r"      // ms 단위\..*?\n      \];", lambda _: charts, s, flags=re.DOTALL
)
s, n2 = re.subn(
    r'(<span id="load-note"\s*>).*?(</span\s*>)',
    lambda mt: mt.group(1) + load_note + mt.group(2),
    s,
    flags=re.DOTALL,
)
if (n1, n2) != (1, 1):
    raise SystemExit(f"치환 위치를 찾지 못함: CHARTS={n1}, load-note={n2}")
page.write_text(s)
print(load_note)
print(startup_take, cpu_take, venv_take, pkg_take, py_take, sep="\n")
