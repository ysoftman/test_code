#!/bin/bash
# ysoftman
find . -name *.cpp > temp_file_list.txt

# euc-kr 파일만 리스트 작성
for i in `cat temp_file_list.txt`
do
	# 'iso-8859-1' 인 경우 euc-kr 인코딩으로 취급
	charset=`file -bi "${i}" | awk '{print $2}'`
	echo ${i} ${charset}
	if [[ ${charset} == 'charset=iso-8859-1' ]]; then
		echo ${i} >> temp_euc_kr_file_list.txt
	fi
done

# euc-kr -> utf-8 인코딩
for i in `cat temp_euc_kr_file_list.txt`
do
	iconv --verbose -f EUC-KR -t UTF-8 ${i} > temp_file
	mv temp_file ${i}
done

rm temp_euc_kr_file_list.txt temp_file_list.txt
