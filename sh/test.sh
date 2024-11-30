#!/bin/bash

# test(builtin command): 값 비교  파일 타입 체크
# 비교/체크 결과 true(0) / false(1) 리턴

a="apple"
test $a = "apple"
echo $?

# -z empty variable
test -z "$a"
echo $?

# -f file does exist
test -f "aaa.txt"
echo $?

# not
test ! -f  "aaa.txt"
echo $?

# -d directory does exist
test -d  "aaa"
echo $?
