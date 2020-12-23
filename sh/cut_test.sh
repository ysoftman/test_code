#!/bin/bash


# 위치는 1부터시작한다.
# character 1-6 까지 문자 출력
echo "'apple lemon'" | cut -c 1-6

# character 1~ 끝까지 문자 출력
echo "'apple lemon'" | cut -c 1-

# echo $(( $(wc -c cut_test_temp | awk '{print $1}')-2 ))

# character 처음과 마지가 ' 제거하고 문자 출력
echo "'apple lemon'" > cut_test_temp
cat cut_test_temp | cut -c 2-$(( $(wc -c cut_test_temp | awk '{print $1}')-2 ))

rm -f cut_test_temp
