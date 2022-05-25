#!/bin/bash
# ysoftman
# 사용자 함수 테스트

if [ $# != 2 ]; then
    echo "argc != 2"
    exit 1
fi

main_arg1=$1
main_arg2=$2
echo "main_arg1 =" ${main_arg1}
echo "main_arg2 =" ${main_arg2}

function testfunc0 {
    echo "testfunc0()...$1 $2"
}

# 사용자 함수 파마리터도 $# $1 $2 .. 으로 받는다.
# function 을 명시하지 않아도 된다.
testfunc1() {
    if [ $# != 2 ]; then
        echo "func_argc($#) != 2"
        exit 1
    fi
    func_arg1=$1
    func_arg2=$2

    # echo 로 출력 한 값은 caller 에서 받아 사용할 수 있다.
    echo "func_arg1 =" ${func_arg1}
    echo "func_arg2 =" ${func_arg2}

    # return 은 종료 상태 코드로 caller 에게 전달 되지 않는다.
    return 0
}

# 함수 호출
testfunc0 lemon 123
testfunc1 ${main_arg1} ${main_arg2}

# 함수 호출 후 stdout 값을 리턴으로 사용한다.
ret=$(testfunc1 ${main_arg1} ${main_arg2})
echo "testfunc1 returns
$ret"
