#!/bin/bash
# test(built-in) 또는 [ 표현 ] 은 조건을 평가한다.

# 디렉토리 존재여부
# -d file, True if file exists and is a directory.
if [ -d '/Users/ysoftman/workspace' ]; then
    echo "exist directory"
else
    echo "not exist directory"
fi

# 파일 존재여부
# e file, True if file exists.
if [ -e './exist_file.sh' ]; then
    echo "exist file"
else
    echo "not exist file"
fi

# 레귤러 파일 존재 하지 않는 경우
# -f file, True if file exists and is a regular file.
if [ ! -f './not_exist_file.sh' ]; then
    echo "not exist file"
fi

# EIDTOR 환경 변수가 값의 길이가 0 이 아닌 경우
# -z string     True if the length of string is zero.
if [ ! -z $EDITOR ]; then
    echo "\$EDITOR = $EDITOR"
fi



# [[ ]] 내에서는 C 와 같은 연산을 할 수 있다.
# var="a"
var="b"
echo $var
if [[ $var == 'a' ]]; then
    echo 'first'
# elif 를 써야 한다. else if 는 syntax error: unexpected end of file
elif [[ $var == 'b' ]]; then
    echo 'second'
else
    echo 'last'
fi

# *"aaa"* 로 aaa 가 포함된 문자열인지 체크할 수 있다.
var="ysoftman lemon 123"
echo $var
if [[ $var == *"man"* ]]; then
    echo "contain"
fi
if [[ $var == *"lemon 1"* ]]; then
    echo "contain"
fi
