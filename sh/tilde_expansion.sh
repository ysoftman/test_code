#!/bin/bash
# tilde expansion 테스트
# 참고 http://www.gnu.org/software/bash/manual/html_node/Tilde-Expansion.html

# ~ 는 $HOME 과 같다.
echo $HOME
echo ~

# ~+  는 $PWD 와 같다.
echo $PWD
echo ~+

testfile="~/aaa.txt"
echo ${testfile}
# testfile 은 ~ 는 실행될때 $HOME 을 찾게 된다.
# 따라서 단순 ~/aaa.txt 스트링은 실행되지 않으면 $HOME 경로를 가지고 않은 단순 스트링일 뿐이다.
# No such file or directory 에러가 발생한다.
# touch ${testfile}
# eval 사용하면 ~/aaa.txt 자체를 실행하기 때문에 $HOME 를 알 수 있다.
eval touch ${testfile}
eval ls -ahl ${testfile}
eval rm -f ${testfile}

# 위와 같이 ~ 있는 구분을 매번 eval 하지 않으려면 그냥 $HOME 을 사용하는것이 좋다.
testfile="$HOME/aaa.txt"
touch ${testfile}
ls -ahl ${testfile}
rm -f ${testfile}
