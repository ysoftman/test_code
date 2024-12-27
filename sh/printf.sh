#!/bin/bash
printf "%s\n" "~~ysoftman~~"
# -문자 로 시작시 -옵션일 수 있어 -- 로 옵션이 끝났을을 설정해야 한다
# -% invalid option
#printf "-%s\n" "~~ysoftman~~"
printf -- "-%s\n" "~~ysoftman~~"
function aaa() {
    # "$*" 로 ""로 감싸면 arguments 모두를 문자(word) 하나로 취급해 출력시 차이가 없다.
    echo "$*"
    printf "$*\n"

    echo "echo-arguments: $@"
    # printf 로 arguments 배열를 출력하면 각 원소 마다 printf format 으로 출력 된다.
    printf "printf-argument: %s\n" "$@"
}

aaa ysoftman lemon apple 1 2 3
