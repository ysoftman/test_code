# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


print("load olympics.csv ... ")
print()

# csv 파일 읽기
# 첫번째 줄을 건너뛰고 로딩
# 0번 컬럼(나라명)을 인덱스로 한다.
df = pd.read_csv('olympics.csv', skiprows=1, index_col=0)
print("df.head()=\n", df.head(), sep="")
print()

# 컬럼 이름들
print(df.columns)
print()


# 컬럼 이름들을 변경
for col in df.columns:
    if col[:2] == '01':
        df.rename(columns={col: 'Gold' + col[4:]}, inplace=True)
    if col[:2] == '02':
        df.rename(columns={col: 'Silver' + col[4:]}, inplace=True)
    if col[:2] == '03':
        df.rename(columns={col: 'Bronze' + col[4:]}, inplace=True)
    if col[:1] == '№':
        df.rename(columns={col: '#' + col[1:]}, inplace=True)

print("df.head()=\n", df.head(), sep="")
print()
