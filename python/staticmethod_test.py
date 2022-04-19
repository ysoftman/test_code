# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : staticmethod 테스트

class AppleClass:
    # 생성자
    def __init__(self):
        print("__init__")

    # 소멸자
    def __del__(self):
        print("__del__")

    def func1(self):
        print("func1")

    @staticmethod
    # @staticmethod 데코레이션을 붙이면 정적 메소드로 취급되어 self 를 사용하지 않는다.
    # 클래스 인스턴스 속성에 영향을 주지 않는 경우만 정적 메소드로 만들자.
    def func2(parameter):
        print("func2 parameter = ", parameter)

# 클래스내의 함수는 클래스 인스턴스를 생성해 호출하는데
temp = AppleClass()
temp.func1()
temp.func2(123)

# @staticmethod 데코레이션을 붙이면 바로 호출할 수 있다.
AppleClass.func2("ysoftman")
