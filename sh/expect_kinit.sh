#!/usr/bin/expect
# ysoftman
# bash 가 아닌  expect 로 실행해야 한다.

# kint 암호 자동 입력
# 참고로 linux 에선 echo  파이프로 처리할 수 있다.
# echo "aaa\!23" | kinit ysoftman

# expect 환경에서 프로세스 실행
spawn kinit ysoftman

# password 비슷한 스트링이 나오면
expect "*password*"

# mac 에선 newline \r (carriage return)
# linux 에선 newline \n (line feed)
# windows 에선 newline \r\n (carriage return + line feed)
send "aaa\!23\r"

# spawn 프로세스 닫기
expect eof
