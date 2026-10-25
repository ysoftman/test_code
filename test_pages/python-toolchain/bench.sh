#!/bin/zsh
# pyenv / uv / mise / pip 벤치마크. 결과는 out/*.json 에 기록한다.
# pyenv 는 설치돼 있지 않아도 된다. 임시 디렉터리에 받아 같은 Python 을 연결해 잰다.
set -eu
W=${BENCH_TMP:-${TMPDIR:-/tmp}/python-toolchain-bench}
O=${0:A:h}/out
ROUNDS=${ROUNDS:-5}
UV=${UV:-$(command -v uv)}
MISE=${MISE:-$(command -v mise)}
PY=${PY:-$($MISE which python3)}
PYENV_REF=${PYENV_REF:-v2.8.13}
PKGS="requests rich pydantic httpx"

rm -rf $W && mkdir -p $W $O && cd $W
# 명령 앞에 env 를 붙이면 프로세스가 하나 더 떠서 시간이 섞이므로 미리 export 한다
export UV_CACHE_DIR=$W/uvc PIP_CACHE_DIR=$W/pipc

{
    $UV --version
    $MISE --version
    $PY --version
    hyperfine --version
} >$O/versions.txt

# 깨끗한 pyenv 에 측정용 Python 을 버전 이름 bench 로 연결한다
git clone -q --depth 1 --branch $PYENV_REF https://github.com/pyenv/pyenv $W/pyenv
mkdir -p $W/pyenv/versions && ln -s ${PY:h:h} $W/pyenv/versions/bench
PYENV_ROOT=$W/pyenv $W/pyenv/bin/pyenv global bench
PYENV_ROOT=$W/pyenv $W/pyenv/bin/pyenv rehash

# mise 바이너리를 python3 이름으로 링크하면 그대로 shim 이 된다
mkdir -p $W/shim && ln -s $MISE $W/shim/python3

# --bare 는 .python-version 을 쓰지 않으므로 pin 으로 같은 Python 을 고정한다
$UV init -q --bare --python $PY $W/proj
$UV python pin -q --project $W/proj $PY
$UV add -q --project $W/proj requests

# 단계마다 시작 시각과 load average(1/5/15분)를 남겨, 측정 조건을 기록된 값으로 인용한다
: >$O/load.txt
stage() {
    echo "== $1"
    echo "$(date +%T) $1 $(sysctl -n vm.loadavg)" >>$O/load.txt
}

stage startup
hyperfine -N -w 5 -r 30 --export-json $O/startup.json \
    -n "프로세스 1회" "/usr/bin/true" \
    -n "python 직접 실행" "$PY -c pass" \
    -n "pyenv shim" "$W/pyenv/shims/python -c pass" \
    -n "mise shim" "$W/shim/python3 -c pass" \
    -n "uv run (프로젝트 안)" "$UV run --project $W/proj python -c pass"

stage venv
hyperfine -w 2 -r 10 --export-json $O/venv.json \
    -n "python -m venv" --prepare "rm -rf $W/v1" "$PY -m venv $W/v1" \
    -n "uv venv --seed" --prepare "rm -rf $W/v2" "$UV venv -q --seed --python $PY $W/v2" \
    -n "python -m venv --without-pip" --prepare "rm -rf $W/v3" "$PY -m venv --without-pip $W/v3" \
    -n "uv venv" --prepare "rm -rf $W/v4" "$UV venv -q --python $PY $W/v4"

# 네트워크가 섞이는 측정은 명령을 1회씩 번갈아 ROUNDS 바퀴 재고 합친다.
# 짝수 바퀴는 순서를 뒤집어 순서 효과를 줄이고, 회차별 값은 xs 에 바퀴 순서대로 남긴다.
# alt <결과이름> <이름> <prepare> <명령> [<이름> <prepare> <명령> ...]
alt() {
    local out=$1
    shift
    local i k
    local -a ks=({1..$#..3})
    for i in {1..$ROUNDS}; do
        ((i % 2 == 0)) && ks=(${(Oa)ks})
        for k in $ks; do
            hyperfine -r 1 --style none --export-json $W/alt-$i-$k.json \
                -n "${@[k]}" --prepare "${@[k + 1]}" "${@[k + 2]}"
        done
        ((i % 2 == 0)) && ks=(${(Oa)ks})
    done
    jq -n '[inputs | {r: (input_filename | capture("alt-(?<i>[0-9]+)-").i | tonumber),
            name: .results[0].name, t: (.results[0].measurements[0].time_wall_clock.value * 1000)}]
        | group_by(.name)
        | map(sort_by(.r) | (map(.t)) as $x | ($x | add / length) as $m | {
            name: .[0].name, n: ($x | length), mean: $m, min: ($x | min), max: ($x | max),
            sd: (($x | map((. - $m) * (. - $m)) | add) / ([($x | length) - 1, 1] | max) | sqrt),
            xs: $x})' \
        $W/alt-*.json >$O/$out.json
    rm -f $W/alt-*.json
}

PIPV="rm -rf $W/p && $PY -m venv $W/p"
UVV="rm -rf $W/u && $UV venv -q --python $PY $W/u"
PIP="$W/p/bin/pip install -q --disable-pip-version-check"
UVP="$UV pip install -q --python $W/u/bin/python"

stage "install cold"
alt install_cold \
    "pip --no-compile" "$PIPV" "$PIP --no-cache-dir --no-compile $PKGS" \
    "uv pip" "rm -rf $UV_CACHE_DIR && $UVV" "$UVP $PKGS" \
    "pip" "$PIPV" "$PIP --no-cache-dir $PKGS" \
    "uv pip --compile-bytecode" "rm -rf $UV_CACHE_DIR && $UVV" "$UVP --compile-bytecode $PKGS"

stage "install warm"
hyperfine -w 1 -r 5 --export-json $O/install_warm.json \
    -n "pip --no-compile" --prepare "$PIPV" "$PIP --no-compile $PKGS" \
    -n "uv pip" --prepare "$UVV" "$UVP $PKGS" \
    -n "pip" --prepare "$PIPV" "$PIP $PKGS" \
    -n "uv pip --compile-bytecode" --prepare "$UVV" "$UVP --compile-bytecode $PKGS"

stage "python install"
# startup 측정이 끝났으므로 mise 경로를 임시 디렉터리로 돌려도 shim 측정에 영향이 없다
export MISE_DATA_DIR=$W/mise/data MISE_CACHE_DIR=$W/mise/cache MISE_STATE_DIR=$W/mise/state
alt pyinstall \
    "uv python install" "rm -rf $W/uvpy $W/uvc2" \
    "$UV python install -q --no-bin --install-dir $W/uvpy --cache-dir $W/uvc2 3.13.17" \
    "mise install" "rm -rf $W/mise" \
    "$MISE install -q python@3.13.17"

# 소스 컴파일은 몇 분 걸리므로 1회만 잰다
stage "pyenv install"
hyperfine -r 1 --export-json $O/pyenv_build.json \
    -n "pyenv install" --prepare "rm -rf $W/pyb" \
    "$W/pyenv/plugins/python-build/bin/python-build 3.13.17 $W/pyb"
(cd $W && du -sh uvpy mise/data/installs/python/3.13.17 pyb) >$O/sizes.txt
stage done

# 결과를 공개 저장소에 올리므로 명령 문자열 속 로컬 경로를 변수 이름으로 바꾼다
sed -i '' -e "s|$W|\$W|g" -e "s|$HOME|\$HOME|g" $O/*.json
