#!/bin/bash
# ysoftman

echo 'read command test'
echo 'input user and password:'

# -s(slient) 사용자 입력을 표시하지 않는다.
# stdin 을 user, password 변수로 저장
# 입력을 공백을 구분 하는 경우
# read -s user password
# 입력을 엔터로 구분 하는 경우
read -s user
read -s password

echo "user->$user"
echo "password->$password"


# 터미널에서 자동 입력 방법1
# echo 'ysoftman' | bash ./read_password_test.sh

# 터미널에서 자동 입력 방법2
# yes 는 특정 키워드를 무한 반복 출력한다.
# yes 'ysoftman' | bash ./read_password_test.sh
