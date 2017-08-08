# -*- coding: utf-8 -*-
'''
author: ysoftman
python version : 2.x
desc : 활성화 함수 테스트
'''
import numpy as np
import matplotlib.pylab as plt


# step(스텝)
# 계단 모양으로 입력이 0 이하면 0(비활성화) 0이상이면 1(활성화)
def step(x):
    # dtype 옵션으로 bool 결과를 int 변환해야 한다.
    return np.array(x > 0, dtype=int)


# sigmoid(시그모이드)
# s 모양으로 출력이 점진적으로 커진다.
# y = 1 / (1 + (자연상수e ** -x))
def sigmoid(x):
    return 1 / (1 + np.exp(-x))


# ReLU(렐루)
# 입력이 0이하면 0, 0 초과하면 입력값 그대로 출력(활성화)
def relu(x):
    return np.maximum(0, x)


def graph(x, y, title):
    # set range y
    plt.ylim(-0.1, 1.1)
    # change windows title
    fig = plt.gcf()
    fig.canvas.set_window_title(title)
    # set x, y value
    plt.plot(x, y)
    # show graph
    plt.show()

# 입력 x 값들에 대해서 활성화(출력 0이상)화 판단
if __name__ == "__main__":
    x = np.arange(-5, 5, 0.1)
    y = step(x)
    print x
    print y
    graph(x, y, "step function")

    y = sigmoid(x)
    print y
    graph(x, y, "sigmoid function")

    y = relu(x)
    print y
    graph(x, y, "sigmoid function")
