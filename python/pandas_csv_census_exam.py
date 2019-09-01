# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


print("load census.csv ... ")
print()

# csv 파일 읽기
census_df = pd.read_csv('census.csv')
print("census_df.head()=\n", census_df.head(), sep="")
print()


# County 가 가장 많은 state 파악
# SUMLEV(Summary Level) 인구 통계청에서 지역구분에 쓰는 코드다
# 040 : state
# 050 : county
# 140 : census trac
# 참고 https://blog.cubitplanning.com/2011/03/census-summary-level-sumlev/

def answer_five():
    # index 가 여러개 있을때 count 의 level 옵션사용
    return census_df.set_index(['SUMLEV', 'STNAME']).count(level='STNAME')['COUNTY'].idxmax()


print(answer_five())


# 인구가 가장 많은 county 3개 찾기(CENSUS2010POP 컬럼 사용)
def answer_six():
    return census_df.set_index('CENSUS2010POP').sort_index(ascending=False)[:3]['CTYNAME'].values


print(type(answer_six()))
print(answer_six())


# 2010~2015 까지 인구 변화가 가장 큰 County 찾기
# POPESTIMATE2010 ~ POPESTIMATE2015 6개 컬럼 모두 고려
# ex) 5 year period is 100, 120, 80, 105, 100, 130, then its largest change in the period would be |130-80| = 50.
def answer_seven():
    columns_to_keep = ['CTYNAME',
                       'POPESTIMATE2010',
                       'POPESTIMATE2011',
                       'POPESTIMATE2012',
                       'POPESTIMATE2013',
                       'POPESTIMATE2014',
                       'POPESTIMATE2015']
    cdf = census_df[columns_to_keep].set_index('CTYNAME')
    # print(cdf.loc[cdf.index[0]])
    # print(cdf.loc['Texas'])
    cdf['max_pop'] = cdf.max(axis=1)
    cdf['min_pop'] = cdf.min(axis=1)
    cdf['gap'] = cdf['max_pop'] - cdf['min_pop']
    # sort_values 는 column 값으로 소팅할때 사용
    # print(cdf['gap'].sort_values())
    return cdf['gap'].idxmax()


print(answer_seven())


# REGION 이 1 또는 2 에 속하고 CTYNAME 가 Washington 이름으로 시작하고
# POPESTIMATE2015 > POPESTIMATE2014 보다 큰
# ['STNAME', 'CTYNAME'] 컬럼을 가지는 5x2 dateframe (인덱스 오름차순) 을 리턴
def answer_eight():
    cdf = census_df[['STNAME', 'CTYNAME', 'REGION',
                     'POPESTIMATE2014', 'POPESTIMATE2015']]
    cdf = cdf[((cdf['REGION'] == 1) | (cdf['REGION'] == 2)) &
              (cdf['CTYNAME'].str.startswith('Washington')) &
              (cdf['POPESTIMATE2015'] > cdf['POPESTIMATE2014'])]

    return cdf[['STNAME','CTYNAME']]


print(answer_eight())
print(type(answer_eight()))
