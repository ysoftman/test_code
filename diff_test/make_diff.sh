#!/bin/bash
# ysoftman
# diff 출력하기
# -u --unified 포맷 통일, 한쪽에는 없는 부분을 있는것 처럼 표시
# -r --recurisve 하위 디렉토리에 있는 파일도 비교
# -N --new-fie 한쪽에는 없는 파일이면 있는것 처럼 표시
/usr/bin/diff -urN a.c b.c

