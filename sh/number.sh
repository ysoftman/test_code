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

echo '-----'
for ((i=0;i<10;i++)); do
    printf "i:%d cnt:%d\n" $i $cnt
    ((cnt++))
done

echo '-----'
text='apple
lemon
orange'
echo $text
# set -e
line_cnt=0
for line in ${text}; do
    echo $line_cnt $line
    # set -e 설정된 경우 line_cnt=0 부터 시작하는 경우 에러발생해 스크립트가 종료된다.
    # 따라서 set -e 가 있다면 +=1 로 사용하는게 안전하다.
    # ((line_cnt++))
    ((line_cnt+=1))
done
