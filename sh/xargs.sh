#!/bin/bash

# xargx -I 옵션로 인자 자리를 나타내는 표시를 설정할 수 있다.
echo ccc | xargs -I{} echo {} "a" "b"
echo ccc | xargs -I{} echo "a" {} "b"
echo ccc | xargs echo "a" "b"

check_process() {
    # -0 는 실제 신호를 보내진 않고 프로세스 존재하면 0(성공), 존재하지 않으면 1(실패) 상태 코드 리턴
    # kill -0 ${1}

    # xargs 사용시 쉘 환경에 따라 kill pid -0 의 순서로 처리될 수 있어 다음과 같이 사용하면 안된다.
    # echo ${1} | xargs kill -0
    # {} 로 위치 표시(마크)
    # echo ${1} | xargs -I{} kill -0 {}
    # _ 로 위치 표시
    echo ${1} | xargs -I_ kill -0 _
}

curr_pid=$$
echo "current_pid:$curr_pid"
check_process $curr_pid
check_process 999999
