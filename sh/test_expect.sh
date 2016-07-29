#!/usr/bin/expect 
# ysoftman

# 프로세스 실행
spawn ssh -l ysoftman localhost

# 1초 대기
sleep 1

# password 비슷한 스트링이 나오면
expect "*assword:*"

# 암호 입력, 엔터
send -- "qwer1234\r"

expect eof



