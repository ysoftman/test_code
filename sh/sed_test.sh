#!/bin/bash
# ysoftman
# sed test1
# 하위 디렉토리(파일을 제외)만 출력하기
# ls -lR ./ ysoftman : ./ysoftman 디렉토리에서 -l : 리스트, -R : 하위 디렉토리
# | grep ":$" : 앞의 출력 결과를 파이프로 넘겨받아 : 로 끝나는 부분만 출력
# | sed 's/:/\//' : 앞의 출력 결과를 파이프로 넘겨받아 처음 부분을 [subdir] 로 바꿔서(추가) 출력
ls -lR .. | grep ":$" | sed "s/^/[subdir]/"
# sed_test.txt 내용에서 ysoftman 찾으면 출력 끝내기
cat sed_test.txt | sed "/ysoftman/q"

# sed test2
# 임시 텍스트 파일 생성
TEMP_FILE="sed_test.tmp"
echo 'aaa line1
bbb line2
ccc line3
ddd line4
eee line5
fff line6
ggg line7
hhh line8
iii line9
jjj line10' > ${TEMP_FILE}
# 라인2만 삭제하고 출력
# d 삭제
echo 'delete line 2 and print'
cat ${TEMP_FILE} | sed  "2d;"
# 2~4 라인만 출력
# -n sed 가 입력받은 각라인의 에코 출력하는것을 막는다. 조건에 해당하는것만 출력하도록 한다.
# '2,4p' 2~4라인 프린트2~4라인 프린트
echo 'print only line 2~4'
cat ${TEMP_FILE} | sed -n "2,4p"
# 3~5 7~8 라인만 출력
# ; 는 조건의 끝을 나타낸다.
echo 'print only line 3~5, 7~8'
cat ${TEMP_FILE} | sed -n "3,5p;7,8p;"
# ccc ~ ggg 패턴 사이의 내용 출력
echo 'print only pattern ccc ~ ggg '
cat ${TEMP_FILE} | sed  -n "/^ccc/,/^ggg/p;"
# ccc ~ ggg 패턴 사이의 내용만 삭제하고 출력
echo 'delete pattern ccc ~ ggg and print'
cat ${TEMP_FILE} | sed "/^ccc/,/^ggg/d;"
# 임시 텍스트  파일 삭제
rm -f ${TEMP_FILE}


# @뒤로 삭제
out=`(echo "ysoftman @open (12345)" | sed "s/@.*$//")`
echo "$out"___result
# 공백@ 뒤로 삭제
out=`(echo "ysoftman @open (12345)" | sed "s/ @.*$//")`
echo "$out"___result