#!/bin/bash
# ysoftman
# 변수 사용 테스트

clear

# clear(이전 명령) 실행 후 리턴 값
echo $?

# 현재 쉘 옵션들(set -o 으로 설정된 옵션들 파악)
echo $-

# 현재 프로세스 ID
echo $$

# 마지막 백그라운드 프로세스 ID
echo $!

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

# `` 으로 명령 실행 후 응답 받기
output=`echo "ysoftman_99s"`
echo "\${output}:" ${output}
# () 으로 명령 실행 후 응답 받기
output=$(echo "ysoftman_99s")
echo "\${output}:" ${output}

# predefined variable
# http://www.tldp.org/LDP/abs/html/internalvariables.html
# 머신 타입
echo "\${MACHTYPE}:" ${MACHTYPE}
# 기본 에디터 프로그램
echo "\${EDITOR}:" ${EDITOR}
# 설정된 경로
echo "\${PATH}:" ${PATH}
# 디폴트로 지정된 쉘
echo "\${SHELL}:" ${SHELL}
# 현재 사용중인 쉘(커맨드라인에서는 echo $0 만 실행해도 된다.)
echo "current shell:" $(ps $(echo $$) | awk '{print $5}' | sed -n "2p")
# 쉘 시작 후 경과 시간(초)
echo "\${SECONDS}:" ${SECONDS}
# 인자 개수
echo "\${#}:" ${#}
# 0번째 인자
echo "\${0}:" ${0}
# 1번째 인자
echo "\${1}:" ${1}
# 디폴트 프롬프트
echo "\${PS1}:" ${PS1}
# continue 프롬프트, 커맨드라인에더 다음줄에 계속 입력할때 표시되는 프롬프트
echo "\${PS2}:" ${PS2}
# select 명령 수행시 선택입력을 위해 표시되는 프롬프트
echo "\${PS3}:" ${PS3}
# 이전 디랙토리 전체 경로 출력
echo "\${OLDPWD}:" ${OLDPWD}
# 현재 디랙토리 전체 경로 출력(Print Working Directoy)
echo "\${PWD}:" ${PWD}
# ${var#Pattern} 변수 앞에서부터 패턴과 매치되는 가장 짧은 부분 제거
# ${var##Pattern} 변수 앞에서부터 패턴과 매치되는 가장 긴 부분 제거
# ${var%Pattern} 변수 뒤에서부터 패턴과 매치되는 가장 짧은 부분 제거
# ${var%%Pattern} 변수 뒤에서부터 패턴과 매치되는 가장 긴 부분 제거
echo "\${PWD#*/}" ${PWD#*/}
echo "\${PWD##*/}:" ${PWD##*/}  # 현재 디렉토리만 출력
echo "\${PWD%/*}" ${PWD%/*} # 현재 디록토리 상위 디렉토리까지의 full path
echo "\${PWD%%/*}" ${PWD%%/*}
# bash 버전
echo "\${BASH_VERSION}:" ${BASH_VERSION}
# 하드웨어 타입
echo "\${HOSTTYPE}:" ${HOSTTYPE}

var1="10.10.10.1:111 10.10.10.2:222 10.10.10.3:333"
cnt=0
for v in ${var1}; do
    # 변수 뒤에서부터 :* 매칭부분 제거
    ip=${v%:*}
    # 변수 앞에서부터 *: 매칭부분 제거
    port=${v#*:}
    echo "var1[$cnt] = ip-> ${ip} , port-> ${port}"
    (( cnt+=1 ))
done
echo "var1 = ${var1}"

# 배열(리스트) 변수의 경우
var1=("10.10.10.1:111" "10.10.10.2:222" "10.10.10.3:333")
echo "var1[0] = ${var1[0]}"
echo "var1[1] = ${var1[1]}"
echo "var1[2] = ${var1[2]}"
# [@] 배열의 모든 것
echo "var1[@] = ${var1[@]}"
# 배열 개수(크기)
echo "#var1[@] = ${#var1[@]}"
# 원소의 크기
echo "#var1[0] = ${#var1[0]}"

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

# 무한 루프
# cnt=0
# while :
# # 또는
# for (( ; ; ))
# do
#     sleep 1
#     cnt=$(($cnt+1))
#     echo $cnt
# done

var1="aaa"
var2="bb"
var3=${var1}${var2}
echo ${var3}
echo ${#var3}
if [[ ${#var3} == 5 ]]; then
    echo "len(${var3}) == 5"
fi


var1="1"
var2="2"
if [[ ${var1} == "1" ]] && [[ ${var2} == "2" ]]; then
    echo 'condition 1'
fi
if [[ ${var1} == "1" ]] && [[ ${var2} == "3" ]]; then
    echo 'condition 2'
fi
if [[ ${var1} == "5" ]] || [[ ${var2} == "2" ]]; then
    echo 'condition 3'
fi
if [[ ${var1} == "5" ]] || [[ ${var2} == "10" ]]; then
    echo 'condition 4'
fi


num1=1
num2=2
if [[ $num1 < $num2 ]]; then
    echo "$num1 < $num2"
fi
num1=1
num2=1
# 이중소괄호는 C형태의 산술연산이 가능하다.
if (( $num1 <= $num2 )); then
    echo "$num1 <= $num2"
fi
# $를 생략해도 된다.
(( ++num1 ))
(( num1++ ))
echo $num1
(( --num1 ))
(( num1-- ))
echo $num1
# 삼항 연산도 가능
(( out = num1==1?99:100 ))
echo $out
# modular 연산
echo "9%8 = $((9%8))"

# a,b,c 출력
echo {a,b,c}

# 1 ~ 10 까지 출력
echo "{1..20}" {1..20}
for v in {1..5}
do
    echo $(($v*100))
done
