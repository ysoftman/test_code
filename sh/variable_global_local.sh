#!/bin/bash
# ysoftman

# 기본은 전역 변수
global_val="lemon"

function aaa() {
    # local 을 사용하면 해등 스코프에서만 유효한 지역 변수가 된다.
    local local_val="orange"
    echo ${global_val}
    echo ${local_val}
}
aaa
echo ${global_val}
echo ${local_val} # 지역 변수라 출력되지 않음
