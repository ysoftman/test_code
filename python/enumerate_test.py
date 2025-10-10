# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : enumerate 테스트

fruits_list = ["apple", "lemon", "orange"]
i = 0
for v in fruits_list:
    print("l[{}] = {}".format(i, v))
    i = i + 1


print("using enumerate() => index and value")
# enumerate함수를 사용하면 카운터(index)도 리턴 받아 사용 할 수 있다.
for index, value in enumerate(fruits_list):
    print("fruits_list[{}] = {}".format(index, value))

print("using enumerate() => tuple")
for ele in enumerate(fruits_list):
    print(ele)

print("using enumerate() => into a list of tuple")
print(enumerate(fruits_list))
print(list(enumerate(fruits_list)))
