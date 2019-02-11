# -*- coding: utf-8 -*-
# author: ysoftman
# local variable test

# 전역 변수
a = 1
b = 1


def increase1():
    # 전역 변수 값을 출력
    print a


def increase2():
    # 로컬 변수 b가 선언되어 있지 않으면 에러가 발생한다.
    b = 10
    # 할당 연산으로 변경이 필요한 경우
    # 전역 변수가 아닌 로컬 변수 b 를 찾게 된다.
    b += 1
    print b
    return b


def increase3():
    return 1


if __name__ == '__main__':
    increase1()
    increase2()
    # 파이썬은 전역 변수를 함수에서 변경하는 것을 지양한다.
    # 대신 함수 리턴값으로 호출한쪽에서 전역 변수를 바꾸도록 권장한다.
    b += increase3()
    print b
