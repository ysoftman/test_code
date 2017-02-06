#!/bin/bash
# ysoftman

# rename 설치(맥의 경우)
# sudo  brew install rename

# 현재 디렉토리내의 모든.txt 확장자 파일을 .log 로 바꾸기(정규 표현식 사용하는 경우)
rename 's/\.txt/\.log/' *.txt
