# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : matplotlib  test
# pip install matplotlib
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import axes3d


def simple2d():
    fig = plt.gcf()
    # fig 제목 설정
    fig.canvas.set_window_title("simple 2d")
    # x = 1, .. 100
    x = range(100)
    # y = x*2
    y = [i * 2 for i in x]
    # set x,y
    plt.plot(x, y)
    # show graph
    plt.show()


# 하나의 윈도우(figure)에서 2개의 그래프 그리기
def multi_graph():
    # 그래프가 들어가 fig 생성
    fig = plt.figure()
    # fig 제목 설정
    fig.canvas.set_window_title(multi_graph.__name__)
    # 2 개의 행, 1 개의 열로 구성된 그래프 중 1번째 그래프 추가
    ax1 = fig.add_subplot(211)
    # 2 개의 행, 1 개의 열로 구성된 그래프 중 2번째 그래프 추가
    ax2 = fig.add_subplot(212)
    x = range(100)
    y = [i * 2 for i in x]
    ax1.set_title("graph1")
    ax1.plot(x, y)
    ax2.set_title("graph2")
    ax2.plot(x, y)
    plt.show()


# 와이드로 표시되는 3d 그래프
def wire3d():
    # 그래프가 들어가 fig 생성
    fig = plt.figure()
    # fig 제목 설정
    fig.canvas.set_window_title(wire3d.__name__)
    # 1 개의 행, 1 개의 열로 구성된 그래프 중 1번째 그래프 추가, 3d 스타일
    ax = fig.add_subplot(111, projection="3d")

    # x = range(100)
    # y = [i * 2 for i in x]
    # z = [i * 2 for i in y]
    x, y, z = axes3d.get_test_data(0.05)

    # X, Y,	Data values as 2D arrays
    # Z
    # rstride	Array row stride (step size), defaults to 1
    # cstride	Array column stride (step size), defaults to 1
    # rcount	Use at most this many rows, defaults to 50
    # ccount	Use at most this many columns, defaults to 50
    ax.plot_wireframe(x, y, z, rstride=10, cstride=10)
    plt.show()


# 화살통(quiver) 모양의 그래프
def quiver():
    X, Y = np.meshgrid(np.arange(0, 2 * np.pi, 0.2), np.arange(0, 2 * np.pi, 0.2))
    U = np.cos(X)
    V = np.sin(Y)
    fig = plt.figure()
    fig.canvas.set_window_title(quiver.__name__)
    Q = plt.quiver(X, Y, U, V, units="width")
    plt.quiverkey(
        Q, 0.9, 0.9, 2, r"$2 \frac{m}{s}$", labelpos="E", coordinates="figure"
    )
    # x,y 축 범위
    plt.xlim([-1, 7])
    plt.ylim([-1, 7])
    # x,y 축 이름
    plt.xlabel("x")
    plt.ylabel("y")
    # 배경 격자 표시
    plt.grid()
    plt.show()


if __name__ == "__main__":
    simple2d()
    multi_graph()
    wire3d()
    quiver()
