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

# 나라(index)별 금메달 획득 여부 파악
# Gold 컬럼에 boolean masking
print(df['Gold'] > 0)

# 금메달을 딴 나라들만 별도의 dataframe 으로 만들 수 있다.
only_gold = df.where(df['Gold'] > 0)
print("only_god =\n", only_gold)

print("df['Gold'].count = ", df['Gold'].count())
print("only_gold['Gold'].count = ", only_gold['Gold'].count())

# NaN 행들지우기, dropna(1)은 NaN 열들지우기
only_gold = only_gold.dropna()
print("only_god =\n", only_gold)
print()

# 하계올림픽(Gold) or 동계올림픽(Gold.1)  에서 금메달 딴 나라
print("(df[(df['Gold'] > 0) | (df['Gold.1'] > 0)]) = \n",
      (df[(df['Gold'] > 0) | (df['Gold.1'] > 0)]))
print()

# 하계올림픽(Gold) 금메달 못 따고 and 동계올림픽(Gold.1) 금메달 딴 나라
print("(df[(df['Gold'] == 0) & (df['Gold.1'] > 0)]) = \n",
      (df[(df['Gold'] == 0) & (df['Gold.1'] > 0)]))
print()


# 인덱스 변경하기
# 인데스 변경전 현재의 인덱스(나라명)을 값을 컬럼으로 보존하기
df['Country'] = df.index
# 인덱스는 컬럼중에 선택할 수 있다.
# Gold 컬럼을 인덱스로 하고 Gold 자체가 인덱스의 이름이 된다.
df = df.set_index('Gold')
print("df.set_index('Gold') = \n", df)
print()

# 인덱스를 리셋하면 디폴트로 숫자 카운트 인덱스가 된다.
df = df.reset_index()
print("df.reset_index() = \n", df)
print()
