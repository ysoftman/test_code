# alias 설정시 다음과 같이 명령어가 계속 이어지는중을 표시하기 위해 \ 를 사용한 경우
alias echoysoftman='echo ysoftman1 &&
echo ysoftman2 &&
echo \
-e ysoftman3'

# zsh 에선 다음과 같이 멀티라인 처리되어 다음과 같이 출력
ysoftman1
ysoftman2
ysoftman3

# bash 에선 \ 를 다르게 인식해서 에러 발생
ysoftman1
ysoftman2
bash: echoysoftman: command not found

# 해결방법 1
# 모든 커멘드를한줄로 처리하면 zsh, bash 둘 잘 작동한다.
alias echoysoftman='echo ysoftman1 && echo ysoftman2 && echo -e ysoftman3'

# 해결방법 2
# 또는 커맨드 하나당 한줄로해도 잘 동작한다. 
alias echoysoftman='echo ysoftman1 &&
echo ysoftman2 &&
echo -e ysoftman3'
