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
    echo "var1 is non-zone, var1 =" ${var1}
else
    echo "var1 is empty"
fi
