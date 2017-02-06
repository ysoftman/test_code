#!/bin/bash

# 텍스트 파일 만들기
echo 'create text_file_sample\n'
echo 'ysoftman 1234 bill
jane    9999
tom 5555

' > text_file_sample

# text_file_sample 에서 라인별로 읽어 a,b,c 변수로 읽어 
# 파싱시 기본 구분자는 공백
echo 'parse text_file_sample'
while read a b c
do
    echo $a $b $c
done < text_file_sample

# 텍스트 파일 삭제
echo 'remove text_file_sample'
rm text_file_sample
