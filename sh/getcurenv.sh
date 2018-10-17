#!/bin/sh
# ysoftman
value=$(pwd)
echo 'pwd='$value

value="this is sh script test...
abcdefg
1234456"
# 줄바꿈이 출력 안된다.
echo "[no-newline]" $value

# "" 로 묶으면 줄바꿈도 출력된다.
echo "[newline] $value"
