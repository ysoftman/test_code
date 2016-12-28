#!/bin/sh
# 버전 스트링 비교하기
version1="4.9.2"
version2="5.0.1"
echo 'version1='${version1}
echo 'version2='${version2}
# 내림 차순 정렬하여 version2 가 vesrion1 보다 높은지 파악한다.
highest_version="$(printf "${version1}\n${version2}" | sort -r | head -n1)"
echo 'highest_version='${highest_version}
if [ "${highest_version}"  == "${version1}" ]; then
    echo "${version1} > ${version2}"
else
    echo "${version1} < ${version2}"
fi
