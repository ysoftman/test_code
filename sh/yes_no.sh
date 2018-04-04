#!/bin/bash

echo "Yes Or No (y/n)?"
# 사용자 입력을 answer 변수에 담는다.
read answer

#echo ${answer}
# 소문자로 치환
answer=$(echo ${answer} | tr '[:upper:]' '[:lower:]')
# echo ${answer}

if [[ ${answer} == 'y' ]]; then
	echo 'Yes'
else
	echo 'No'
fi
