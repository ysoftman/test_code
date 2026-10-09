#!/bin/bash
# ysoftman

# 쉘 스크립트 정적 분석 도구 shellcheck
# 설치: brew install shellcheck
# 검사: shellcheck shellcheck.sh
# 특정 코드만 검사: shellcheck -i SC2155 shellcheck.sh
# 주의: "# shellcheck ..." 로 시작하는 주석은 directive 로 해석된다.
# 참고 https://www.shellcheck.net/wiki/SC2155

# SC2155 (warning): Declare and assign separately to avoid masking return values.
# local(declare, export, readonly 도 동일) 선언과 $(...) 대입을 한줄에 하면
# $? 에는 $(...) 명령이 아니라 local 명령 자체의 종료 코드(거의 항상 0)가 남아
# 명령 실패가 가려진다(masking).

bad() {
    # SC2155 경고 발생
    local result=$(false)
    echo "bad  : \$?=$?" # false 가 실패했지만 local 의 결과인 0 이 출력됨
}

good() {
    # 선언과 대입을 분리하면 $? 에 $(...) 명령의 종료 코드가 남는다.
    local result
    result=$(false)
    echo "good : \$?=$?" # false 의 결과인 1 이 출력됨
}

bad
good

# set -e(명령 실패시 스크립트 종료) 를 사용해도 bad 방식은 실패를 감지하지 못한다.
(
    set -e
    f() {
        local v=$(false)
        echo "set -e + bad  : 실패를 감지하지 못하고 계속 진행됨"
    }
    f
)
(
    set -e
    f() {
        local v
        v=$(false)
        echo "set -e + good : 여기는 출력되지 않음"
    }
    f
)
echo "set -e + good : 실패 감지로 subshell 종료, \$?=$?"

# SC1091 (info): Not following: ./lib.sh was not specified as input (see shellcheck -x).
# source 경로는 알지만 검사 대상으로 넘기지 않아 해당 파일 내부는 검사하지 않는다는 안내.
# 검사시 -x 옵션을 주면 source 파일까지 따라가서 검사한다.
# ~/.shellcheckrc 등에서 disable 되어 있다면 --norc 옵션으로 확인할 수 있다.
[[ -f ./lib.sh ]] && source ./lib.sh

# SC1090 (warning): ShellCheck can't follow non-constant source. Use a directive to specify location.
# source 경로가 변수, 명령 출력처럼 실행 시점에 정해져 어떤 파일인지 알 수 없다는 경고.
lib=$(mktemp)
cat >"$lib" <<'EOF'
echo "SC1090 : source $1"
EOF
source "$lib" "bad"
# 해결: source=<경로> directive 로 실제 파일을 알려주거나, 따라갈 파일이 없으면 /dev/null 로 지정한다.
# shellcheck source=/dev/null
source "$lib" "good"
rm -f "$lib"

# SC2139 (warning): This expands when defined, not when used. Consider escaping.
# alias 를 큰따옴표로 정의하면 변수가 정의 시점에 값으로 고정된다.
# 사용 시점에 확장하려면 작은따옴표를 사용한다. 정의 시점 고정이 의도라면 disable 한다.
dir="/tmp"
alias goto_dq="cd $dir" # cd /tmp 로 고정
alias goto_sq='cd $dir' # 실행할 때의 $dir 사용
dir="/usr"
alias goto_dq goto_sq

# SC2045 (error): Iterating over ls output is fragile. Use globs.
# $(ls) 출력은 공백 기준으로 단어 분리되어 공백이 있는 파일명이 깨진다.
tmp_dir=$(mktemp -d)
touch "$tmp_dir/a b.txt" "$tmp_dir/c.txt"
for f in $(ls "$tmp_dir"); do
    echo "ls   : [$f]" # [a] [b.txt] [c.txt] 로 분리됨
done
for f in "$tmp_dir"/*; do
    echo "glob : [${f##*/}]" # [a b.txt] [c.txt]
done
# 매칭되는 파일이 없으면 bash 는 패턴 문자열 그대로 남고, zsh 는 no matches found 에러가 난다.
# 존재 여부를 확인하거나 bash 는 shopt -s nullglob 을 사용한다.
for f in "$tmp_dir"/*.yaml; do
    [[ -e $f ]] || continue
    echo "yaml : $f"
done
rm -rf "$tmp_dir"

# SC2207 (warning): Prefer mapfile or read -a to split command output (or quote to avoid splitting).
# arr=($(cmd)) 는 출력이 IFS(공백,탭,줄바꿈) 기준으로 단어 분리되고 glob(*) 도 확장된다.
# zsh 는 단어 분리는 되지만 glob 확장은 하지 않는다(GLOB_SUBST 미설정시).
tmp_dir=$(mktemp -d)
touch "$tmp_dir/x.txt" "$tmp_dir/y.txt"
arr=($(printf '%s\n' "a b" "$tmp_dir/*.txt"))
echo "SC2207 bad     : $(printf '[%s] ' "${arr[@]##*/}")" # [a] [b] [x.txt] [y.txt]

# 해결: mapfile 로 줄 단위로 담는다(bash 4+ 에서만 동작).
if ((BASH_VERSINFO[0] >= 4)); then
    mapfile -t arr < <(printf '%s\n' "a b" "$tmp_dir/*.txt")
    echo "SC2207 mapfile : $(printf '[%s] ' "${arr[@]##*/}")" # [a b] [*.txt]
fi

# bash 3.2, zsh 에서도 동작하는 방법(대신 길다)
arr=()
while IFS= read -r line; do
    arr+=("$line")
done < <(printf '%s\n' "a b" "$tmp_dir/*.txt")
echo "SC2207 read    : $(printf '[%s] ' "${arr[@]##*/}")" # [a b] [*.txt]
rm -rf "$tmp_dir"

# mapfile 은 zsh, bash 3.2(macOS 기본)에 없어 bash/zsh 양쪽에서는 arr=($(cmd)) 형태가 가장 간단하다.
# 출력에 공백, glob 문자가 없다면 disable 하고 사용한다.
# shellcheck disable=SC2207
arr=($(printf '%s\n' "apple" "lemon"))
echo "SC2207 disable : $(printf '[%s] ' "${arr[@]}")" # [apple] [lemon]

# 경고를 의도적으로 무시하려면 해당 라인 위에 disable 주석을 단다.
# 첫 명령 전(셔뱅 아래)에 두면 파일 전체, 그 외에는 바로 다음 명령에만 적용된다.
# 프로젝트/사용자 전체는 .shellcheckrc 에 disable=SC1091 처럼 지정한다.
# shellcheck disable=SC2155
export MY_PATH=$(pwd)
echo "MY_PATH=${MY_PATH}"
