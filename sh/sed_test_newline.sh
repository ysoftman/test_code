#!/bin/bash
# ysoftman

# && -> newline
# linux
# \n 로 치환한다.
echo "ysoftman&&lemon" | sed -e 's/&&/\n/'

# linux, mac
# 실제 다음처럼 라인을 추가하고 닫아야한다
echo "ysoftman&&lemon" | sed -e 's/&&/\
/'

# linux, mac
# $....는 bash-ism 표현으로 \n 을 뉴라인으로 변환한다.
echo "ysoftman&&lemon" | sed $'s/&&/\\\n/'


# delete newline
# sed 's/\n//' 로 newline 을 제거할 수 없다.
# sed ':a;N;$!ba;s/\n//g'\
# 로 사용해야 하는데 mac에선 안된다.
# 그래서 tr을 쓰라고한다.
# tr -d '\n' 를
# 참고 http://sed.sourceforge.net/sedfaq5.html#s5.10
echo "-----"
echo "lemon
apple
orange" | tr -d '\n'

echo "\n"

colorls_path=$(which colorls)
# echo $colorls_path
file_colorls="${colorls_path##*/}"
# echo $file_colorls
if [[ $file_colorls == "colorls" ]]; then
    # colorls *.txt 출력은 newline 중복(\n\n)된다.
    # sed 로 두번재 newline(\n 있고 아무것도 없는 줄) 지우기
    echo "remove \n\n using sed '/^$/d'"
    colorls *.txt | sed -e '/^$/d'
    echo "remove \n\n using tr -s '\n'"
    # 또는 tr -s (Squeeze)옵션으로 중복되는 문자를 하나로 줄인다.
    colorls *.txt | tr -s '\n'
fi
