# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : matplotlib  test
# pip install matplotlib

import matplotlib.pyplot as plt

def showgraph():
    # x = 1, .. 100
    x = range(100)
    # y = x*2
    y = [i*2 for i in x]
    # set x,y 
    plt.plot(x,y)
    # show graph
    plt.show()

if __name__ == '__main__':
    showgraph()
