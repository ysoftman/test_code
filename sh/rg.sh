#!/bin/bash
# https://github.com/BurntSushi/ripgrep (rg) 관련 테스트

# 사용법은 grep 과 비슷, 디폴트로 정규식 패턴을 사용한다.
# 주요 옵션
# -i, --ignore-case
# -g, --glob GLOB ..
# -c, --count
# -t, --type TYPE ...
# -I, --no-filename
# -A, --after-context NUM
# -B, --before-context NUM
# -C, --context NUM
# -N, --no-line-number
# -v, --invert-match
# --hidden, Search hidden files and directories. By default, hidden files and directories are skipped.
# --type-list Show all supported file types and their corresponding globs.

# ysoftman 이 있는 라인 출력(디폴트 파일명도 같이 출력)
rg ysoftman

# ysoftman 이 있는 라인 출력, 파일명 출력 제외
rg ysoftman --no-filename

# .go 파일에서 easy or medium or hard 가 있는 라인 카운트
# -i 대소문자 구별 안함
rg -i "easy|medium|hard" --glob *.go -c
# *.cpp *.go 파일에 대해서
rg -i "easy|medium|hard" -g *.cpp -g *.go -c
# 또는
rg -i "easy|medium|hard" -g *.{cpp,go} -c

# .go 파일에서 easy or medium or hard 가 없는 라인 카운트
# -c 옵션은 zero(0)인 경우 출력되지 않아
# --files-without-match 로 없는 없는 파일을 찾는다.
rg -i "easy|medium|hard" -g *.{cpp,go} --files-without-match

# bbb 는 빼고 출력
echo "aaa
bbb
ccc
ddd
eee" |rg -i -v "bbb|cc"
