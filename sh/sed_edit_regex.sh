#!/bin/bash

temp="aaaabbbbcccc"
echo $temp

# a -> z 모두 변경
echo $temp | sed -e 's/a/z/g'

# -E or -r 으로 정규표현식 사용
# a or b 모두 z 로 변경
# echo $temp | sed -r 's/(a|b)/z/g'
echo $temp | sed -E 's/(a|b)/z/g'

# a or b 모두 z 로 변경뒤에 () 와 첫번째 매칭되는것 추가
echo $temp | sed -E 's/(a|b)/z\1/g'

#a or b 모두 z 로 변경뒤에() () () 각각 1~3번째 매칭된것 추가
echo $temp | sed -E 's/(a)|(b)|(c)/z\1\2\3/g'

temp="aaaa/bbbb/cccc"
# /검색식/치환문자열/ 에서
# 검색식에서 . 는 정규표현식이라 literal . 는 \. 로 이스케이프해야 한다.
# 치환문자열에서는 . 자체가 일반 문자열로 이스케이프 없이 . 로 사용하면 된다.
# / 구분자 대신 | 사용하여 가독성을 높인다.
echo $temp | sed -E 's|cccc|.|g'
