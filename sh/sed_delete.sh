#!/bin/bash
# ysoftman

temp='
aaa line1\n
bbb line2\nccc line3\n
ddd line4\n
line 5 ysoftman \n
eee line6\n
fff line7\nggg line8\n
hhh line9\n
iii line10\n
jjj line11\n
line 12 ysoftman \n
'

echo -e $temp
# d 삭제
# 라인2만 삭제하고 출력
echo 'delete line 2 and print'
echo -e $temp | sed  "2d;"

# ccc ~ ggg 패턴 사이의 내용만 삭제하고 출력
echo 'delete pattern ccc ~ ggg and print'
echo -e $temp | sed "/^ccc/,/^ggg/d"

echo 'find ysoftman and delete'
echo -e $temp | sed "s/ysoftman//g"

echo 'find ysoftman and delete line'
echo -e $temp | sed "/ysoftman/d"
