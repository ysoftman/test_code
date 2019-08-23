#!/bin/bash
# ysoftman
# 디렉토리 내의 모든 파일들을 대상으로 문자열 찾기
# -r : 재귀수행(하위 디렉토리)
# -n : 라인번호# --include=*.cpp : cpp 확장자 파일만 대상
# -E : 확장 정규식 사용 or(|) 연산을 사용하기 위해
# "ysoftman|bill" : ysoftman 또는 bill 문자열이 있는 경우
# . : 시작할 디렉토리
# 정규식 OR 연사자 |
grep -rn --include="grep_test.txt" -E "name|yoon" .
# 정규식 AND 연자사는 없어어 "pattern2.*pattern2" 로 찾는다.
grep -rn --include="grep_test.txt" -E "name.*yoon" .

# -e 로 패턴 여러개를 명시해도 된다.
# ps 컬럼명과 포함해서 보기
ps -ef | grep -e "PID" -e "grep"

# 현재 계정으로 실행중인 프로세스들에서 grep 빼고 보기
ps | grep "" | grep -v "grep"

# -i --ignore-care 대소문자 구별 없이 찾기
echo 'fruite lemon apple' | grep -i "LEMON"

# -m --max-count=num 개수만큼 매칭하고 reading 중지
ls -1 | grep .sh -m 5
