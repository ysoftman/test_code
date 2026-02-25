#!/bin/bash
# directory stack
# https://www.gnu.org/software/bash/manual/html_node/Directory-Stack-Builtins.html

# 디렉토리 이동 히스토리 지우기
dirs -c

# 디렉토리 이동 히스토리(스택, 왼쪽이 top으로 현재 최신인 현재디렉토리이다.), 기본 현재디렉토리(~)
dirs

# 스택형식으로 보기(위가 최신)
dirs -p

# 디렉토리 추가, 추가한 디렉토리로 자동 이동한다.
# pushd, popd 를 할때마다 dirs 가 자동 호출된다.
echo 'pushd /'
pushd /
echo 'pushd $HOME'
pushd $HOME

# 최신 디렉토리 제거, 이전 디렉토리로 자동 이동된다.
echo 'popd'
popd

# 참고로 -는 바로 이전 디렉토리($OLDPWD)로 이동한다.
# cd -
