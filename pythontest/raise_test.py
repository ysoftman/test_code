# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : raise 테스트

import pickle

def check_something(string):
    if string == 'ysoftman':
        return 'success'
    else:
        # 강제로 예외 발생
        # raise NotImplementedError
        raise Exception('raise test')


if __name__ == '__main__':
    print check_something('ysoftman')
    print check_something('yoon')
