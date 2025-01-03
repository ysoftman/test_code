#!/bin/bash
# ysoftman

# -r \ escape 처리 하지 않기
# -p 로 프롬프트 메시지 출력 후 입력받기
read -r -p "input:" input
echo $input

# -n 3 으로 문자 3개만 입력 받기
read -r -n 3 ysoftman
echo $ysoftman

# 이스케이프문자 처리 ex) a\t\t\b
read -r var1
echo $var1

# 텍스트 파일 만들기
printf 'create text_file_sample\n'
echo 'ysoftman 1234 bill
jane    9999
tom 5555

' >text_file_sample

# text_file_sample 에서 라인별로 읽어 a,b,c 변수로 읽어
# 파싱시 기본 구분자는 공백
echo 'parse text_file_sample'
while read -r a b c; do
    echo $a $b $c
done <text_file_sample

# 텍스트 파일 삭제
echo 'remove text_file_sample'
rm text_file_sample
