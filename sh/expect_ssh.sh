#!/usr/bin/expect 
# ysoftman
# bash 가 아닌  expect 로 실행해야 한다.

# expect 환경에서 프로세스 실행
spawn ssh -l ysoftman localhost

# 1초 대기
sleep 1

# password 비슷한 스트링이 나오면
expect "*assword:*"

# 암호 입력, 엔터
# -- 옵션의 끝(더이상의 옵션은 없음을 의미)
send -- "qwer1234\r"

# spawn 프로세스 닫기
expect eof
