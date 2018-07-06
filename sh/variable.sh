#!/bin/bash
# ysoftman
# 변수 사용 테스트

var1="ysoftman"

# 변수 사용시 ${}와 같이 curly brace 로 감싸는 이유는 변수 확장(variable expansion)하기 위함이다.
echo $var1
# 변수화변수값을 얻어온 후 스트링을 추가하는 경우
echo ${var1}_add_something
# 다음과 같이 파라미터 개수가 10을 넘어가는 2자리수 부터는 {} 로 감싸줘야 한다.
echo $0 $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11}

# 매개변수 개수
echo $#
# 매개변수 모두
echo $*
# 매개변수 모두(문자로 취급)
echo $@

var1=""
# -z -n 을 뒤에 명시하면 "unary operator expected" 가 발생하니 주의!
# -z : null(empty) 인경우 체크
if [ -z "${var1}" ]; then
    echo "var1 is empty"
else
    echo "var1 =" ${var1}
fi

var1=1
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
echo "\${var3}:" ${var3}

# 명령 실행 후 응답 받기
output=$(echo "ysoftman_99s")
# 응답 내용 출력
echo "\${output}:" ${output}

# predefined variable
# http://www.tldp.org/LDP/abs/html/internalvariables.html
# 머신 타입
echo "\${MACHTYPE}:" ${MACHTYPE}
# 기본 에디터 프로그램
echo "\${EDITOR}:" ${EDITOR}
# 설정된 경로
echo "\${PATH}:" ${PATH}
# 스클비트 수행 시간
echo "\${SECONDS}:" ${SECONDS}
# 인자 개수
echo "\${#}:" ${#}
# 0번째 인자
echo "\${0}:" ${0}
# 1번째 인자
echo "\${1}:" ${1}
# 현재 디랙토리 전체 경로 출력
echo "\${PWD}:" ${PWD}
# 현재 디렉토리만 출력
echo "\${PWD##*/}:" ${PWD##*/}
# bash 버전
echo "\${BASH_VERSION}:" ${BASH_VERSION}
# 하드웨어 타입
echo "\${HOSTTYPE}:" ${HOSTTYPE}

echo "\${IFS}:" ${IFS}
for v in `cat variable.txt`
do
    echo ${v}
done

# 입력 필드 구분자를 뉴라인으로 명시, 기본은 스페이스
IFS=$'\n'
echo "\${IFS}:" ${IFS}
for v in `cat variable.txt`
do
    echo ${v}
done


var1="aaa"
var2="bb"
var3=${var1}${var2}
echo ${var3}
echo ${#var3}
if [[ ${#var3} == 5 ]]; then
    echo "len(${var3}) == 5"
fi