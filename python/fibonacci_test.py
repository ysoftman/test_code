# -*- coding: utf-8 -*-
# author: ysoftman
# fibonacci test


# 0 1 1 2 3 5 8 13 21 34 55
# 현재피보나치값 = (현재피보나치값-2) + (현재피보나치값-1) 가 반복된다.
def fibonnaci(n):
    if n == 1 or n == 0:
        return n
    return fibonnaci(n - 2) + fibonnaci(n - 1)


if __name__ == "__main__":
    # x번째 값의 피보나치 값을 구한다.
    print("fibonnaci(0) = ", fibonnaci(0))
    print("fibonnaci(1) = ", fibonnaci(1))
    print("fibonnaci(2) = ", fibonnaci(2))
    print("fibonnaci(3) = ", fibonnaci(3))
    print("fibonnaci(4) = ", fibonnaci(4))
    print("fibonnaci(5) = ", fibonnaci(5))
    print("fibonnaci(6) = ", fibonnaci(6))
    print("fibonnaci(7) = ", fibonnaci(7))
    print("fibonnaci(8) = ", fibonnaci(8))
    print("fibonnaci(9) = ", fibonnaci(9))
    print("fibonnaci(10) = ", fibonnaci(10))
