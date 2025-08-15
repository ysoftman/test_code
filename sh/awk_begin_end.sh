#!/bin/bash
# ysoftman
# '' 에 사용하는 프로그래밍은 c 언어 문법과 비슷함
# BEGIN/END(대문자) 패턴

cat <<'zzz' >file.txt
name age
alice 21
ryan 30
zzz

awk '
# BEGIN 입력 파일 라인 처리전 실행
BEGIN {
    print "BEGIN (before reading input)"
}
# 입력 파일 라인 처리
{
    # 단어 " " 카운드 로 기록
    for (i = 1; i <= NF; i++) {
        if (NR == 1) {
            s[i] = $i;
        } else {
            s[i] = s[i] " " $i;
        }
    }
}
# END 입력 파일 라인 처리 후 실행
END {
    for (i = 1; s[i] != ""; i++) {
        print s[i];
    }
}' file.txt

rm -rf file.txt
