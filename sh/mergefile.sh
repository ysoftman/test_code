#!/bin/sh
# ysoftman

currentpath=$(pwd)
mergedfile="content.txt"

rm -f ${mergedfile}

# txt 파일명으로 리스트 파일 생성
ls -l *.txt | awk '{print $9}' > txtlist
for i in `cat txtlist`
# 파일 내용 하나로 취합
do
	echo "FileName : ${currentpath}/${i}"
	cat "${i}" >> ${mergedfile}
done
