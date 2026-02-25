#!/bin/bash
# ysoftman
# find test 1
# jpg 파일들만 검색해서 다른 디렉토리로 복사하기
# find . : 현재 디렉토리를 포함한 하위 디렉토리에서
# -name *.jpg : 확장자가 jpg 인 파일을 찾아
# -exec cp -v {}  /home/ysoftman/ \; : 찾은결과 {} 에서 /home/ysoftman 로 -v 복사상태를 표시하며 복사(-exec 는 항상 공백\; 로 끝나야한다.)
find . -name "*.jpg" -exec cp -v {} /home/ysoftman/ \;

# find test 2
# 특정 파일들의 특정 문자열 변경하여 저장하기 테스트
TEMP_FILE1="test1.txt"
TEMP_FILE2="test2.txt"
echo 'ysoftman' >${TEMP_FILE1}
echo 'ysoftman' >${TEMP_FILE2}

# 특정 파일들의 특정 문자열 변경하여 저장하기
# find . : 현재 디렉토리를 포함한 하위 디렉토리에서
# -type f : 파일타입이 f(일반 파일)인 경우만
# -name text*.txt : text*.txt 포맷의 파일을 찾아
# -exec sed -i '' 's/ysoftman/bill/g' {} \;
#   sed 를 실행하여 찾은파일들 {} 의 각 내용에 ysoftman을 bill 로 g(문서 전체)에서 바꾼다.
#   -i '' 으로 바로 파일 변경하기, 원본 파일을 백업할 경우 파일 명시, 없으면 원본파일 백업 안함.(mac 에서는 -i 뒤에 원본 백업이 없어도 '' 명시해야함)
#   (-exec 는 항상 공백\; 로 끝나야한다.)
find . -type f -name "test*.txt" -exec sed -i '' 's/ysoftman/bill/g' {} \;

# 참고로 파일 하나에 대해서
# sed -i '' 's/ysoftman/bill/g' test1.txt

# 변경 내용 확인
cat ${TEMP_FILE1}
cat ${TEMP_FILE2}

# 임시 텍스트  파일 삭제
rm -f ${TEMP_FILE1} ${TEMP_FILE2}

# find test 3
# 현재로 부터 1일 전(24~48) 수정된 파일만 찾기
find . -name "*.txt" -mtime 1
# 현재로 부터 수정된지 1일 이상(24~) 파일만 찾기
find . -name "*.txt" -mtime +1

# find test 4
# gopath, chromium 가 들어간 경로는 제외하고 .git  이 있는 디렉토리 찾기
find ~/workspace -name .git -not -path "*gopath*" -not -path "*chromium*"
