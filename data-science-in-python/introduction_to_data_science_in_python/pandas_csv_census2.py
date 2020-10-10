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

# df[][][]...형태르 쓰는 chain indexing 은
# numpy 에 따라 view 복사본을 리턴할 수 있어 나쁜 사용법이다.
# df.aaa().bbb() method chain 방식
# SUMLEVL==50이고
# NaN 가 포함된 로우(row)들 지우고
# STNAME, CTYNAME 컬럼으로 인덱스로 설정하고
# 컬럼이름 변경 ESTIMATESBASE2010 -> Estimates Base 2010
print(df.where(df['SUMLEV'] == 50).dropna().set_index(['STNAME', 'CTYNAME']).rename(
    columns={'ESTIMATESBASE2010': 'Estimates Base 2010'}))
print()

# pandas idiomatic (판다 관용 표현) 성능(method index 보다 빠르다)과 가독성이 좋다.
# Pandorable 판다스럽다라는 뜻
df = df[df['SUMLEV'] == 50]
df.set_index(['STNAME', 'CTYNAME'], inplace=True)
df.rename(columns={'ESTIMATESBASE2010': 'Estimates Base 2010'})
print(df)
print()


# dataframe(df) 에 저용할 min,max 함수
def min_max(row):
    # df 에 적용할 컬림들(2차원으로 선언)
    data = row[['POPESTIMATE2010',
                'POPESTIMATE2011',
                'POPESTIMATE2012',
                'POPESTIMATE2013',
                'POPESTIMATE2014',
                'POPESTIMATE2015']]
    # data 컬럼들에서  min, max 값을 찾아 새로운 series 데이터를 만든다.
    return pd.Series({'min': np.min(data), 'max': np.max(data)})


# df 컬럼(axis=1)에 대해 min_max 함수를 수행(적용)한다.
# df 에 min_max 의 series 컬럼만 추가된 형태가 된다.
min_max_series = df.apply(min_max, axis=1)
print(min_max_series)
print(type(min_max_series))
print()

# 다음과 같이 idiomatic (Pandorable 판다스럽다라는 뜻)하게 람다 코드를 사용할 수 있다.
rows = ['POPESTIMATE2010',
        'POPESTIMATE2011',
        'POPESTIMATE2012',
        'POPESTIMATE2013',
        'POPESTIMATE2014',
        'POPESTIMATE2015']
print(df.apply(lambda x: np.max(x[rows]), axis=1))
print()
