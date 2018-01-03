# 다음과 같이 alias \ 가 들어간 경우
alias echoysoftman='echo ysoftman && \
echo ysoftman'

# zsh 에선 다음과 같이 멀티라인 처리되어 다음과 같이 출력
ysoftman
ysoftman

# bash 에선 \ 를 커맨드로 인식해서 에러 발생
ysoftman
bash: echoysoftman: command not found

# \ 문자 빼면 zsh, bash 둘 잘 작동한다.
alias echoysoftman='echo ysoftman &&
echo ysoftman'
