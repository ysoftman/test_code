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
def simple_function2(x):
    return x[0]**2 + x[1]**2

def function_2(x):
    if x.ndim == 1:
        return np.sum(x**2)    
    else:
        return np.sum(x**2, axis=1)


def temp_function1(x1):
    return x1**2 + 4.0**2


def temp_function2(x2):
    return 3.0**2 + x2**2


# 기울기 구하기
def numerical_gradient(f, x):
    h = 1e-4  # 0.001 더 작으면 파이썬에 0으로 취급된다.
    grad = np.zeros_like(x)  # x 같은 모양의 0값으로 초기화
    for i in range(x.size):
        temp = x[i]
        # f(x+h) 계산
        x[i] = temp + h
        fxh1 = f(x)

        # f(x-h) 계산
        x[i] = temp - h
        fxh2 = f(x)

        # 수치 미분
        grad[i] = (fxh1 - fxh2) / (2 * h)

        x[i] = temp

    return grad

# 기울기 구하기 배치 작업
def numerical_gradient_batch(f, X):
    if X.ndim == 1:
        return numerical_gradient(f, X)
    else:
        grad = np.zeros_like(X)
        for idx, x in enumerate(X):
            grad[idx] = numerical_gradient(f, x)

        return grad


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
    graph(x, y, "간단한 2차 함수 - 첫번째")
    # 2차 함수에서 5일대의 수치미분 계산
    # 0.1999999999990898 (실제 해석적 미분값은 0.2 으로 거의 같다)
    print(numerical_differentiation(simple_function1, 5))
    # 2차 함수에서 10일대의 수치미분 계산
    # 0.2999999999986347 (실제 해석적 미분값은 0.3 으로 거의 같다)
    print(numerical_differentiation(simple_function1, 10))

    """
    변수가 2개인 2차 함수 그리기
    """
    x1 = np.arange(-10.0, 10.1, 0.1)
    x2 = np.arange(10.0, -10.1, -0.1)
    # 2차원 배열 생성
    x1_2d, x2_2d = np.meshgrid(x1, x2)
    # x1_2d, x2_2d 배열 하나에 묶어 2차 함수 계산
    y_2d = simple_function2([x1_2d, x2_2d])
    graph_wire3d(x1_2d, x2_2d, y_2d)

    """
    편미분(partial derivative)
    변수가 2개 이상인 함수에 대한 미분
    목표 변수외의 변수는 고정하여 계산
    """
    # x1=3.0 x2=4.0 일때
    # x2 = 4.0 고정 하여 계산
    print(numerical_differentiation(temp_function1, 3.0))
    # x1 = 3.0 고정 하여 계산
    print(numerical_differentiation(temp_function2, 4.0))

    """
    기울기(gradient)
    모든 변수의 편미분을 벡터로 구성한것
    """
    # 변수 2개 편미분 한번에 하기
    # 점(3,4) 에서의 기울기 = (6,8)
    print(numerical_gradient(simple_function2, np.array([3.0, 4.0])))
    # 점(0,2) 에서의 기울기 = (0,4)
    print(numerical_gradient(simple_function2, np.array([0.0, 2.0])))
    # 점(3,0) 에서의 기울기 = (6,0)
    print(numerical_gradient(simple_function2, np.array([3.0, 0.0])))
    # 각 지접에서의 기울기 화살표 기울기로 그리기
    x0 = np.arange(-2, 2.5, 0.25)
    x1 = np.arange(-2, 2.5, 0.25)
    X, Y = np.meshgrid(x0, x1)
    X = X.flatten()
    Y = Y.flatten()
    grad = numerical_gradient_batch(function_2, np.array([X, Y]) )
    plt.figure()
    plt.quiver(X, Y, -grad[0], -grad[1],  angles="xy",color="#666666")#,headwidth=10,scale=40,color="#444444")
    # plt.xlim([-2, 2])
    # plt.ylim([-2, 2])
    # plt.xlabel('x0')
    # plt.ylabel('x1')
    # plt.grid()
    # plt.legend()
    # plt.draw()
    plt.show()