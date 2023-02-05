#!/bin/bash
# ysoftman
# IFS(Input Field Separators) test

set -e

# IFS 기본은 공백
echo "\${IFS}:" ${IFS} "(space)"
for v in `cat variable_ifs.txt`
do
    # 요소를 공백으로 구분해서 출력
    echo ${v}
done

# 입력 필드 구분자를 뉴라인으로 명시, 기본은 스페이스
# \n 를 하나의 문자로 취급해야 하기 때문에 $를 붙여 표현
IFS=$'\n'
echo "\${IFS}:" ${IFS} "(newline)"
for v in `cat variable_ifs.txt`
do
    # 요소를 뉴라인으로 구분해서 출력
    echo ${v}
done


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

IFS=' '
list="lemon apple banana"
echo $list
echo "****"
# for item in ${list}; do
for item in ${list}; do
    echo "item:$item"
done

if [[ $shell_name == "zsh" ]]; then
    # sh_word_split 비활성화
    unsetopt sh_word_split
fi
