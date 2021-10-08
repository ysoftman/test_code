#!/bin/bash
# ysoftman

# 하위 디렉토리(파일을 제외)만 출력하기
# ls -lR ./ ysoftman : ./ysoftman 디렉토리에서 -l : 리스트, -R : 하위 디렉토리
# | grep ":$" : 앞의 출력 결과를 파이프로 넘겨받아 : 로 끝나는 부분만 출력
# | sed 's/:/\//' : 앞의 출력 결과를 파이프로 넘겨받아 처음 부분을 [subdir] 로 바꿔서(추가) 출력
ls -lR .. | grep ":$" | sed "s/^/[subdir]/"


