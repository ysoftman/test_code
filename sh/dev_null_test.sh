#!/bin/bash
# ysoftman

touch exist_file
rm -v exist_file


touch exist_file
# stdou /dev/null 로 넘겨 화면에 출력하지 않는다.
rm -v exist_file > /dev/null


touch exist_file
# 2>&1  : stderr 를 stdout 으로 리다이렉션
# stdou, stderr 를 /dev/null 한번에 보낼 수 없다.
# rm -v exist_file not_exist_file 2>&1 /dev/null
# 다음과 같이 /dev/null 뒤에 2>&1 을 명시해서 stdout, stderr 버릴 수 있다.
rm -v exist_file not_exist_file > /dev/null 2>&1
