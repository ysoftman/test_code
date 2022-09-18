#!/bin/bash
# delcare(typeset 이름으로도 사용), 변수 타입(특성) 지정

function aaa {
    echo "aaa"
}

# 함수 실행
aaa

# aaa 함수 정의 보기
echo "declare -f aaa"
declare -f aaa
# echo "typeset -f aaa"
# typeset -f aaa

# 모든 함수 정의 보기
# declare -f

# 읽기 전용으로 변수 선언
var_readonly="origin"
declare -r var_readonly
# var_readonly="modify"  # 읽기 전용 변수라 엘 발생
echo "var_readonly:" $var_readonly

# 변수를 정수 타입으로 선언
declare -i var_number
var_number=123
echo "var_number:" $var_number
var_number="aaa"  # 정수값이 아니라 0 으로 취급한다.
echo "var_number:" $var_number

# 변수를 배열 타입으로 선언
declare -a var_array
# -a 선언 하지 않으면 일반 문자열 변수타입인데
# -a 로 배열을 선언해서 배열[0] 에 값이 설정된다.
var_array="lemon apple orange"
echo "var_array:" ${var_array[*]}
echo "var_array:" ${var_array[0]}
var_array[1]="banana"
echo "var_array:" ${var_array[1]}

var_export="ysoftman"
# -x(export) 외부(새로운 쉘) 환경에서 var_export 변수를 사용가능하도록 한다.
declare -x var_export

# 모든 변수 이름 보기
# declare

# -x, -i, -r 등의 변수 상태 보기
declare -p | rg -i "var_.*"
