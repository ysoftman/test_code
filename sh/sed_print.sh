#!/bin/bash
# ysoftman

# 임시 텍스트 파일 생성
temp='
aaa line1\n
bbb line2\n
ccc line3\n
ddd line4\n
line 5 ysoftman \n
eee line6\n
fff line7\n
ggg line8\n
hhh line9\n
iii line10\n
jjj line11\n
'
echo -e $temp

# 2~4 라인만 출력
# -n 는 sed 가 입력받은 각라인의 에코 출력을 막는다.
# echo "ysoftman" | sed 'p'  는 ysoftman 2번 출력
# echo "ysoftman" | sed -n 'p'  는 ysoftman 1번 출력
# '2,4p' 2~4라인 프린트2~4라인 프린트
echo 'print only line 2~4'
echo -e ${temp} | sed -n "2,4p"
# 3~5 7~8 라인만 출력
# ; 는 조건의 끝을 나타낸다.
echo -e 'print only line 3~5, 7~8'
echo -e ${temp} | sed -n "3,5p;7,8p;"
# ccc ~ ggg 패턴 사이의 내용 출력
echo -e 'print only pattern ccc ~ ggg'
echo -e ${temp} | sed  -n "/^ccc/,/^ggg/p;"
