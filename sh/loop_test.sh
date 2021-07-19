#!/bin/bash

# 무한 루프
# cnt=0
# while :
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
