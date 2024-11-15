#!/bin/bash

# pipe 로 standard input 으로 전달될때 - 로 한번에 읽을 라인의 개수 지정
# a b 를 한번에 읽고 출력 후 다음줄에 c 출력
echo "a
b
c" | paste - -

echo "======"
# -s 는 한줄로 합치 출력
echo "a
b
c" | paste -s -

# 5 columns in each line
#ls | paste - - - - -

echo "======"
echo "a
b
c" > paste_tmp1

echo "lemon
123" > paste_tmp2

echo "======"
# delimiter , 사용(디폴트 tab)
paste -s -d, paste_tmp1

echo "======"
# 파일 2개 라인별로 합치기
paste -d, paste_tmp1 paste_tmp2

echo "======"
# 파일 2개 각각 single line 후 다음 줄에 추가(2줄이 된다)
paste -s -d, paste_tmp1 paste_tmp2

rm -f paste_tmp1 paste_tmp2
