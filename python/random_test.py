# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : random test

import random

def do_random():
    # 0.0 ~ 1.0 랜덤값
    print('random.random() =', random.random())

    # 1 ~ 100 정수 랜덤값
    print('random.randint(1,100) =', random.randint(1, 2))

    # 1~99 정수
    print('random.randrange(1,100) =', random.randrange(1,100))

if __name__ == '__main__':
    do_random()
