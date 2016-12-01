#!/bin/sh
# ysoftman
# 커맨드 실행하기
cmd="ll"

checkexitcode() {
    cmd=$1
    echo "command="$cmd
    ${cmd}
    # ? 는 가장 최근 실행한 명령의 종료 코드를 저장하고 쉘 내장 변수 이다.
    echo "exitcode="$?
    if [[ $? != 0 ]]; then
        echo "fail"
    fi
}

checkexitcode "asdf"  # 찾을 수 없는 명령어로 실패함
checkexitcode "ls -1" # 명령 실행 성공
