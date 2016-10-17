# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : sort test


def do_sort():
    data = [5,4,3,2,1]
    print 'orgin = ', data

    # 정렬하기
    data.sort()
    print 'sort = ', data

    # 리스트 생성시 정렬하기
    data2 = sorted([10,9,8,7,6,5,4,3,2,1,0])
    print 'sorted = ', data2

    # 내림차순으로 정렬
    # data3 = sorted(data2, reverse=True)
    data2.sort(reverse=True)
    print 'reversed sort = ',data2

if __name__ == '__main__':
    do_sort()
