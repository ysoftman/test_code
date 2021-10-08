#!/bin/bash

# ysoftman
i=0
# 숫자비교를 위해 -lt 를 사용
while [ ${i} -lt 10 ]
do
    echo ${i}
    # 기본적으로 변수값은 스트링으로 취급되어 숫자 연산을 위해선 expr 명령어를 사용한다.
    # expr 사용시 인자 사이를 띄워야 더하기 연산이 된다.
    # 붙이면 스트링형태로 처리된다.
    i=`expr ${i} + 1`
done
