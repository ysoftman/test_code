#!/bin/bash
# interactive shell이 아닌 경우(bash aaa.sh)에도 alias 가 작용
# 참고로 shopt 는 bash built-in 명령으로 zsh 에서는 사용할 수 없는 명령이다.
shopt -s expand_aliases

# alias 설정시 다음과 같이 명령어가 계속 이어지는중을 표시하기 위해 \ 를 사용한 경우
alias echoysoftman1='echo ysoftman1 &&
echo ysoftman2 &&
echo \
-e ysoftman3'

echo "---echoysoftman1---"
echoysoftman1

# zsh 에선 다음과 같이 멀티라인 처리되어 다음과 같이 출력
# ysoftman1
# ysoftman2
# ysoftman3

# bash 에선 \ 를 다르게 인식해서 에러 발생
# ysoftman1
# ysoftman2
# bash: echoysoftman: command not found

# 해결방법 1
# 모든 커멘드를한줄로 처리하면 zsh, bash 둘 잘 작동한다.
alias echoysoftman2='echo ysoftman1 && echo ysoftman2 && echo -e ysoftman3'

echo "---echoysoftman2---"
echoysoftman2

# 해결방법 2
# 또는 커맨드 하나당 한줄로해도 잘 동작한다. 
alias echoysoftman3='echo ysoftman1 &&
echo ysoftman2 &&
echo -e ysoftman3'

echo "---echoysoftman3---"
echoysoftman3
