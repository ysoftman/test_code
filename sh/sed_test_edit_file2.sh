#!/bin/bash
# ysoftman

TEMP_FILE="${0}.tmp"

# 임시 텍스트 파일 생성
echo 'aaa line1
bbb line2
ccc line3
ddd line4
line 5 ysoftman 
eee line6
fff line7
ggg line8
hhh line9
iii line10
jjj line11' > ${TEMP_FILE}

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

# ${TEMP_FILE} 에서 ysoftman -> bill 로 변경해서 저장
echo 'replace ysoftman to bill in '${TEMP_FILE}
# -i '' 또는 -i 로 옵션값이 없으면 원본 백업 파일을 생성하지 않고 대상 파일을 변경한다.
sed -i '' -e 's/ysoftman/bill/g' ${TEMP_FILE}
cat ${TEMP_FILE}

# 임시 파일 삭제
rm -f ${TEMP_FILE}
