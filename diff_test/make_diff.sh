#!/bin/bash
# ysoftman
# diff 출력하기
# -u --unified 포맷 통일, 한쪽에는 없는 부분을 있는것 처럼 표시
# -r --recursive 하위 디렉토리에 있는 파일도 비교
# -N --new-file 한쪽에는 없는 파일이면 있는것 처럼 표시
/usr/bin/diff -urN a.c b.c

# 참고
# diff 결과를 파일로 만들고 /usb/bin/path 를 사용해서 원보파일에 변경을 적용할 수 있다.

