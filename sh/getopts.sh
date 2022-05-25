#!/bin/bash
# getopts 명령(builtin) 테스트
# 실행 예
# short(한글자) 옵션명 -a -b
# long(여러자) 옵션명 --ccc
# bash ./getopts.sh -a lemon -b apple -c orange --ccc ysoftman

# 다음 처리되어야 옵션 index
# echo ${OPTIND}
# 옵션 값
# echo ${OPTARG}

# : 로 끝나면 arg값이 있는 경우 옵션이다.
# getopts 는 short 옵션만 처리가능하다.
while getopts "a:b:c" opt; do
    case ${opt} in
        a|c)
            echo "a|c ${OPTIND} ${OPTARG}"
            ;;
        'b')
            echo "b ${OPTIND} ${OPTARG}"
            ;;
        *)
            echo "undefined option ${OPTIND} ${OPTARG}"
            exit 1
            ;;
    esac
done
