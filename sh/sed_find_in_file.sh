#!/bin/bash
# ysoftman

TEMP_FILE="${0}.tmp"
# 테스트를 위한 임시 파일 생성
cat > ${TEMP_FILE} << 'zzz'
this string data for test.
ysoftman
123456789
zzz
# ${TEMP_FILE} 내용에서 ysoftman 찾으면 출력 끝내기
cat ${TEMP_FILE} | sed "/ysoftman/q"
# 임시 파일 삭제
rm -f ${TEMP_FILE}
