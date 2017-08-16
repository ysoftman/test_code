# -*- coding: utf-8 -*-
'''
author: ysoftman
python version : 3.x
desc : 미분, 기울기(gradient) 함수
'''
import numpy as np
import matplotlib.pylab as plt
# for 3d graph
from mpl_toolkits.mplot3d import axes3d
from activation_function import graph


# 수치 미분
# 함수f에서 임의 x 위치에서 변화량으로 미분에 근사한 값을 구한다.
def numerical_differentiation(f, x):
    h = 1e-4  # 0.001 더 작으면 파이썬에 0으로 취급된다.
    # 함수 f 위에 x+h(시간 또는 거리)와 x-h 두점을 기준으로 접선(변화량)을 계산
    return (f(x + h) - f(x - h)) / (2 * h)


# 간단한 2차 함수
def simple_function1(x):
    return 0.01 * x**2 + 0.1 * x


# 간단한 2차 함수
def simple_function2(x1, x2):
    return x1**2 + x2**2


def graph(x, y, title):
    # set range y
    plt.ylim(-0.1, 7.0)
    # change windows title
    fig = plt.gcf()
    fig.canvas.set_window_title(title)
    # set x, y value
    plt.plot(x, y)
    # show graph
    plt.show()


def graph_wire3d(x, y, z):
    # 그래프가 들어가 fig 생성
    fig = plt.figure()
    # fig 제목 설정
    fig.canvas.set_window_title(graph_wire3d.__name__)
    # 1 개의 행, 1 개의 열로 구성된 그래프 중 1번째 그래프 추가, 3d 스타일
    ax = fig.add_subplot(111, projection='3d')

    # X, Y,	Data values as 2D arrays
    # Z
    # rstride	Array row stride (step size), defaults to 1
    # cstride	Array column stride (step size), defaults to 1
    # rcount	Use at most this many rows, defaults to 50
    # ccount	Use at most this many columns, defaults to 50
    ax.plot_wireframe(x, y, z, rstride=10, cstride=10)
    plt.show()


# 입력 x 값들에 대해서 활성화(출력 0이상)화 판단
if __name__ == "__main__":
    """
    수치미분(두점의 변화량을 이용해서 미분을 계산)
    """
    x = np.arange(0.0, 20.0, 0.1)
    y = simple_function1(x)
    # graph(x, y, "간단한 2차 함수 - 첫번째")
    # 2차 함수에서 5일대의 수치미분 계산
    # 0.1999999999990898 (실제 해석적 미분값은 0.2 으로 거의 같다)
    print(numerical_differentiation(simple_function1, 5))
    # 2차 함수에서 10일대의 수치미분 계산
    # 0.2999999999986347 (실제 해석적 미분값은 0.3 으로 거의 같다)
    print(numerical_differentiation(simple_function1, 10))

    """
    변수가 2개읜 2차 함수 그리기
    """
    x1 = np.arange(-10.0, 10.1, 0.1)
    x2 = x1
    # 2차원 배열 생성
    x1_2d, x2_2d = np.meshgrid(x1, x2)
    y_2d = simple_function2(x1_2d, x2_2d)
    graph_wire3d(x1_2d, x2_2d, y_2d)
    print(x1_2d, x2_2d, y_2d)
