#!/bin/bash
# ysoftman
# 숫자 변수 테스트

num1=1
num2=2
if [[ $num1 < $num2 ]]; then
    echo "$num1 < $num2"
fi
num1=1
num2=1
# 이중소괄호는 C형태의 산술연산이 가능하다.
if (( $num1 <= $num2 )); then
    echo "$num1 <= $num2"
fi
# $를 생략해도 된다.
(( ++num1 ))
(( num1++ ))
echo $num1
(( --num1 ))
(( num1-- ))
echo $num1
# 삼항 연산도 가능
(( out = num1==1?99:100 ))
echo $out
# modular 연산
echo "9%8 = $((9%8))"