#!/bin/bash

# placeholder -> {}
# find 결과를 {} 로 받기
find . -name "placeholder.sh" -exec echo "aaa -> {}" \;

# {} 를 원하는 값으로 변경해 실행하기
str="apple_lemon_orange"
cmd='echo "{}" && echo "{}"'
realcmd=$(echo $cmd | sed "s/{}/$str/g")
eval $realcmd
