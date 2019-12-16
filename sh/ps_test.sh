#!/bin/bash
# ysoftman

# -e 모든 프로세스
# -f  uid, pid, parent pid, recent CPU usage, process start time 등 full 항목 보기
ps -ef | grep $(whoami)


# -o 특정 필드만 골라서 보기 (-f 랑 같이 쓸 수 없다.)
# lstart 로 정확한 프로세스 시작 시간을 알 수 있다.
ps -e -o ppid,pid,lstart,command | grep $(whoami)
