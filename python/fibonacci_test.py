# -*- coding: utf-8 -*-
# author: ysoftman
# fibonacci test


def fibonnaci(n):
    if n == 1 or n == 0:
        return n
    return fibonnaci(n - 1) + fibonnaci(n - 2)

if __name__ == '__main__':
    print 'fibonnaci(0) = ', fibonnaci(0)
    print 'fibonnaci(1) = ', fibonnaci(1)
    print 'fibonnaci(2) = ', fibonnaci(2)
    print 'fibonnaci(3) = ', fibonnaci(3)
    print 'fibonnaci(4) = ', fibonnaci(4)
    print 'fibonnaci(5) = ', fibonnaci(5)
    print 'fibonnaci(6) = ', fibonnaci(6)
    print 'fibonnaci(7) = ', fibonnaci(7)
    print 'fibonnaci(8) = ', fibonnaci(8)
    print 'fibonnaci(9) = ', fibonnaci(9)
    print 'fibonnaci(10) = ', fibonnaci(10)
