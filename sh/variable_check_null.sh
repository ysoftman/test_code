#!/bin/bash
# ysoftman

# null(empty) 값 체크
var1=""
# -z -n 을 뒤에 명시하면 "unary operator expected" 가 발생하니 주의!
# -z : null(empty) 인경우 체크
if [ -z "${var1}" ]; then
    echo "var1 is empty"
else
    echo "var1 =" ${var1}
fi

var1=1
# -n : non-zero 값이 있는 경우
if [ -n "${var1}" ]; then
    echo "var1 is non-zero, var1 =" ${var1}
else
    echo "var1 is empty"
fi

# variable set 여부 확인, $없이 변수 이름만  사용
if [ ! -v var2 ]; then
    echo $var2 is not set
else
    printf "$var2 is (%s)", $var2
fi
