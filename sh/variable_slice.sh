#!/bin/bash

msg='"I likes lemon."'

echo $msg

# 0 부터 시작해서 8개 문자 출력
echo ${msg:0:8}
echo ${msg::8}

# 9 부터 시작해서 5개 문자 출력
echo ${msg:9:5}

# 0 부터 마지막에서 -1 까지 문자 출력
echo ${msg::-1}

# 0 부터 마지막에서 -1 까지 문자 출력
# trim 으로 사용하기 좋을 것 같다.
echo ${msg:1:-1}
