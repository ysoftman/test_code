#!/bin/bash

function aaa() {
    # "$*" 로 ""로 감싸면 arguments 모두를 문자(word) 하나로 취급해 출력시 차이가 없다.
    echo "$*"
    printf "$*\n"

    echo "echo-arguments: $@"
    # printf 로 arguments 배열를 출력하면 각 원소 마다 printf format 으로 출력 된다.
    printf "printf-argument: %s\n" "$@"
}

aaa ysoftman lemon apple 1 2 3
