# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : decorator 테스트


# 함수의 처리의 앞,뒤에 공통적으로 적용할것들 있다면
def myfunc1(arg):
    print("before something")
    print(arg)
    print("after something\n")


def myfunc2(a, b):
    print("before something")
    print(a + b)
    print("after something\n")


# decorator 를 사용했을대 사용되는 함수 정의
def dosomething(func):
    # closure 형태로 내부함수를 만들어 사용한다.
    def inner_func(*argc, **argv):
        print("before something")
        func(*argc, **argv)
        print("after something\n")
    return inner_func


# dosomething decorator 를 적용하면 함수 앞처리의 전,후 로 공통적인 처리를 decorator 로 적용할 수 있다.
# decorator 쪽으로 함수자체를 전달한다.
@dosomething
def myfunc3(arg):
    print(arg)


@dosomething
def myfunc4(a, b):
    print(a + b)

if __name__ == "__main__":
    myfunc1("ysoftman")
    myfunc2(5, 5)
    # decorator 적용한 함수
    myfunc3("ysoftman")
    myfunc4(5, 5)
