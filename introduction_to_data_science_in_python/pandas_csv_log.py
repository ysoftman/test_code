# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


print("load log.csv ... ")
print()

# csv 파일 읽기
df = pd.read_csv('log.csv')
print("df.head()=\n", df.head(), sep="")
print()

# 컬럼 이름들
print(df.columns)
print()

# time 컬럼으로 인덱싱
df = df.set_index(['time'])
df.sort_index()
print(df)
print()

# time, user 컬럼으로 인덱싱
df = df.reset_index()
df = df.set_index(['time', 'user'])
print(df)
print()

# missing data 처리
# NA, NaN 상태의 값들을
# NaN -999 값으로 채우기
df = df.fillna(-999)
# ffill(forward to next:이전의 유효한 값들을 사용) 방식으로 채워넣는다.
# df = df.fillna(method='ffill')
print(df)
print()
