# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : 전역변수 사용하기

# 전역변수 선언
val0 = 1
somelist = [1, 2, 3, 4, 5]


def func1():
    # 지역변수
    val1 = 5
    print val1

    # 전역변수를 사용하려면 global을 명시해야 한다.
    global val0
    val0 += 9
    print val0


def func2():
    # = 으로 할당하는 경우 global 을 명시하지 않으면 로컬변수가 된다.
    # somelist = [99]

    # 하지만 = 를 사용하지 않는다면(선언하지 않는다면) 이미 선언된 지역변수 또는 전역변수에 대한 함수 호출이된다.
    # 따라서 somelist 가 글로벌 변수로 이미 선언되어 있고 지역변수에 같은 이름이 없으면 전역변수를 사용한다.
    somelist.append(100)

    print somelist


if __name__ == "__main__":
    func1()
    print val0

    func2()
    print somelist
