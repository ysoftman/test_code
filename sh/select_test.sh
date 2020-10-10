#!/bin/bash
# ysoftman
# select test

list=("lemon" "apple" "orange")
# 리스트 모든 원소 출력
echo "list = ${list[@]}"

# select 에서 입력시 표시되는 프롬프트
PS3='select item: '
select choice in "${list[@]}"; do
    # 번호가 표시되고 번호를 입력(선택)한다
    case $choice in
        "lemon")
            echo 'select lemon'
            break
            ;;
        "apple")
            echo 'select apple'
            break
            ;;
        "orange")
            echo 'select orange'
            break
            ;;
        *)
            echo 'select none!'
            # break 가 없으면 계속 입력을 받는다.
            ;;
    esac
done

# 번홉 입력 없이 대기 없이 사용시
# echo '1' | bash ./select_test.sh
