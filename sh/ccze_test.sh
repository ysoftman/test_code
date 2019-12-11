#!/bin/bash
# ccze 로그 컬러출력 테스트
# yum install ccze
# apt-get install ccze
# brew install ccze

# 파일들 첫 4096바이트 hex+ascii 출력
# ccze 컬러로 출력
# -o nolookups 사용자이름 서비스 이름등 많은 정보를 lookup 하면 느리기 때문에 lookup 은 꺼둔다.
find /usr/local/bin | xargs head -c 4096 | hexdump -C | ccze -A -o nolookups
