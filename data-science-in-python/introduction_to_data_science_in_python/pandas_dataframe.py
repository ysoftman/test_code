# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


# dataframe 은 데이터들을 컬럼 모양으로 묶어 표처럼 나탄낸다.
# 시리즈의를 묶어 2차원의 dataframe 구조를 만들 수 있다.
dic1 = {"name": "jane", "fruit": "lemon", "price": 1000}
dic2 = {"name": "bill", "fruit": "orange", "price": 2000}
dic3 = {"name": "tom", "fruit": "apple", "price": 3000}
dic4 = {"name": "alice", "fruit": "banana", "price": 4000}
s1 = pd.Series(dic1)
s2 = pd.Series(dic2)
s3 = pd.Series(dic3)
s4 = pd.Series(dic4)
# df1 = pd.DataFrame([dic1, dic2, dic3, dic4],  index=['user1', 'user2', 'user3', 'user4'])
df1 = pd.DataFrame([s1, s2, s3, s4], index=[
                   'user1', 'user2', 'user3', 'user4'])
print("df1=\n", df1, sep="")
print("df1['name'] =\n", df1['name'], sep="")
print()

# row (lable) 인덱싱 방법1
print("df1['user2'] =\n", df1.loc['user2'], sep="")
# row (lable) 인덱싱 방법2, loc 를 사용하길 권고한다.
print("df1.loc['user2'] =\n", df1.loc['user2'], sep="")
print("df1.loc['user2']['price'] = ", df1.loc['user2']['price'])
print()

print("type(df1) = ", type(df1))
print("type(df1.loc['user2']) = ", type(df1.loc['user2']))
print()

# transpose 해서 row col 위치를 바꾼다.
print("df1.T=\n", df1.T, sep="")
print("df1.T.loc['fruit']['user1'] =\n", df1.T.loc['fruit']['user1'], sep="")
print()

# 차원별 슬라이싱
print("df1.loc[:, ['fruit', 'price']] =\n",
      df1.loc[:, ['fruit', 'price']], sep="")
print()

# 값 업데이트
df1['price'] *= 0.8
print("df1=\n", df1, sep="")
print()

# 컬럼 추가
df1["date"] = None
print("df1=\n", df1, sep="")
print()

# 다중 컬럼만 조회
print("df1[['name','price']]=\n", df1[['name', 'price']], sep="")
print("type(df1[['name','price']])=\n", type(df1[['name', 'price']]), sep="")
# 인덱스 제외하고 출력
print("df1[['name','price']].values=\n", df1[['name', 'price']].values, sep="")
print("type(df1[['name','price']].values)=\n",
      type(df1[['name', 'price']].values), sep="")
print()

# 복사하기
df2 = df1.copy()
print("df2=\n", df2, sep="")
# 레이블로 관련 데이터 삭제
# axis = 0 이면 row, 1이면 col 기준의 label
# inplace = True 현재 df 를 drop 내용을 반영한다.(df2 = df2.drop('user3') 와 같다.)
df2.drop('user3', axis=0, inplace=True)
print("df2 =\n", df2, sep="")
print()

# 컬럼 이름 fruit -> my-favorite-fruits 바꾸기
df2.rename(columns={'fruit': 'my-favorite-fruits'}, inplace=True)
print("df2 =\n", df2, sep="")
print()

# 인덱스 이름 바꾸기
df2.index.name = "new_index"
# df2.index.names = ["new_index"]
print("df2 =\n", df2, sep="")
print()
