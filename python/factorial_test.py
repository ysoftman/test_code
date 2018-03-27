# -*- coding: utf-8 -*-
# author: ysoftman
# factorial test


def factorial(n):
    # print n
    if n == 1 or n == 0:
        return n
    return n * factorial(n - 1)

if __name__ == '__main__':
    print 'factorial(0) = ', factorial(0)
    print 'factorial(5) = ', factorial(5)
    print 'factorial(10) = ', factorial(10)
