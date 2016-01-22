#!/bin/sh
# ysoftman
currentpath=$(pwd)
ls -l *.pdf | awk '{print $9}' > pdflist
for i in `cat pdflist`
do
	echo "FileName : $currentpath/$i"
	for ((num=0; num<50; num++));
	do
		cat "$i-$num.jpg.txt" >> $i.txt || break
	done
done
