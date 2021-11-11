#!/bin/bash
# ysoftman
# trap(builtin command) test

# 사용가능한 signal list
trap -l

# signal 발생시 수행할 동작
trap "echo SIGHUP" SIGHUP
# exit 를 사용하지 않으면, ctrl-d 후 프로세스 kill
trap "echo SIGINT; exit 1" SIGINT # ctrl+c
trap "echo SIGQUIT; exit 0" SIGQUIT # ctrl+\

# 현재 설정된 trap 보기
trap -p

for ((;;)) do
    echo "trap testing, press ctlr+c or ctrl+\\"
    sleep 1;
done
