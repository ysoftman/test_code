#!/bin/bash
# ysoftman

lemon="lemon_juice"
# `` 으로 명령 실행 후 응답 받기
# `` 안에 `` 를 사용하려면 이스케이프가 필요하다.
# $lemon 자체를 literal 로 출력하려면 '' 로 감싸야한다.
output=`echo "ysoftman_99s" \`echo $lemon '\$lemon'\``
echo "\${output}:"${output}

# 위왜 같은 불편함으로 $() 으로 명령 실행 후 응답 받기를 권고한다.
output=$(echo "ysoftman_99s" $(echo $lemon \$lemon))
echo "\${output}:"${output}

