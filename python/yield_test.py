# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : yield test
import time


def fruit():
    r = []
    for i in ["apple", "orange", "lemon"]:
        time.sleep(0.5)
        r.append(i)
    return r


print(fruit())


def fruit_yield():
    for i in ["apple", "orange", "lemon"]:
        time.sleep(0.5)
        # generator(필요시 생성되는 객체)로 i 를 루프때마다 리턴한다.
        yield i


# <generator object fruit_yield at 0x...> 가 리턴된다.
print(fruit_yield())

# yield 로 리턴되는 값을 출력
for i in fruit_yield():
    print(i)
