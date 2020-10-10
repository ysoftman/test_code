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

# 컬럼 이름들
print(df.columns)
print()

# SUMLEV 컬럼의 유니크값
# SUMLEV(Summary Level) 인구 통계청에서 지역구분에 쓰는 코드다
# 040 : state
# 050 : county
# 140 : census trac
# 참고 https://blog.cubitplanning.com/2011/03/census-summary-level-sumlev/
print("df['SUMLEV'].unique() =", df['SUMLEV'].unique())
print()

# SUMLEV == 50 인 데이터만 남기기
df = df[df['SUMLEV'] == 50]
# 지정한 컬럼만 남기기
columns_to_keep = ['STNAME',
                   'CTYNAME',
                   'BIRTHS2010',
                   'BIRTHS2011',
                   'BIRTHS2012',
                   'BIRTHS2013',
                   'BIRTHS2014',
                   'BIRTHS2015',
                   'POPESTIMATE2010',
                   'POPESTIMATE2011',
                   'POPESTIMATE2012',
                   'POPESTIMATE2013',
                   'POPESTIMATE2014',
                   'POPESTIMATE2015']
df = df[columns_to_keep]
print(df)
print()

# STNAME, CTYNAME 2개의 컬럼을 인덱스로 설정(MultiIndex 멀티 인덱스)
df = df.set_index(['STNAME', 'CTYNAME'])
# 기존 디폴트 인덱스에 추가할 수 도 있지만
# 디폴트는 숫자 카운트 형이라 조회시 불편하다.
# df = df.set_index([df.index, 'STNAME', 'CTYNAME'])
# 인덱스 이름을 별도로 설정할 수도 있다.
df.index.name = ['state', 'city']
print(df)
print()

# STNAME, CTYNAME 가 인덱싱이 되었으니
# STNAME=Michigan, CTYNAME=Washtenaw County 레이블로 조회 할 수 있다.
# 차원으로 표현된다.
print("df.loc['Michigan', 'Washtenaw County'] =\n",
      df.loc['Michigan', 'Washtenaw County'])

# 2개의 도시이니경우 다음과 같이 2차원으료 표현된다.
print("df.loc[[('Michigan', 'Washtenaw County'),('Michigan', 'Wayne County')]]=\n",
      df.loc[[('Michigan', 'Washtenaw County'), ('Michigan', 'Wayne County')]])
print()
