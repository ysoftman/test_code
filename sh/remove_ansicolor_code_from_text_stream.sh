#!/bin/bash
. echo_color.sh

# 컬러 출력 후 파일 기록
# ansi color 코드도 같이 파일로 기록
echo -e "${lightpurple}ysoftman${reset_color}" | tee ${0}.log
# ansi color 코드제거해  파일로 기록(stdout 에서는 y 문자 잘림 문제가 있다.)
echo -e "${lightcyan}ysoftman${reset_color}" | sed -e 's/\\033//g' -e 's/\[[0-9;]*m//' -e 's/\[0m//g' | tee -a ${0}.log
