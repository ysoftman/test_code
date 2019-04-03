# github api 사용하기

```bash
# 사용자의 모든 저장소 정보
curl -s --user "ysoftman:password123" https://api.github.com/user/repos

# 해당 저장소에서 사용되는 언어별 사용 bytes
curl -s --user "ysoftman:password123" https://api.github.com/repos/ysoftman/test_code/languages

# github api 를 이용해 이슈 정보 파악하기
# https://developer.github.com/v3/issues/
# 이슈번호 : 10
curl -s --user "ysoftman:password123" https://api.github.com/repos/ysoftman/test_code/issues/10

# git release 정보 파악하기
# https://developer.github.com/v3/repos/releases/
curl -s --user "ysoftman:password123" https://api.github.com/repos/ysoftman/test_code/releases
```

## git subprogram(custom) command 사용하기

```bash
# git-명령이름 으로 실행할 파일을 만들고
vi git-ysoftman

#!/bin/bash
echo "ysoftman's custom git command test"
chmod +x git-ysoftman

# 다음과 같이 명시하면 현재 위치에서는 커스텀 명령이 실행된다.
git ysoftman

# 만약 현재경로에서 git ysoftman 실행시 다음과 같은 에러가 발생하면
git: 'ysoftman' is not a git command.

# GIT_EXEC_PATH 환경변수를 현재디렉토리로 설정해 실행한다.
# https://git-scm.com/book/ko/v2/Git%EC%9D%98-%EB%82%B4%EB%B6%80-%ED%99%98%EA%B2%BD%EB%B3%80%EC%88%98
GIT_EXEC_PATH=$(pwd) git ysoftman
# 또는
git --exec-path=. br
# 또는
# bash, zsh 등에서 git-subcommand 를 현재 디렉토리에서 실행하기 위해
# PATH 환경변수 처음이나 마지막에 구분자(:)가 있거나
# PATH 중간에 :: 부분이 있어야 한다.
# ./a.sh 대신 a.sh 실행 가능해야 한다.
export PATH=$PATH:
# 또는
export PATH=:$PATH
# 또는
export PATH=::$PATH

# 참고
# 다음 옵션으로 현재 사용중인 command 경로를 알 수 있다.
git --exec-path

# git 명령이 어떻게 수행되는지 trace 해볼 수 있다.
# 2값이상을 주면 open file descriptor 번호로 파악해서 해당 파일로 trace를 기록한다.
GIT_TRACE=2 git ysoftman
```

### git-br

브랜치명이 xxx-이슈번호 인 경우, github 의 이슈타이틀을 파악해서 현재 로컬 브랜치에 정보에 같이 표시한다.

- 예시

```bash
# test_code 에 테스트를 위한 이슈(10번)를 만들어두었음
# ysoftman-10 를 만들어 본다.
git co -b ysoftman-10
# git-br 에 password 명시하고 실행
git br
```
