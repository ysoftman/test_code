#!/bin/bash
# brew install coreutils 로 timeout 커맨드 설치

# timeout duration command command-args

# duration 이후 kill command kill
# 3초(기본 초단위) 후 sleep kill
# timeout 3 sleep 10

# 3초후 sleep 에 3(QUIT) 시그널 보내기
# timeout -s QUIT 3s sleep 10
timeout 3 bash -c 'echo "timeout 3 sleep 10"; for ((i=1;i<10;i++)) do echo $i; sleep 1; done;'
