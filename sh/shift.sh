#!/bin/bash
# shift 인자 이동 테스트
# bash ./shift_test.sh 1 2 3 4 5
echo "argc: $#"
echo "args: $@"

while [[ $# -gt 0 ]]; do
    echo $1
    # 입력 받은 인자를 왼쪽으로 n 만큼 이동시킨다.
    shift 1
done
