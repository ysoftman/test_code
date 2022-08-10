# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : collection(컨테이너) 중 딕션어리 테스트

# import os
# import sys
import operator

# dictionary 테스트
val1 = {}
print("val1 = ", val1)
val1 = {"aa": 123, "bb": "lemon"}
print("val1 = ", val1)
# ** dictionary key argument 를 파악할 수 있다.
print("val1 = {aa} {bb}".format(**val1))

# key1 = 문자열 추가
val1["key1"] = "string value"
# key2 = 리스트 추가
val1["key2"] = [50, 60, 70]

print("val1 = ", val1)
print("val1['key1'] = ", val1["key1"])
print("val1['key2'] = ", val1["key2"])
# key2 의 리스트 값중 0번째 출력
print("val1['key2'][0] = ", val1["key2"][0])

# 없는 키 인덱싱시 에러로 중단
# print("val1['key32'] = ", val1["key3"])
# get()을 사용하면 None  값으로 에러없이 계속 실행가능
print("val1.get('key3'] = ", val1.get("key3"))
print("val1.keys() = ", val1.keys())

# key3 값이 없으면 추가
if not "key3" in val1:
    val1["key3"] = "aaaa"
    print("add {key3:aaa}")
# key3 값이 있으면 값 변경
if "key3" in val1:
    val1["key3"] = "bbb"
    print("add {key3:bbb}")
print("print all in val1", val1)

# key3 요소 삭제
del val1["key3"]
print("del val1['key3']\nprint all in val1", val1)

# 정렬 테스트
print("\n")
print("-- dictionary sort test --")
val2 = {1: 30, 2: 20, 3: 10, 4: 40, 5: 50}
print("val2 = ", val2)
for i in val2:
    print("val2[%d] = %d" % (i, val2[i]))

# 내림 차순 정렬
val3 = collections.OrderedDict(
    sorted(val2.items(), key=operator.itemgetter(1), reverse=True)
)
print(val3)
for i in val3:
    print("val3[%d] = %d" % (i, val3[i]))
