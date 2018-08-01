#!/bin/bash
# ysoftman
# 구구단 출력

# bash 산술 표현은 $(( )) 또는 let 을 사용한다.
a=$((1+2))
echo "a=\$((1+2))" : ${a}
let a=3+4
echo "let a=3+4" : ${a}

for ((i=1;i<=9;i++))
do
    for ((j=1;j<=9;j++))
    do
        echo $i \* $j = $(($i*$j))
    done
    echo ""
done
