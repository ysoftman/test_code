#!/bin/bash
# field 인덱스는 1부터시작한다.
# -d 구분자사용시 -f 필드 옵션은 항상 있어야 한다.
# : 로 구분했을때 1,3 번 필드
echo "'apple:lemon:banana'" | cut -d ':' -f 1,2,3
# : 로 구분했을때 2번필드부터 끝까지
echo "'apple:lemon:banana'" | cut -d ':' -f 2-

# character 1-6 까지 문자 출력
echo "'apple lemon'" | cut -c 1-6

# character 1~ 끝까지 문자 출력
echo "'apple lemon'" | cut -c 1-

# echo $(( $(wc -c cut_test_temp | awk '{print $1}')-2 ))

# character 처음과 마지가 ' 제거하고 문자 출력
echo "'apple lemon'" >cut_test_temp
cat cut_test_temp | cut -c 2-$(($(wc -c cut_test_temp | awk '{print $1}') - 2))

rm -f cut_test_temp
