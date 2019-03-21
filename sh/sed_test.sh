#!/bin/bash
# ysoftman

TEMP_FILE="sed_test.tmp"


##########


# 테스트를 위한 임시 파일 생성
cat > ${TEMP_FILE} << zzz
lemon apple orange lemon
banana mango lemon
zzz
# -e 은 editing command 를 추가할때 사용한다.
sed -e 's/lemon/aaa/g' -e 's/aaa/bbb/g' ${TEMP_FILE}
# 또는 다음과 같이 라인으로 구분해서 여러개의 editing command 명시할 수 있다.
sed 's/lemon/aaa/g
s/aaa/bbb/g
s/bbb/ccc/g
s/ccc/ddd/g
s/ddd/eee/g
' ${TEMP_FILE}
# -i 는 stdin 과 사용할 수 없어 파이프를 사용하지 못한다.
# -i 확장자명시하면 수정된 결과를 원본파일.확장자 파일로 저장한다.
# /g global 을 사용해야 라인에서 모든 매치되는 경우를 변경한다.
sed -i '.bak' 's/lemon/aaa/g' ${TEMP_FILE}
# 임시 파일 삭제
rm -f ${TEMP_FILE}
rm -f ${TEMP_FILE}.bak


##########


# 하위 디렉토리(파일을 제외)만 출력하기
# ls -lR ./ ysoftman : ./ysoftman 디렉토리에서 -l : 리스트, -R : 하위 디렉토리
# | grep ":$" : 앞의 출력 결과를 파이프로 넘겨받아 : 로 끝나는 부분만 출력
# | sed 's/:/\//' : 앞의 출력 결과를 파이프로 넘겨받아 처음 부분을 [subdir] 로 바꿔서(추가) 출력
ls -lR .. | grep ":$" | sed "s/^/[subdir]/"
# 테스트를 위한 임시 파일 생성
cat > ${TEMP_FILE} << zzz
this string data for test.
ysoftman
123456789
zzz
# sed_test.txt 내용에서 ysoftman 찾으면 출력 끝내기
cat sed_test.txt | sed "/ysoftman/q"
# 임시 파일 삭제
rm -f ${TEMP_FILE}


##########


# 임시 텍스트 파일 생성
echo 'aaa line1
bbb line2
ccc line3
ddd line4
eee line5
fff line6
ggg line7
hhh line8
iii line9
jjj line10' > ${TEMP_FILE}
# 라인2만 삭제하고 출력
# d 삭제
echo 'delete line 2 and print'
cat ${TEMP_FILE} | sed  "2d;"
# 2~4 라인만 출력
# -n sed 가 입력받은 각라인의 에코 출력하는것을 막는다. 조건에 해당하는것만 출력하도록 한다.
# '2,4p' 2~4라인 프린트2~4라인 프린트
echo 'print only line 2~4'
cat ${TEMP_FILE} | sed -n "2,4p"
# 3~5 7~8 라인만 출력
# ; 는 조건의 끝을 나타낸다.
echo 'print only line 3~5, 7~8'
cat ${TEMP_FILE} | sed -n "3,5p;7,8p;"
# ccc ~ ggg 패턴 사이의 내용 출력
echo 'print only pattern ccc ~ ggg '
cat ${TEMP_FILE} | sed  -n "/^ccc/,/^ggg/p;"
# ccc ~ ggg 패턴 사이의 내용만 삭제하고 출력
echo 'delete pattern ccc ~ ggg and print'
cat ${TEMP_FILE} | sed "/^ccc/,/^ggg/d;"
# 임시 파일 삭제
rm -f ${TEMP_FILE}


##########


# @뒤로 삭제
# Substitute 형식 : s/regular expression/replacement/flag
out=`(echo "ysoftman @open (12345)" | sed "s/@.*$//")`
echo "$out"___result
# 공백@ 뒤로 삭제
out=`(echo "ysoftman @open (12345)" | sed "s/ @.*$//")`
echo "$out"___result
# 컬문자의 경우
reset_color='\033[0m'
green='\033[0;32m'
# 공백이 아닌 컬러 문자가 포함되어 공백 뒤 삭제가 안된다.
echo -e "ysoftman ${green}color${reset_color} string " | sed "s/ color.*$//"
# 중간에 컬러 문자를 제거해줘야 한다.
echo -e "ysoftman ${green}color${reset_color} string " | sed "s,$(printf '\033')\\[[0-9;]*[a-zA-Z],,g" | sed "s/ color.*$//"
