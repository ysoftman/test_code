#!/bin/sh
# ysoftman

# 참고 https://linuxcommand.org/lc3_man_pages/seth.html

# set -x 옵션을 사용하면 현재 스크립트 명령 자체도 stderr 로 확인 할 수 있다.
# set +x 를 하면 다시 비활성화
set -x
fruits="apple banana lemon"
echo "${fruits}" | awk '{print $2}'
set +x

# set -o 옵션명 : 옵션 활성화(on)
# set -o(옵션 출력)설명
# vi 스타일로 line 편집(w,W,b,B,i,a,... 등)
set -o vi
# set 옵션 on/off 상태 표시
set -o
# vi 스타일 비활성화
# bash-> novi 하면 invalid option name 에러
# zsh -> novi 하면 vi off 표시되지만 vi 스타일이 아직 적용되어 있다.
# set -o novi
# emacs 모드 (alt+left,alt+right,.. 등) 를 활성화 해야 한다.
set -o emacs

# zsh 쉘을 사용중에 파일을 오버라이트 하는 경우 다음과 같이 에러가 발생할 수 있다.
echo "aaa" >set_test.txt
echo -e "aaa\nbbb" >set_test.txt
# zsh: file exists: set_test.txt
# 해결방법1
# >! 로 강제 오버라이트 되도록 할 수 있다.
echo -e "aaa\nbbb" set_test.txt >!
# 해결방법2
# 현재 noclobber 상태 파악
set -o | grep noclobber
# noclobber off 로 설정(clobber on)
# bash 에서는 clobber 라는 별도 옵션명이 없어 clobber: invalid option name 에러가 발생한다.
# zsh ./set_test.sh 로 실행한다.
set -o clobber
set -o | grep noclobber
echo -e "aaa\nccc" >set_test.txt

echo "cat set_test.txt"
cat set_test.txt
rm -f ! set_test.txt

# -e 옵션을 설정하면 커맨드 실패시(종료 코드!=0) 바로 종료된다.
# -e 설정 없으면 aaa 명령 실패 이후 echo 명령 계속 진행
# -e 설정하면 aaa 명령 실패 이후 바로 종료
echo "set -e"
set -e
# aaa # aaa: command not found

# -u 설정되지 않은(unset) 변수를 치환할때 에러메시지 발생해서 원인파악을 쉽게할 수 있다.
echo "set -eu"
set -eu
# PH => typo
# export PATH="aaa/bbb:$PH" #  PH: unbound variable
# echo "\$a0:$a0" # a0: unbound variable

# -o pipefail 파이프라인에서 exitcode 를 이어 받아 나중에 파이프라인에서 에러(exitcode!=0)이 있었는지 파악(echo $?)할 수 있다.
echo "set -euo pipefail"
set -euo pipefail
# aaaaa: command not found  로 종료하는데
# set -o pipefail 설정 안했으면 echo $? 가 0
# set -o pipefail 설정했으면 echo $? 가 실패한 종료 코드
# aaaaa | echo

echo "end of test"
