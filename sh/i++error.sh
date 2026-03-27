#!/usr/bin/env bash

set -e
i=-1
while ((i < 10)); do
    echo $i
    # 후위 증가 연산(post increment operator) 주의
    # ((...)) 계산 결과 0이면 exit status = 1(실패)가 된다.
    # set -e 는 exit status 이 0 아니면 즉시 종료
    # ((i++))
    # 전위 증가 연산(pre increment operator) 연사도 i=-1 부터 시작이면 0에서 종료
    # ((++i))
    # 다음 방법이 안전한다.
    i=$((i + 1))
done
