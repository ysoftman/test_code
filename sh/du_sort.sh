#!/bin/bash
# ysoftman
# 현재 디렉토리으 모든 파일에서 가장 큰 10개 출력하기
# du -a(all) -k(kbyte) 리눅스에서는 -b(bytes) 도 사용가능
# sort -n(number) -r(reverse)
# head -10(lines)
du -ak | sort -nr | head -10

