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

# SUMLEVL==50이고
# NaN 가 포함된 로우(row)들 지우고
# STNAME, CTYNAME 컬럼으로 인덱스로 설정하고
# 컬럼이름 변경 ESTIMATESBASE2010 -> Estimates Base 2010
print(df.where(df['SUMLEV'] == 50).dropna().set_index(['STNAME', 'CTYNAME']).rename(
    columns={'ESTIMATESBASE2010': 'Estimates Base 2010'}))
