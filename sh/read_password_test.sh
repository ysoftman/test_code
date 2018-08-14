#!/bin/bash
# ysoftman

echo 'read command test'
echo 'input password:'

# -s(slient) 사용자 입력을 표시하지 않는다.
# password 변수로 stdin 저장
read -s password

echo $password


# 터미널에서 자동 입력 방법1
# echo 'ysoftman' | bash ./read_password_test.sh

# 터미널에서 자동 입력 방법2
# yes 는 특정 키워드를 무한 반복 출력한다.
# yes 'ysoftman' | bash ./read_password_test.sh
