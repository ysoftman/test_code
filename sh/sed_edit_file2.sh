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

# ${TEMP_FILE} 에서 ysoftman -> bill 로 변경해서 저장
# -i 확장자 명시하면 수정결과를 파일로 저장하고 수정전의 원본파일.확장자 파일로 저장한다.
# -i '' (mac)
# 또는 -i 로 옵션값이 없으면 (linux)
# 원본 백업 파일을 생성하지 않고 대상 파일을 변경한다.
echo 'replace ysoftman to bill in '${TEMP_FILE}
if [[ $(uname -s) =~ ^Darwin.* ]]; then
    sed -i '' -e 's/ysoftman/bill/g' ${TEMP_FILE}
elif [[ $(uname -s) =~ ^Linux.* ]]; then
    sed -i -e 's/ysoftman/bill/g' ${TEMP_FILE}
fi
cat ${TEMP_FILE}

# 임시 파일 삭제
rm -f ${TEMP_FILE}
