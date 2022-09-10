#!/bin/bash
# ysoftman

touch exist_file
rm -fv exist_file

touch exist_file
# stdout /dev/null 로 넘겨 화면에 출력하지 않는다.
rm -fv exist_file > /dev/null

touch exist_file
# 2>&1 : stderr 를 stdout 으로 리다이렉션
# 아래와 같이하면과 stdout, stderr 를 /dev/null 한번에 보낼 수 없다.
# rm -fv exist_file not_exist_file 2>&1 /dev/null
# 다음과 같이 /dev/null 뒤에 2>&1 을 명시해서 stdout, stderr 리다이렉트할(버릴) 수 있다.
# fd(/dev/null)이 먼저 파악되어 stdout > fd 로 갈 수 있도록 한 상태에서, stderr(2) > stdout(1) 로 보내야 한다.
rm -fv exist_file > /dev/null 2>&1
# rm -f 옵션을 사용하면 없는 파일도 에러메시지 없이 동작해서 뺏음
rm -v not_exist_file > /dev/null 2>&1
