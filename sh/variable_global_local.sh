#!/bin/bash
# ysoftman

# 기본은 전역 변수
global_val="lemon"

aaa() {
    # local 을 사용하면 해당 스코프에서만 유효한 지역 변수가 된다.
    local local_val="orange"
    echo ${global_val}
    echo ${local_val}
}
aaa
echo ${global_val}
echo ${local_val} # 지역 변수라 출력되지 않음

readonly_var() {
    # -r : readonly 로컬 변수
    local -r v=$1
    # var="aaa"
    echo $v
}

modify_var() {
    # -n nameref (reference) 참조 변수로 값을 수정하면 원래 변수도 값이 수정된다.
    local -n ref=$1
    ref="modified"
    echo "$ret"
}

original="original"
readonly_var $original
echo $original

modify_var $original
echo $original
