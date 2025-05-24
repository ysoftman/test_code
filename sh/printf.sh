#!/bin/bash
printf "%s\n" "~~ysoftman~~"
# -문자 로 시작시 -옵션일 수 있어 -- 로 옵션이 끝났음을 설정해야 한다
# -% invalid option
#printf "-%s\n" "~~ysoftman~~"
printf -- "-%s\n" "~~ysoftman~~"
function aaa() {
    # "$*" 로 ""로 감싸면 arguments 모두를 문자(word) 하나로 취급해 출력시 차이가 없다.
    echo '$*:' "$*"
    printf "$*\n"

    # lint error) argument mixes string and arrayu
    # echo "echo-arguments: $@"
    echo "echo-arguments: $*"
    # printf 로 arguments 배열를 출력하면 각 원소 마다 printf format 으로 출력 된다.
    printf "printf-argument: %s\n" "$@"
}

aaa ysoftman lemon apple 1 2 3

# stdout 확인
# bash ./printf.sh 2> /dev/null
printf "stdout message\n"
# stderr 확인
# bash ./printf.sh > /dev/null
printf "stderr message1\n" >&2
printf >&2 "stderr message2\n"
