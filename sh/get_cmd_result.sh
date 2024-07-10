#!/bin/bash
# ysoftman
# shell 명령 실행 후 결과 변수로 저장
# man bash 참고
# backquote 보다는 $() 을 쓰는것이 좋다.

myname="_ysoftman_"

# 방법1 `command`
var=`echo ${myname}`
echo ${var}
# 방법2 $(command)
var=$(echo ${myname})
echo ${var}

# ``는 오래된 방법으로 \ 를 표시하기 위해선 두번을 써야하는 불편함이 있다.
var=`echo \\${myname}`
echo ${var}
var=$(echo \${myname})
echo ${var}

# ``안에서 중첩된 명령을 사용하기 위해선 \ 를 사용하기 때문에 가독성이 떨어진다.
var=`echo lemon \`echo apple\` `
echo ${var}
var=$(echo lemon $(echo apple))
echo ${var}

aa() {
    echo "ysoftman"
}
# 함수 호출시에도 사용한다.
echo "call aa():" `aa`
echo "call aa():" ` aa `
echo "call aa():" $(aa)
echo "call aa():" $( aa )
