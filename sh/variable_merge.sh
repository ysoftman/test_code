#!/bin/bash
# ysoftman

var1="ysoftman"
# 변수 사용시 ${}와 같이 curly brace 로 감싸는 이유는 변수 확장(variable expansion)하기 위함이다.
echo '$var1:'$var1
# 변수화변수값을 얻어온 후 스트링을 추가하는 경우
echo '${var1}_add_something:'${var1}_add_something

# 변수 값 합치기
var1="ysoftman"
var2="123"
var3="${var1} ${var2}"
echo "\${var3}:"${var3}

