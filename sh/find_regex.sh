#!/bin/bash
# ysoftman

# 정규식 사용하기
# bsd(OSX)
# -E 를 find 뒤에 명시해야 한다.
if [ $(uname | tr '[:upper:]' '[:lower:]') == 'darwin' ]; then
    find -E . -regex ".*.md$|.*.sh$"
fi

# linux
# -regextype 타임 종류
# findutils-default
# awk
# egrep
# ed
# emacs
# gnu-awk
# grep
# posix-awk
# posix-basic
# posix-egrep
# posix-extended
# posix-minimal-basic
# sed
if [ $(uname | tr '[:upper:]' '[:lower:]') == 'linux' ]; then
    find . -regextype awk ".*.md$|.*.sh$"
fi
