#!/bin/bash
# ysoftman

# && -> newline
# linux
# \n 로 치환한다.
echo "ysoftman&&lemon" | sed -e 's/&&/\n/'

# linux, mac
# 실제 다음처럼 라인을 추가하고 닫아야한다
echo "ysoftman&&lemon" | sed -e 's/&&/\
/'

# linux, mac
# $....는 bash-ism 표현으로 \n 을 뉴라인으로 변환한다.
echo "ysoftman&&lemon" | sed $'s/&&/\\\n/'
