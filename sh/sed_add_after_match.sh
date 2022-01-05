#!/bin/bash
# ysoftman
# sed append after match test

sample="lemon
orange_juice
apple
banana"


# oragne 다음줄에 스트링 추가 - linux(GNU) sed 에서만 가능
if [[ $(uname -s) =~ ^Linux.* ]]; then
    echo "${sample}" | sed '/^orange.*/a ysoftman'
fi

# oragne 다음줄에 스트링 추가 - mac, linux sed 에서 가능
echo "${sample}" | sed '/^orange.*/{a\
ysoftman\
 ysoftman_abc
}'
