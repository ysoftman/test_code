#!/bin/bash

# ysoftman
# 인자 처리 하기

# 인자 리스트
echo 'arg list'
for i in "$@"
do
	echo $i
done

echo ""
# 인자들 모두를 하나의 스트링 인자로 표현
echo 'args as single sring'
# "" 로 감싸지 않으면 $@ 처럼 리스트가 된다.
# for i in $*
for i in "$*"
do
	echo $i
done

echo ""

# 인자 개수
argc=$#

echo "argc: $argc"

# -eq, -ne 는 숫자만 비교할 수있다.
# '1' "1" 은되고, 'a', "a" 는 안된다.
if [ 1 -ne $argc ]
then
	echo "argc != 1"
	echo "ex) $0 ysoftman"

elif [ 1 -eq $argc ]
then
	echo "argc == 1 .. ok"
	echo "argv0 = $0"
	echo "argv1 = $1"
fi


# 산술 연산시 (()) 사용
if (( $argc > 1 )); then
	echo "argc > 1 .. ok"
fi
if (( $argc >= 1 )); then
	echo "argc >= 1 .. ok"
fi
if (( $argc < 3 )); then
	echo "argc < 3 .. ok"
fi
if (( $argc <= 3 )); then
	echo "argc <= 3 .. ok"
fi

if [ $argc -gt 1 ]; then
	echo "argc > 1 .. ok"
fi
if [ $argc -ge 1 ]; then
	echo "argc >= 1 .. ok"
fi
if [ $argc -lt 3 ]; then
	echo "argc < 3 .. ok"
fi
if [ $argc -le 3 ]; then
	echo "argc <= 3 .. ok"
fi

arg1=$1

# string 비교
if [ $arg1 != "ysoftman" ]; then
	echo 'arg1 is not ysoftman.'
else
	echo 'arg1 is ysoftman.'
fi

# =~ 정규식 매칭
if [[ $arg1 =~ ^(apple|banana|lemon)$ ]]; then
	echo 'arg1 matched ^(apple|banana|lemon)$'
else
	echo 'arg1 not matched ^(apple|banana|lemon)$'
fi


case $arg1 in
	ysoftman)
		echo "case"
		echo "ysoftman";;
		# lemon 이 포함된 경우
	*lemon*)
		echo "case";
		echo 'it contains lemon';;
	*)
		echo "case"
		echo "other(*)";;
esac

