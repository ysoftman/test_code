#!/bin/bash
# ysoftman
# IFS(Input Field Separators) test

# IFS 기본은 공백
echo "\${IFS}:" ${IFS}
for v in `cat variable_ifs.txt`
do
    # 요소를 공백으로 구분해서 출력
    echo ${v}
done

# 입력 필드 구분자를 뉴라인으로 명시, 기본은 스페이스
IFS=$'\n'
echo "\${IFS}:" ${IFS}
for v in `cat variable_ifs.txt`
do
    # 요소를 뉴라인으로 구분해서 출력
    echo ${v}
done
