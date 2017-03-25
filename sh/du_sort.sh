#!/bin/bash
# ysoftman
# 현재 디렉토리으 모든 파일에서 가장 큰 10개 출력하기
# du -a(all) -b(bytes)
# sort -n(number) -r(reverse)
# head -10(lines)
du -ab | sort -nr | head -10

