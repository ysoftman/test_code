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

# SUMLEV 컬럼의 유니크값
# SUMLEV(Summary Level) 인구 통계청에서 지역구분에 쓰는 코드다
# 40 : state
# 50 : county
# state 로우만 필터링
df = df[df['SUMLEV'] == 50]

# 유니크로 구별했을때
for state in df['STNAME'].unique():
    # 현재 순회중인 state 들의 County 들에 대해서
    # NaN 값이 있는 로우는 제거하고
    # CENSUS2010POP 컬럼 값의 평균
    avg = np.average(df.where(df['STNAME'] == state).dropna()['CENSUS2010POP'])
    print('Counties in state ' + state +
          ' have an average population of ' + str(avg))
print()

# 위 내용을 groupby 를 사용하면 간편하고 빠르다.
# 같은 STNAME 을 갖는 데이터까리 그룹핑
# 그룹핑은 루프를 돌면 그룹명(group), 그룹데이터(frame)를 파악할 수 있다.
for group, frame in df.groupby('STNAME'):
    av = np.average(frame['CENSUS2010POP'])
    print('Counties in state ' + group +
          ' have an average population of ' + str(avg))
print()


# STNAME 을 인덱스로 설정
df2 = df.set_index('STNAME')


def fun(item):
    # item 첫글자가 A~O 인경우
    if item[0] < 'M':
        # print('< M', item)
        return 0
    # item 첫글자가 M~P 인경우
    if item[0] < 'Q':
        # print('< Q', item)
        return 1
    return 2


# groupby 기준을 컬럼대신 함수로 필터링할 수 있다.
# 함수 호출시 기본 인덱스값이 파라미터로 전달된다.
for group, frame in df2.groupby(fun):
    print('There are ' + str(len(frame)) +
          ' records in group ' + str(group) + ' for processing.')

# 위 예시 groupby 없이 series 로 구분하는 방법
aa = df['STNAME'].apply(lambda x: 0 if x[0] < 'M' else 1 if x[0] < 'Q' else 2)
print(type(aa))
print(aa.value_counts())


# STNAME 으로 그룹핑 후 CENSUS2010POP 의 평균을 aggregate(집계)
print(df.groupby('STNAME').agg({'CENSUS2010POP': np.average}))


# 컬럼 2개 이상이면 2차원의 DataframeGroupBy 타입
# 인덱스가 1개라면 level=0
print(type(df.groupby(level=0)['POPESTIMATE2010', 'POPESTIMATE2011']))
# 컬럼 1개면 1차원의 SeriesGroupBy 타입
print(type(df.groupby(level=0)['POPESTIMATE2010']))

# STNAME 인덱싱 후
# level=0 인덱스로 그룹핑 후
# CENSUS2010POP 의 평균, 합을 avg, sum 컬럼 이름으로 aggregate(집계)
# 참고로 agg 에 dict{}형태는 deprecated 될 예정이다.
# using a dict on a Series for aggregation is deprecated and will be removed in a future version
print(df.set_index('STNAME').groupby(level=0)['CENSUS2010POP']
      .agg({'avg': np.average, 'sum': np.sum}))

# POPESTIMATE2010, POPESTIMATE2011 2개의 컬럼을 집계
print(df.set_index('STNAME').groupby(level=0)['POPESTIMATE2010', 'POPESTIMATE2011']
      .agg({'avg': np.average, 'sum': np.sum}))

# POPESTIMATE2010 는 평균만, POPESTIMATE2011 는 합만 집계
print(df.set_index('STNAME').groupby(level=0)['POPESTIMATE2010', 'POPESTIMATE2011']
      .agg({'POPESTIMATE2010': np.average, 'POPESTIMATE2011': np.sum}))
