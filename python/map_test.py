# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : map test


def myfunc(fruit):
    return "i like " + fruit


mylist = ['apple', 'banana', 'lemon', 'orange', 'strawberry']

# 내장함수 map 사용하기
# map object 의 메모리 주소만 출력된다.
print(map(myfunc, mylist))
print(list(map(myfunc, mylist)))
