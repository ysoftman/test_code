# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : enumerate 테스트

l = ["apple", "lemon", "orange"]
i = 0
for v in l:
    print("l[{}] = {}".format(i, v))
    i = i + 1


print("using enumerate() => index and value")
# enumerate함수를 사용하면 카운터(index)도 리턴 받아 사용 할 수 있다.
for index, value in enumerate(l):
    print("l[{}] = {}".format(index, value))

print("using enumerate() => tuple")
for ele in enumerate(l):
    print(ele)

print("using enumerate() => into a list of tuple")
print(list(enumerate(l)))
