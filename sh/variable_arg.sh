#!/bin/bash
# ysoftman
# argument(인자) 변수
# https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Special-Parameters
# clear(이전 명령) 실행 후 리턴 값
echo '$?:'$?

# 현재 쉘 옵션들(set -o 으로 설정된 옵션들 파악)
echo '$-:'$-

# 현재 프로세스 ID
echo '$$:'$$

# 마지막 백그라운드 프로세스 ID
echo '$!:'$!

# args 개수
echo '$#:'$#

# args 모두, "$*" 로 사용하면 args 모두를 합쳐서 하나로 문자(word)로 취급
# "arg1 arg2" arg3 처럼 "" 로 된 arg 를 하나의 arg 구분하지 못한다.
echo '$*:'$*
for a in $*; do echo "-$a"; done;
for a in "$*"; do echo "error, double-quotes-$a"; done;
# $@ 는"로 없어도 splie  되지만 ""  없으면 re-splitting 될 수 있다
for a in $@; do echo "-$a"; done;
for a in "$@"; do echo "double-quotes-$a"; done;

# args 모두(n 개의 argument 가 유지되고, 각 argument는 문자로 취급)
echo '$@:' "$@"
# substring
# 1번째 뒤로 모두
echo "${@:1}"
# 2번째 뒤로 모두
echo "${@:2}"
# 2번째 부터 2개까지
echo "${@:2:1}"


# 0번째 인자
echo "\${0}:" ${0}
# 1번째 인자
echo "\${1}:" ${1}

# 다음과 같이 파라미터 개수가 10을 넘어가는 2자리수 부터는 {} 로 감싸줘야 한다.
echo '$0 $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11}:'$0 $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11}
