# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : numpy 테스트

# pip install numpy
import numpy


def calc_do_something():
    # 2x3 배열
    ar1 = numpy.array([[1,2,3],[4,5,6]])
    print 'ar1 =', ar1
    # 타입
    print 'type(ar1) = ', type(ar1)
    # 차원을 나타내는 튜플
    print 'ar1.shape = ', ar1.shape
    # 원소 개수
    print  'ar1.size = ', ar1.size
    # 특정 원소 인덱싱
    # 0번째 행의 2번째 열 위치 원소
    print 'ar1[[0],[2]] = ', ar1[[0],[2]]
    print ''

    # 3x3 크기의 모든 원소 값이 0
    ar2 = numpy.zeros((3,3))
    print ar2
    print ''
    # 3x3 크기의 모든 원소 값이 9
    ar3 = numpy.full((3,3),9.0)
    print ar3
    print ''

    # 램덤 출력
    print 'randint test'
    for i in range(0, 10):
        r = numpy.random.randint(100)
        print r

    
if __name__ == '__main__':
    calc_do_something()