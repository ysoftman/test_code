#/bin/sh
# ysoftman

# set -x 옵션을 사용하면 현재 스크립트 명령 자체도 stderr 로 확인 할 수 있다.
set -x
fruits="apple banana lemon"
echo "${fruits}" | awk '{print $2}'


# zsh 쉘을 사용중에 파일을 오버라이트 하는 경우 다음과 같이 에러가 발생힌다.
echo "aaa" > set_test.txt
echo "aaa" > set_test.txt
# zsh: file exists: set_test.txt
# 해결방법1
# >! 로 강제 오버라이트 되도록 할 수 있다.
echo "aaa" >! set_test.txt
# 해결방법2
# 현재 noclobber 상태 파악
set -o | grep noclobber
# noclobber off 로 설정(clobber on)
# clobber: invalid option name 에러가 발생한 zsh ./set_test.sh 로 실행한다.
set -o clobber
echo "aaa" > set_test.txt

# 참고
# set -o 옵션명 : 옵션 활성화(on)
# set -o no옵션명 : 옵션 비활성화(off)
# set -o(옵션 출력)설명 http://linuxcommand.org/lc3_man_pages/seth.html
