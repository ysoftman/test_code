# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : numbers test

import math


def do_math():
    # 올립(ceil), 반올림(round), 버림(floor)
    num = 123.5687281
    print('---\nnum =', num)
    print('math.ceil(num) =', math.ceil(num))
    print('round(num) =', round(num))
    print('round(num,1) =', round(num,1)) # 소수점1자리까지 표현
    print('round(num,2) =', round(num,2)) # 소수점2자리까지 표현
    print('round(num,3) =', round(num,3)) # 소수점3자리까지 표현
    print('math.floor(num) =', math.floor(num))

    # 절대값
    num = -123
    print('---\nnum =', num)
    print('math.fabs(num) =', math.fabs(num))

    # float to int
    num = 1.5
    print('---\num =', int(num))
    print('num =', num+0.5)
    print('num =', int(num+0.5))

    # 제곱
    num = 4.2
    print('---\nnum =', num)
    print('num =', math.pow(num, 2))

    # 로그함수
    num = 50
    print('---\nnum =', num)
    print('num =', math.log(num, 10))

    # 파이값
    print('---\nmath.pi =', math.pi)


if __name__ == '__main__':
    do_math()
