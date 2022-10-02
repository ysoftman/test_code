#!/bin/sh
# ysoftman
# eval 는 argument 를 현재 쉘에서 실행하고 그 결과를 리턴한다.

# example2
echo "aa=ysoftman"    # 그냥 문자열 출력으로 aa 값이 설정되지 않음
echo "echo aa=ysoftman, " $aa
eval "aa=ysoftman"    # aa=ysoftman 를 쉘에서 실행했기 때문에 aa 에 값이 설정됨
echo "eval aa=ysoftman, " $aa


# example2
var1="ysoftman"
var2="$"var1
echo $var2          # $val1 라는 문자열로 출력한다.
eval "echo $var2"   # 문자열에 포함된 변수(또는 명령)를 쉘에 의해 var1변수로 처리하여 var1변수의 값을 출력하게 된다.


# example3
# $(echo "cat eval.sh | grep example") # | 문자가 있으면 에러
eval $(echo "cat eval.sh | grep example") # eval 로 | 를 평가해서 실행된다.
