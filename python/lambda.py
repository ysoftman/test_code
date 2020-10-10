# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : lambda test


def add(a):
    return a+1


print(add(9))

# 람다 문법
# (lambda 파라미터 : 표현)(파라미터값)
# 위를 람다식으로 바꾸면
print((lambda a: a+1)(9))


def a(a):
    if a == "aaa":
        return "ok"
    else:
        return "no"


print(a("aaa"))

# 위를 if 를 포함하는 람다식으로 바꾸면
# 참값 if 표현식 else 참이아닌값
print((lambda a: "ok" if a == "aaa" else "no")("aaa"))
