# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : numpy 테스트

# pip install np
import numpy as np


def calc_do_something():
    # 2x3 배열(행렬))
    ar1 = np.array([[1, 2, 3], [4, 5, 6]])
    print('ar1 =', ar1)
    # 타입
    print('type(ar1) = ', type(ar1))
    # 차원을 나타내는 튜플
    print('ar1.shape = ', ar1.shape)
    # 원소 개수
    print('ar1.size = ', ar1.size)
    # 특정 원소 인덱싱
    # 0번째 행의 2번째 열 위치 원소
    print('ar1[[0],[2]] = ', ar1[[0], [2]])
    print('')

    # 3x3 크기의 모든 원소 값이 0
    ar2 = np.zeros((3, 3))
    print(ar2)
    print('')
    # 3x3 크기의 모든 원소 값이 9
    ar3 = np.full((3, 3), 9.0)
    print(ar3)
    print('')

    # 행렬에 값하나(스칼라) 연산
    print(ar3 + 2)
    print(ar3 - 2)
    print(ar3 / 3)
    print(ar3 * 3)

    ar4 = np.full((3, 3), 3.0)
    print(ar3 + ar4)
    print(ar3 - ar4)
    print(ar3 / ar4)
    # 각 원소에 대한 단순 곱
    print(ar3 * ar4)

    # 행렬의 곱은 dot 연산 사용
    print(np.dot(ar3, ar4))

    # 램덤 출력
    print('randint test')
    for _ in range(0, 10):
        r = np.random.randint(100)
        print(r)


def reshape_arr():
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
    calc_do_something()
    reshape_arr()
