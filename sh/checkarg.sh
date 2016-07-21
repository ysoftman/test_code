#!/bin/bash

# ysfotman 
# 인자 처리 하기
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
