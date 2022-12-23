#!/bin/bash
# 터미널 창 크기 변경에 따른 colums, lines 크기 파악하기

function output {
    clear
    echo "cols: $(tput cols), lines: $(tput lines)"
}

# SIGWINCH Window size change
# 터미널 윈도우 크기 변경시 output 함수 실행
trap output WINCH

output
while true; do
    sleep 0.1
    continue
done
