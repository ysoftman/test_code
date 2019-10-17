# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd

df = pd.DataFrame(['A+', 'A', 'A-', 'B+', 'B', 'B-', 'C+', 'C', 'C-', 'D+', 'D'],
                  index=['excellent', 'excellent', 'excellent', 'good', 'good', 'good', 'ok', 'ok', 'ok', 'poor', 'poor'])
# 0 -> Grades 컬럼이름 변경
df.rename(columns={0: 'Grades'}, inplace=True)
print(df)
print(type(df))
print()

# 'category' 라는 탑으로 변환
df2 = df['Grades'].astype('category')
print(df2)
print(type(df2))
print()


# 'category' 라는 탑으로 변환, D < D+ < C- < C ... B+ < A- < A < A+ 순서로
df3 = df['Grades'].astype('category',
                             categories=['D', 'D+', 'C-', 'C', 'C+',
                                         'B-', 'B', 'B+', 'A-', 'A', 'A+'],
                             ordered=True)
print(df3)
print(type(df3))
print()


# C 초과 학점 파악
print(df3 > 'C')
print(df[df3 > 'C'])
print(df[df3 > 'C']['Grades'])
print(df[df3 > 'C']['Grades'].index.values)
print()
