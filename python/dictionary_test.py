# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 딕션어리 테스트

# import os
# import sys
import collections
import operator

# dictionary 테스트
val1 = {}
print("val1 = ", val1)

# key1 = 문자열 추가
val1["key1"] = "string value"
# key2 = 리스트 추가
val1['key2'] = [50, 60, 70]

print("val1 = ", val1)
# print("val1 = key1 -> ", val1["key1"])
# print("val1 = key2 -> ", val1["key2"])

# key3 값이 없으면 추가
if not 'key3' in val1:
    val1['key3'] = "aaaa"
    print("add {key3:aaa}")
# key3 값이 있으면 값 변경
if 'key3' in val1:
    val1['key3'] = "bbb"
    print("add {key3:bbb}")


print("print all in val1", val1)


# key2 의 리스트 값중 0번째 출력
print(val1["key2"][0])

# 정렬 테스트
print("\n")
print("-- dictionary sort test --")
val2 = {1: 30, 2: 20, 3: 10, 4: 40, 5: 50}
print("val2 = ", val2)
for i in val2:
    print("val2[%d] = %d" % (i, val2[i]))

# 내림 차순 정렬
val3 = collections.OrderedDict(
    sorted(val2.items(), key=operator.itemgetter(1), reverse=True))
print(val3)
for i in val3:
    print("val3[%d] = %d" % (i, val3[i]))
