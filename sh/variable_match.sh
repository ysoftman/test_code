#!/bin/bash
# ysoftman

# 매칭 부분 제거
var1="10.10.10.1:111 10.10.10.2:222 10.10.10.3:333"
cnt=0
for v in ${var1}; do
    # 변수 뒤에서부터 :* 매칭부분 제거
    ip=${v%:*}
    # 변수 앞에서부터 *: 매칭부분 제거
    port=${v#*:}
    echo "var1[$cnt] = ip-> ${ip} , port-> ${port}"
    (( cnt+=1 ))
done
echo "var1 = ${var1}"
