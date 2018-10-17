#/bin/sh
# ysoftman

# set -x 옵션을 사용하면 현재 스크립트 명령 자체도 stderr 로 확인 할 수 있다.
set -x
fruits="apple banana lemon"
echo "${fruits}" | awk '{print $2}'
