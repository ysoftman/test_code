#!/bin/bash
echo "ysoftman" # ysoftman
echo 'ysoftman' # ysoftman
echo "'ysoftman'"   # 'ysoftman'
echo '"ysoftman"'   # "ysoftman"
echo "''ysoftman''" # ''ysoftman''

# single quote in single quote
# 방법1
# 이전 블럭은 '' 로 닫고 "' 로 ' 를 출력하는 방법
echo 'a' "'ysoftman'" 'b'   # a 'ysoftman' b

# 방법2
# bash 2.4 이후 $로 시작하면 escape 로 처리할 수 있다.
echo $'a \'ysoftman\' b'    # a 'ysoftman' b



####

set -x

var="__ysoftman\n
__apple__\n
__lemon__"

# '' 안에 변수 치환 예시
message='{"aaa":"A1", "bbb":"'"${var}"'", "ccc": "C3"}'
echo -e $message

set -
