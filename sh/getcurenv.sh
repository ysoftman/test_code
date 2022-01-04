#!/bin/sh
# ysoftman
value=$(pwd)
echo 'pwd='$value

value="this is sh script test...
abcdefg
1234456"


# 줄바꿈이 출력 안된다.
# bash 로 실행면 newline 대신 space 로 출력된다.
# bash getcurenv.sh
# zsh 로 실행면 newline 로 출력된다.
# zsh getcurenv.sh
echo "[no-newline]" $value

# "" 로 묶으면 줄바꿈도 출력된다.
echo "[newline] $value"
