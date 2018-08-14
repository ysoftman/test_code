#!/bin/bash
echo 'read command test'
echo 'input passwrd:'

# -s(slient) 사용자 입력을 표시하지 않는다.
# password 변수로 stdin 저장
read -s password

echo $password