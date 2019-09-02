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
# csv 파일의 나라명(첫번째)을 인덱스로 한다.
df = pd.read_csv('olympics.csv', skiprows=1, index_col=0)
# Totals 라인은 제거하고 시작
df = df.drop('Totals')
# '(' 부분제거
names_ids = df.index.str.split('\s\(')
# names_ids.str[0] 는 나라이름이 들어 있다.
df.index = names_ids.str[0]
# 3자리수 나라명을 ID 컬럼으로 추가
df['ID'] = names_ids.str[1].str[:3]
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


# 하계올림픽 금메달 가장 많이 딴 나라
def answer_one_1():
    maxi = 0
    max_country = ""
    for index, row in df.iterrows():
        if row['Gold'] > maxi:
            maxi = row['Gold']
            max_country = index
    return max_country


print(answer_one_1())


# 하계올림픽 금메달 가장 많이 딴 나라(gold 인덱싱해서 처리)
# 인덱스 변경전 현재의 인덱스(나라명)을 값을 컬럼으로 보존하기
# 인덱스 소팅후 마지막 인덱스의 나라 리턴
def answer_one_2():
    df2 = df.copy()
    df2['Country'] = df2.index
    df2 = df2.set_index('Gold')
    return df2.loc[df2.sort_index().index[-1]]['Country']


print(answer_one_2())


# 하계올림픽 금메달 가장 많이 딴 나라
# idxmax() 는 Gold 컬럼의 숫가 최대인 인덱스를 리턴한다.
def answer_one():
    return (df['Gold'].idxmax())


print(answer_one())


# 하계올림픽과 동계올림픽의 차이가 가장 큰 나라
def answer_two():
    return (abs(df['Gold'] - df['Gold.1']).idxmax())


print(answer_two())


# 전체 금메달중 하계 동계 금메달 차이가 가장 큰나라
# 하계, 동계 금메달이 0 인 경우 제외
def answer_three():
    df2 = df.copy()
    for index, row in df2.iterrows():
        if row['Gold'] == 0 or row['Gold.1'] == 0:
            df2 = df2.drop(index)

    return ((abs(df2['Gold'] - df2['Gold.1'])/df2['Gold.2']).idxmax())


print((answer_three()))


# 금,은,동 각 3,2,1 가중치를 부한 점수를 가진 series 생성
def answer_four():
    return pd.Series((df['Gold.2'] * 3) + (df['Silver.2'] * 2) + (df['Bronze.2'] * 1))


print(type(answer_four()))
print(answer_four())
