#!/bin/sh
# ysoftman
# eval test

echo "eval command test..."

var1="ysoftman"

# 단순 문자열 자체를 출력한다.
var2="$"var1
echo $var2

# 문자열에 포함된 변수(또는 명령)를 실행하여 var1의 값을 출력하게 된다.
eval var2="$"var1
echo $var2
