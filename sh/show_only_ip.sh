#!/bin/sh
# ysoftman
# 로컬 ip 만 파악하기
if [[ $(uname) == 'Darwin' ]]; then
    /sbin/ifconfig en0 | grep 'inet ' | awk '{print$2}'
    # 또는 다음과 같이 cut 을 사용해도 된다.
    # en0 정보만 보기 -> 'inet ' 부분만 보기 ->  공백으로 구분했을때 2번째 필드만 보기
    # /sbin/ifconfig en0 | grep 'inet ' | cut -d ' ' -f 2
elif [[ $(uname) == 'Linux' ]]; then
    # grep -n 으로 되어 있다면 달라질 수 있다.
    /sbin/ifconfig eth0 | grep 'inet ' | awk '{print$2}'
    # /sbin/ifconfig eth0 | grep 'inet ' | cut -d ' ' -f 2
fi
