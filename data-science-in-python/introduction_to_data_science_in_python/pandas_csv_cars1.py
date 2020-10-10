# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


print("load cars.csv ... ")
print()

# csv 파일 읽기
df = pd.read_csv('cars.csv')
print(df)
print()

# pivot_table 로 원하는 데이터만 따로 DataFrame 으로 생성한다.
# 연도별(year컬럼을 인덱스, 각 행)
# 제조사(Make컬럼, 각 열)의
# 배터리(kw컬럼, 열들의 값이 된다.) 평균을 집계한다.
print(df.pivot_table(values='(kW)', index='YEAR', columns='Make', aggfunc=np.mean))
print()


# 평균, 최소값 2개를 집계한다.(제조사별 min 값 컬럼들이 추가된다.)
print(df.pivot_table(values='(kW)', index='YEAR', columns='Make',
                     aggfunc=[np.mean, np.min], margins=True))
print()
