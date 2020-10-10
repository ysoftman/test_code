# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : sort test


def do_sort():
    data = [5, 4, 3, 2, 1]
    print('orgin = ', data)

    # 정렬하기
    data.sort()
    print('sort = ', data)

    # 리스트 생성시 정렬하기
    data2 = sorted([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0])
    print('sorted = ', data2)

    # 내림차순으로 정렬
    # data3 = sorted(data2, reverse=True)
    data2.sort(reverse=True)
    print('reversed sort = ', data2)

    # 2차원 배열
    # iterate 리스트 마다 원소 합을 람다함수로 키 로직 설정
    data3 = [[2, 2], [4, 1], [6, 1], [3, 7]]
    print('2d list sorted = ', sorted(data3))
    data3_sorted = sorted(data3, key=lambda x: x[0] + x[1])
    print('2d list sorted by custom key = ', data3_sorted)


if __name__ == '__main__':
    do_sort()
