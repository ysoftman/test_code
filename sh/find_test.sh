#!/bin/bash
# ysoftman
# jpg 파일들만 검색해서 다른 디렉토리로 복사하기
# find . : 현재 디렉토리를 포함한 하위 디렉토리에서
# -name *.jpg : 확장자가 jpg 인 파일을 찾아
# -exec cp -v {}  /home/ysoftman/ \; : 찾은결과 {} 에서 /home/ysoftman 로 -v 복사상태를 표시하며 복사(-exec 는 항상 공백\; 로 끝나야한다.)
find . -name *.jpg -exec cp -v {} /home/ysoftman/ \;
