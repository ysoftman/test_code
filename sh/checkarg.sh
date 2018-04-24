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
if [ 1 -ne $argc ] 
then
	echo "argc != 1"
	echo "ex) $0 ysoftman"
	exit 1

elif [ 1 -eq $argc ]  
then
	echo "argc == 1 .. ok"
	echo "argv0 = $0"
	echo "argv1 = $1"
fi

arg1=$1
case $arg1 in
	ysoftman)
		echo "case"
		echo "ysoftman";;
	*)
		echo "case"
		echo "other(*)";;
esac

