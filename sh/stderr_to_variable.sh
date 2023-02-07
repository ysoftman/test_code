#!/bin/bash

shell_name=""
if [[ $(ps -o command $$) == *"bash"* ]]; then
    shell_name="bash"
elif [[ $(ps -o command $$) == *"zsh"* ]]; then
    shell_name="zsh"
fi
echo "\$shell_name:" $shell_name

if [[ $shell_name == "zsh" ]]; then
    # zsh 에서는 sh_word_split 활성화야 공백,엔터로 구분할 수 있다.
    setopt sh_word_split
fi

###################

# $() 실행시 stdout,stderr 은 보이지 않고 변수로 담기
temp=$(ls not_exist_file 2>&1 /dev/null 2>&1)
# echo $temp

if [[ $shell_name == "zsh" ]]; then
    # zsh 라면 다음과 같이 {} 를 사용할 수도 있다.
    temp=$({ ls not_exist_file | rg -i "no such" } 2>&1)
    echo $temp
fi
