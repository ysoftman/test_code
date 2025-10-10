# -*- coding: utf-8 -*-
# python2 테스트
__author__ = "ysoftman"

import os

# 현재 디렉토리 파악
print("os.curdir:", os.curdir)


# 함수 테스트
def add(val1, val2):
    return val1 + val2


result = add(1, 2)
print("add(1,2) result:", result)

# 문자열 테스트
var1 = "string1"
var2 = "string2"
var3 = var1 + " " + var2
print(var3)

var1 = "123"
print(var1.isdigit())
