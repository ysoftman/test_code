# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 매트릭스 그래프 표시
import seaborn as sn
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    # mat = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    #        ]
    lines = 10
    cols = lines
    mat = np.zeros((lines, cols))
    print(mat)
    for line in range(len(mat)):
        for cols in range(len(mat[line])):
            mat[line][cols] = np.random.randint(100)
    print(mat)
    names = {
        "aaa",
        "bbb",
        "ccc",
        "ddd",
        "eee",
        "fff",
        "ggg",
        "hhh",
        "iii",
        "jjj",
    }
    df_cm = pd.DataFrame(mat, index=[i for i in names], columns=[i for i in names])
    plt.figure()
    sn.heatmap(df_cm, annot=True)
    plt.show()
