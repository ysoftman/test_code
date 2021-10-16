#!/bin/bash
# ysoftman

function fibonacci() {
    n=$1
    if (( n<=2 )); then 
        echo 1
        return
    fi
    # 리턴값은 종료 코드로 사용할 수 없어, echo(stdout)을 출력($()로 결과를 받아사용할 수도 있다.)
    echo $(( $(fibonacci $((n-1))) + $(fibonacci $((n-2))) ))
    return
}

for ((i=1;i<=10;i++)); do
    echo "fibonacci $i: " $(fibonacci $i)
done
