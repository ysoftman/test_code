# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# factorial test


# 5 * 4 * 3 * 2 * 1 = 120
# 현재팩토리얼값 = (현재팩토리얼값) * (현재팩토리얼값-1) 가 반복된다.
def factorial(n):
    # print n
    if n == 1 or n == 0:
        return n
    return n * factorial(n - 1)


if __name__ == "__main__":
    print("factorial(0) = ", factorial(0))
    print("factorial(5) = ", factorial(5))
    print("factorial(10) = ", factorial(10))
