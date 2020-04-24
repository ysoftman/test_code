#!/bin/bash
# time 측정
time sleep 1

rm -f time_command.log

# time 측정값 파일로 기록
echo "sleep 2 && sleep 1 elapsed time" > time_command.log
# { } 를 사용할때는 { 공백 } 으로 사용해야 한다.
# { time (sleep 2 && sleep 1); } 2>> time_command.log

# 명령에러(asdf) stderr 가 파일에만 기록되는 문제가 있다.
#(time (sleep 2; asdf; sleep 1)) 2>> time_command.log

# 명령에러(asdf) stderr 출력 및 파일에도 기록되
(time (sleep 2; asdf; sleep 1)) 2> >(tee -a time_command.log)
