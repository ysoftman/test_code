# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : numpy 테스트

# pip install np
import numpy as np


def calculate_array():
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
    print("ar2 np.zeros((3, 3) =", ar2)
    print('')
    # 3x3 크기의 모든 원소 값이 9
    ar3 = np.full((3, 3), 9.0)
    print("ar3 np.full((3, 3), 9.0) = ", ar3)
    print('')

    # 행렬에 값하나(스칼라) 연산
    print("ar3 + 2 = ", ar3 + 2)
    print("ar3 - 2 = ", ar3 - 2)
    print("ar3 / 3 = ", ar3 / 3)
    print("ar3 * 3 = ", ar3 * 3)

    ar4 = np.full((3, 3), 3.0)
    print("ar3 + ar4 =", ar3 + ar4)
    print("ar3 - ar4 =", ar3 - ar4)
    print("ar3 / ar4 =", ar3 / ar4)
    # 각 원소에 대한 단순 곱
    print("ar3 * ar4 =", ar3 * ar4)

    # 행렬의 곱은 dot 연산 사용
    print("ar3 dot ar4 =", np.dot(ar3, ar4))

    # 램덤 출력
    print('randint(100) test')
    for _ in range(0, 10):
        r = np.random.randint(100)
        print(r, end=' ')

    print('')


if __name__ == '__main__':
    calculate_array()
