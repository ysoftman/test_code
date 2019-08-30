# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : numpy 테스트

# pip install np
import numpy as np


def do_array():
    # 6x6 배열 생성
    # ar1 = np.arange(start=0, stop=36, step=1, dtype='int')
    ar1 = np.arange(0, 36, 1, 'int')
    print("ar1 =\n", ar1)
    ar1 = ar1.reshape(6, 6)
    print("ar1.reshape(6, 6) =\n", ar1)
    print("ar1[...] =\n", ar1[...])
    # 차원은 , 로 구분
    # 차원은 리스트 슬라이싱 패턴 start:stop:step

    # 0~6 리스트 선택 후 각 리스트의 뒤에서 -7 씩 증가한 위치의 값
    print("ar1[0:6, ::-7] =\n", ar1[0:6, ::-7])
    # 전체 리스트 선택 후 각 리스트의 앞에서 7 씩 증가한 위치의 값
    print("ar1[:, ::7] =\n", ar1[:, ::7])
    # 1차원 배열(리스트)로 만들 후 리스트의 앞에서 7 씩 증가한 위치의 값
    print("ar1.reshape(36)[::7] =\n", ar1.reshape(36)[::7])
    # 첫번째 차원(리스트들)의 7 씩 증가한 위치의 값
    print("ar1[::7] =\n", ar1[::2])

    print("ar1[2:4, 2:4] =\n", ar1[2:4, 2:4])
    print("ar1[::2, ::2] =\n", ar1[::2, ::2])
    print("ar1[2::2, 2::2] =\n", ar1[2::2, 2::2])


if __name__ == '__main__':
    do_array()
