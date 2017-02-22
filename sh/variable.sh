#!/bin/bash
# ysoftman
# 변수 사용 테스트

var1=""

# -z -n 을 뒤에 명시하면 "unary operator expected" 가 발생하니 주의!
# -z : null(empty) 인경우 체크
if [ -z "${var1}" ]; then
    echo "var1 is empty"
else
    echo "var1 =" ${var1}
fi
# -n : non-zero 값이 있는 경우
if [ -n "${var1}" ]; then
    echo "var1 is non-zone, var1 =" ${var1}
else
    echo "var1 is empty"
fi

# 변수 값 합차기
var1="ysoftman"
var2="123"
var3="${var1} ${var2}"
echo ${var3}

# 명령 실행 후 응답 받기
output=$(echo "ysoftman_99s")
# 응답 내용 출력
echo ${output}

# predefined variable
# http://www.tldp.org/LDP/abs/html/internalvariables.html
# 머신 타입
echo ${MACHTYPE}
# 기본 에디터 프로그램
echo ${EDITOR}
# 설정된 경로
echo ${PATH}
# 스클비트 수행 시간
echo ${SECONDS}
# 인자 개수
echo ${#}
# 0번째 인자
echo ${0}
# 1번째 인자
echo ${1}
# 현재 디랙토리 전체 경로 출력
echo ${PWD}
# 현재 디렉토리만 출력
echo ${PWD##*/}
