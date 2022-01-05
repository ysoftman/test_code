#!/bin/bash
# ysoftman

sample="111-222-333
(111) 222-333
aaa-bbb-123
12-34-56-78"
# bash 에서는 변수를 "" 안에 둬야 newline 이 출력한된다.
# echo "$sample"

# regx1="^[0-9]{3}-[0-9]{3}-[0-9]{3}$"
regx2="^\([0-9]{3}\) [0-9]{3}-[0-9]{3}$"
while read line
do
    echo -n "${line} ==> "
    # =~ 정규식 매칭
    # 주의 정규표현식을 "" 로 묶으면 스트링으로 취급되니 주의!
    if [[ ! ${line} =~ ^[0-9]{3}-[0-9]{3}-[0-9]{3}$ ]] && [[ ! ${line} =~ $regx2  ]]; then
        echo "invalid"
    else
        echo "valid"
    fi
done <<< "${sample}"
