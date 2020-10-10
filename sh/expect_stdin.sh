#!/usr/bin/expect
# ysoftman
# bash 가 아닌  expect 로 실행해야 한다.

# 사용자가 apple 을 입력하면(apple 입력 될때까지 계속 입력 받는다.)
expect "apple"

# lemon 출력
send "lemon\n"
