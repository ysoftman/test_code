# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : numpy 테스트

# pip install np
import numpy as np


def calculate_array():
    # 2x3 배열(행렬))
    ar = np.array([[1, 2, 3], [4, 5, 6]])
    print('ar =', ar)
    # 타입
    print('type(ar) = ', type(ar))
    # 차원을 나타내는 튜플
    print('ar.shape = ', ar.shape)
    # 원소 개수
    print('ar.size = ', ar.size)
    # 특정 원소 인덱싱
    # 0번째 행의 2번째 열 위치 원소
    print('ar[[0],[2]] = ', ar[[0], [2]])
    print()

    # 큰 배열 생성
    ar = np.zeros(1000000, dtype=int)
    print("ar np.zeros(1000000, dtype=int) =", ar)
    print()
    ar = np.empty(1000000, dtype=int)
    print("ar = np.empty(1000000, dtype=int) =", ar)
    print()

    # 3x3 크기의 모든 원소 값이 0
    ar = np.zeros((3, 3))
    print("ar np.zeros((3, 3) =", ar)
    print()
    # 3x3 크기의 모든 원소 값이 9
    ar1 = np.full((3, 3), 9.0)
    print("ar1 np.full((3, 3), 9.0) = ", ar1)
    print()
    # 3x3 크기의 모든 원소 값이 3
    ar2 = np.full((3, 3), 3.0)
    print("ar2 np.full((3, 3), 3.0) = ", ar2)
    print()

    # 행렬에 값하나(스칼라) 연산
    print("ar1 + 2 = ", ar1 + 2)
    print("ar1 - 2 = ", ar1 - 2)
    print("ar1 / 3 = ", ar1 / 3)
    print("ar1 * 3 = ", ar1 * 3)
    print()

    # 행렬 끼리 연산
    print("ar1 + ar2 =", ar1 + ar2)
    print("ar1 - ar2 =", ar1 - ar2)
    print("ar1 / ar2 =", ar1 / ar2)
    print("ar1 * ar2 =", ar1 * ar2)
    print()

    # 행렬의 곱은 dot 연산 사용
    print("ar1 dot ar2 =", np.dot(ar1, ar2))
    print()
    # 램덤 출력
    print('np.random.randint(100) test')
    for _ in range(0, 10):
        r = np.random.randint(100)
        print(r, end=' ')
    print()
    print()

    ar = [i for i in range(1, 11)]
    print('ar =', ar)
    print('np.mean(ar) =', np.mean(ar))
    # min, max -> amin(), amax() 의 별명
    print('np.min(ar) =', np.min(ar))
    print('np.amin(ar) =', np.amin(ar))
    print('np.max(ar) =', np.max(ar))
    print('np.amax(ar) =', np.amax(ar))
    print()

    # -10 ~ 10 상의 숫자 10개 랜덤 생성
    ar = np.random.randint(-10, 10, 10)
    print('ar np.random.randint(-10, 10, 10) =', ar)
    # 이전 원소값 + 현재 원소값 => 현재원소값
    print('ar.cumsum()', ar.cumsum())


if __name__ == '__main__':
    calculate_array()
