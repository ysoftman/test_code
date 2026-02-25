#!/bin/bash
# ysoftman

# @뒤로 삭제
# Substitute 형식 : s/regular expression/replacement/flag
# delimiter 는 # , 공백도 사용할 수 있다. 상황에 맞게 backslash 없이 사용할때 유용
echo "ysoftman @open (12345) /abc/def/ggg" | sed "s/\/abc\/def\/ggg/zzzzz/"
echo "ysoftman @open (12345) /abc/def/ggg" | sed "s#/abc/def/ggg#zzzzz#"
echo "ysoftman @open (12345) /abc/def/ggg" | sed "s,/abc/def/ggg,zzzzz,"
echo "ysoftman @open (12345) /abc/def/ggg" | sed "s /abc/def/ggg zzzzz "
echo "ysoftman @open (12345) /abc/def/ggg" | sed "s/@.*$//"
# 여러개를 변경할 경우 ; 구분
echo "ysoftman @open (12345) /abc/def/ggg" | sed "s/abc/aaa/;s/def/bbb/;s/ggg/zzz/"
# 또는 -e 옵션 반복 사용
echo "ysoftman @open (12345) /abc/def/ggg" | sed -e "s/abc/aaa/" -e "s/def/bbb/" -e "s/ggg/zzz/"

# 공백@ 뒤로 삭제
echo "ysoftman @open (12345)" | sed "s/ @.*$//"

# 컬러문자의 경우
reset_color='\033[0m'
green='\033[0;32m'
# 공백이 아닌 컬러 문자가 포함되어 공백 뒤 삭제가 안된다.
echo -e "ysoftman ${green}color${reset_color} string " | sed "s/ color.*$//"
# 중간에 컬러 문자를 제거해줘야 한다.
echo -e "ysoftman ${green}color${reset_color} string " | sed "s,$(printf '\033')\\[[0-9;]*[a-zA-Z],,g" | sed "s/ color.*$//"
