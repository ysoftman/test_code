# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 클래스 테스트

# import os
# import sys


class Parent:
    def func1(self):
        print("parent func1")


# 클래스 테스트(Parent 클래스 상속)
class TestClass(Parent):
    val1 = 0

    # 생성자
    def __init__(self):
        print("__init__")

    # 소멸자
    def __del__(self):
        print("__del__")

    # 객체로 호출했을때
    def __call__(self, a=None, b=None):
        print("__call__")
        if a is not None:
            print(f"a:{a}")
        if b is not None:
            print(f"b:{b}")

    def func1(self):
        print("func1")
        # 부모클래스 func1() 호출
        super().func1()

    def func2(self, parameter):
        print("func2 parameter = ", parameter)


# 클래스 객체 생성
temp = TestClass()
print(temp.val1)
# 객체 호출
temp()
temp("lemon", 123)

# 클래스 멤버 함수 호출
temp.func1()
temp.func2(123)
