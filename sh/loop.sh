#!/bin/bash

# 무한 루프
# cnt=0
# while : ; do
#     sleep 1
#     cnt=$(($cnt+1))
#     echo $cnt
# done
# # 또는
# for (( ; ; ))
# do
#     sleep 1
#     cnt=$(($cnt+1))
#     echo $cnt
# done
echo 'for (( i=0; i<5; i++ ))
do
    echo $i
done'

for (( i=0; i<5; i++ ))
do
    echo $i
done


echo 'i=0
j=10
while (( i<j )); do
    echo $i
    ((i++))
done'
i=0
j=10
while (( i<j )); do
    echo $i
    ((i++))
done

# sh(일반 리눅스 배포판에서는 sh->bash라 상관없음)에서는 for ((;;)) 문법이 지원되지 않아 while 사용해야 한다.
echo 'i=0; while [ $i -lt 10 ]; do echo $i; i=$((i+1)); done;'
i=0; while [ $i -lt 10 ]; do echo $i; i=$((i+1)); done;


# 1 ~ 20 까지 출력
echo "{1..20} =>" {1..20}
# 1 ~ 20 까지 every 2nd 출력
echo "{1..20..2} =>" {1..20..2}
# 1 ~ 20 까지 every 2nd 출력
echo "seq 1 2 20 =>" $(seq 1 2 20)

# in 으로 범위 명시
echo 'for v in {1..10}; do echo $(($v*100)); done'
for v in {1..10}; do echo $(($v*100)); done

echo 'for v in {1..10..3}
do
    echo $(($v*100))
done'
for v in {1..10..3}
do
    echo $(($v*100))
done

echo 'for v in $(seq 1 3 10)
do
    echo $(($v*100))
done'
for v in $(seq 1 3 10)
do
    echo $(($v*100))
done

echo 'for i in $0 a b c 1 2 3
do
    echo $i
done'
for i in $0 a b c 1 2 3
do
    echo $i
done
