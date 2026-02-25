#!/bin/bash
# ysoftman
# 디렉토리 내의 모든 파일들을 대상으로 문자열 찾기
# -r : 재귀수행(하위 디렉토리)
# -n : 라인번호# --include=*.cpp : cpp 확장자 파일만 대상
# -E : 확장 정규식 사용 or(|) 연산을 사용하기 위해
# "ysoftman|bill" : ysoftman 또는 bill 문자열이 있는 경우
# . : 시작할 디렉토리
# 정규식 OR 연산자 |
grep -rn --include="grep.txt" -E "name|yoon" .
# 정규식 AND 연산자는 없어 "pattern2.*pattern2" 로 찾는다.
grep -rn --include="grep.txt" -E "name.*yoon" .

# tab 이 포함된 경우 다음과 같은 공백으로는 grep 되지 않는다.
grep "apple lemon" grep.txt
# -P, --perl-regexp 는 mac(BSD) grep 에서 지원하지 않는다.
# grep -P "apple\tlemon" grep.txt
# printf '\t' 나 echo '\t' 로 출력해서 탭을 표현
grep "apple$(printf '\t')lemon" ./grep.txt
grep "apple$(echo '\t')lemon" ./grep.txt

# -e 로 패턴 여러개를 명시해도 된다.
# ps 컬럼명과 포함해서 보기
ps -ef | grep -e "PID" -e "grep"

# 현재 계정으로 실행중인 프로세스들에서 grep 빼고 보기
ps | grep "" | grep -v "grep"

# -i --ignore-case 대소문자 구별 없이 찾기
echo 'fruite lemon apple' | grep -i "LEMON"

# -m num, --max-count=num 개수만큼 매칭하고 reading 중지
ls -1 | grep .sh -m 5 -n

# easy or medium or hard 단어가 없는 파일명 파악
# -i --ignore-case 대소문자 구별 없이 찾기
# -E easy|medium|hard : easy or medium or hard 가 있는 라인 찾기
# -c : 찾은 라인 카운트
# | grep ":0" : 앞서 찾은 파일:카운트 중 :0 인것만 파악
grep -i -E "easy|medium|hard" *.go -c | grep :0

# apple 이전 1줄 결과에 포함
echo -e 'fruite\nlemon\napple\nbanana' | grep -i "apple" --color=never -B 1

# apple 다음 1줄 결과에 포함
echo -e 'fruite\nlemon\napple\nbanana' | grep -i "apple" --color=never -A 1
