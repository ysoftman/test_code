# -*- coding: utf-8 -*-
'''
author: ysoftman
python version : 3.x
desc : 미분, 기울기(gradient) 함수
'''
import numpy as np
import matplotlib.pylab as plt
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
    # 0.2999999999986347 (실제 해석저 미분값은 0.3 으로 거의 같다)
    print(numerical_differentiation(simple_function1, 10))

