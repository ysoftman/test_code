#!/bin/sh

# ysoftman
# tr 을 이용한 문자 변경 테스트

# 소문자를 대문자로 변경
echo "ysoftman" | tr "[a-z]" "[A-Z]"

# 개행을 공백으로 변경
cal | tr "\n" " "

# 숫자 제거하여 출력
cal | tr -d "[0-9]"

# m -> x, a -> y, n -> z 문자로 변경
echo "ysoftman123" | tr "man" "xyz"

