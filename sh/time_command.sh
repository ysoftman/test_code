#!/bin/bash
# time 측정
time sleep 1

rm -f time_command.timelog

# time 측정값 파일로 기록
echo "sleep 2 && sleep 1 elapsed time" > time_command.timelog
# { time (sleep 2 && sleep 1); } 2>> time_command.timelog
# 명령에로(asdf) stderr 도 같이 기록되는 문제가 있다.
(time (sleep 2; asdf; sleep 1)) 2>> time_command.timelog
