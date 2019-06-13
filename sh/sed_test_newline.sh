#!/bin/bash
# ysoftman

# && -> newline
# linux
# \n 로 치환한다.
echo "ysoftman&&lemon" | sed -e 's/&&/\n/'

# linux, mac
# 실제 다음처럼 라인을 추가하고 닫아야한다
echo "ysoftman&&lemon" | sed -e 's/&&/\
/'

# linux, mac
# $....는 bash-ism 표현으로 \n 을 뉴라인으로 변환한다.
echo "ysoftman&&lemon" | sed $'s/&&/\\\n/'


# delete newline
# sed 에선 newline 을 삭제 sed 's/\n//' 로 할 수 없다.
# sed ':a;N;$!ba;s/\n//g'\
# 로 사용해야 하는데 mac에선 안된다.
# 그래서 tr을 쓰라고한다.
# tr -d '\n' 를
# 참고 http://sed.sourceforge.net/sedfaq5.html#s5.10
echo "-----"
echo "lemon
apple
orange" | tr -d '\n'
