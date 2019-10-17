# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


print("load census.csv ... ")
print()

# csv 파일 읽기
df = pd.read_csv('census.csv')
print("df.head()=\n", df.head(), sep="")
print()

df = df[df['SUMLEV'] == 50]
df = df.set_index('STNAME').groupby(level=0)[
    'CENSUS2010POP'].agg({'avg': np.average})
print(df)

# 3개의 범주(bin)나누고 각각 레이블을 붙인다.
print(pd.cut(df['avg'], 3))
print(pd.cut(df['avg'], 3, labels=['Small', 'Medium', 'Large']))
