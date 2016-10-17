# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : tuple test


def tuple_test():
    # 튜플이 리스트와 다른점 1
    # 표현시 () 를 사용한다. 리스트는 [] 사용 
    tp = (1, 'ysoftman', 7, 'abc')
    print 'tuple = ', tp

    # 튜플이 리스트와 다른점 2
    # 튜플은 데이터  수정을 할 수 없다.
    # 에러 발생
    # del tp[1]
    # 반면 리스트는 수정할 수 있다.
    ls = [1, 'ysoftman', 7, 'abc']
    print 'list = ', ls
    del ls[1]
    print 'list = ', ls


if __name__ == '__main__':
    tuple_test()
