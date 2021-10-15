#!/bin/bash
# ysoftman

var1="aaa"
var2="bb"
var3=${var1}${var2}
echo '${var1}:'${var1}
echo '${var2}:'${var2}
echo '${var3}:'${var3}

# 변수 길이 파악
echo '${#var3}:'${#var3}
if [[ ${#var3} == 5 ]]; then
    echo "len(${var3}) == 5"
fi
