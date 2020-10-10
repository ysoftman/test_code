#!/bin/bash
set -x
echo "$SHLVL"

# 현재 쉘에서 파생된 새로운 쉘이면 shell level 증가

# 비추 표현) 중복 quote 가 복잡
bash -c 'echo $SHLVL; bash -c '" 'echo \$SHLVL;' "' '
# 추천 표현) $ 로 quote escape 사용
bash -c $'echo $SHLVL; bash -c \' echo $SHLVL;\''
