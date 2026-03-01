#!/usr/bin/env bash

set -e
i=0
while ((i < 10)); do
    echo $i
    # 후위 증가 연산(post increment operator) 주의
    # ((i++)) # set -e 설정시 0 ++ 를 하기 때문에 에러 리턴
    ((++i))
done
