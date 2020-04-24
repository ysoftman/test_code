#!/bin/bash
# time 측정
time sleep 1

rm -f time_command.timelog

# time 측정값 파일로 기록
echo "sleep 2 && sleep 1 elapsed time" > time_command.timelog
{ time (sleep 2 && sleep 1); } 2>> time_command.timelog
