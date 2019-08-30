# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : numpy 테스트

# pip install np
import numpy as np


def reshape_array():
    # 64x64x3 의 3차원 배열을 만든다.
    arr = np.zeros((64, 64, 3))
    print("arr.shape:", arr.shape)
    # 4096x3 의 2차원 배열로 변경
    newarr1 = arr.reshape(64 * 64, 3)
    print("arr -> newarr1.shape:", newarr1.shape)
    # 첫번째 인자에 -1의 의미 : 2차원 16, 3차원 16으로 맞춘다음 나머지 (64*64*3) / (16x16) = 48 를 1차원 요소로 맞춘다.
    newarr2 = arr.reshape(-1, 16, 16)
    print("arr -> newarr2.shape:", newarr2.shape)
    # 세번재 인자에 -1의 의미 : 1차원 16, 2차원 16으로 맞춘다음 나머지 (64*64*3) / (16x16) = 48 를 3차원 요소로 맞춘다.
    newarr2 = arr.reshape(16, 16, -1)
    print("arr -> newarr2.shape:", newarr2.shape)


if __name__ == '__main__':
    reshape_array()
