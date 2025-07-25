#!/bin/bash
# ysoftman

temp="
aaa line1
bbb line2ccc line3
ddd line4
line 5 ysoftman
eee line6
fff line7ggg line8
     hhh line9
     iii line10
     jjj line11
line 12 ysoftman
"

echo -e "$temp"
# d 삭제
# 라인2만 삭제하고 출력
echo 'delete line 2 and print'
echo -e "$temp" | sed "2d;"

# ccc ~ ggg 패턴 사이의 내용(라인들)만 삭제하고 출력
echo 'delete pattern ccc ~ ggg and print'
echo -e "$temp" | sed "/^ccc/,/^ggg/d"

echo 'find ysoftman and delete'
echo -e "$temp" | sed "s/ysoftman//g"

# d 는 라인 단위로만 삭제 가능하다.
echo 'find ysoftman and delete line'
echo -e "$temp" | sed "/ysoftman/d"

echo 'delete after line word'
echo -e "$temp" | sed "s/line.*//"

echo 'trim prefix spaces'
echo -e "$temp" | sed "s/^[[:space:]]*//"

echo "remove trailing whitespace"
r=$(printf "hello   " | sed -E "s/[[:space:]]+$//")
echo "...${r}..."
