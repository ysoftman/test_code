#!/bin/bash
# ysoftman
# 머신 전체 디스크 사용량 -h(--human-readable) 로 보기
df -h

# 현재 디렉토리(하위포함)에서 차지하는 디스크 사용량 -s(--summarize) 보기
du -sh

# 현재 디렉토리에서 파일 및 하위 디렉토리의 디스크 사용량 보기
du -sh *

# 현재 디렉토리으 모든 파일에서 가장 큰 10개 출력하기
# du -a(all) -k(kbyte) 리눅스에서는 -b(bytes) 도 사용가능
# sort -n(number) -r(reverse)
# head -10(lines)
du -ak | sort -nr | head -10
