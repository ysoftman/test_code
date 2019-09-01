# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd

fruits = ["lemon", "orange", "apple"]
print("fruits = ", fruits)
# series(시리즈)는 키를 가지는 리스트의 1차원자료 구조다.
# 시리즈의를 묶어 2차원의 dataframe 구조를 만들 수 있다.
print("pd.Series(fruits) =\n", pd.Series(fruits), sep="")
print()

# int 리스트를 가지고 있는 시리즈
numbers = [1, 2, 3]
print("numbers = ", numbers)
print("pd.Series(numbers) =\n", pd.Series(numbers), sep="")
print()

# None 은 NaN(Not A Number:표현 불가능한 수치)로 표현된다.
# NaN 으로 float 값으로 처리된다.
floats = [1, 2, None]
print("floats = ", floats)
print("pd.Series(floats) =\n", pd.Series(floats), sep="")
print("pd.Series(floats).name =\n", pd.Series(floats).name, sep="")
print()

# 시리즈에 추가하기
fruits1 = pd.Series(fruits, name="new1")
fruits2 = pd.Series(["strawberry", "watermelon", "mango"], name="new2")
fruits3 = pd.Series(["aa", "cc"], name="new3")
fruits1 = fruits1.append(fruits2)
fruits1 = fruits1.append(fruits3)
print("fruits1 =\n", fruits1, sep="")
print("fruits1[1] =\n", fruits1[1], sep="")
print()

# dictionary -> series
fruitsDict = {"lemon": 9000, "apple": "7000", "orange": "5000"}
print("fruitsDict = ", fruitsDict)
print("pd.Series(fruitsDict) =\n", pd.Series(fruitsDict), sep="")
print()

fs = pd.Series(fruitsDict)
# 현재 index
print("fs.index = ", fs.index)
# index 새로 지정할 수 있고
# index 를 지정하지 않는 값은 사라지고(무효화)  => orange
# index 에 해당하는 값이 없으면 NaN 또는 None 이된다. => banana
fs2 = pd.Series(fs, index=["lemon", "apple", "banana"])
print("fs =\n", fs, sep="")
print("fs2 = \n", fs2, sep="")
print()

# label 로 시리즈 인덱싱, 슬라이싱
print('fs.loc["apple"]', fs.loc["apple"])
print('fs.loc["lemon":"orange"]', fs.loc["lemon":"orange"])
# 위치 로 시리즈 인덱싱, 슬라이싱
print('fs.iloc[1]', fs.iloc[1])
print('fs.iloc[0:]', fs.iloc[0:])
# 일반 인덱싱으로도 되지만 2차원이상의 데이터에서는 키 에러가 발생한다.
# print('fs["apple"]', fs["apple"])
# print('fs[1]', fs[1])
# 값 추가
# fs['id'] = 'ysfotman'
fs.loc['id'] = 'ysfotman'
print("fs =\n", fs, sep="")
print()

# 10000 개의 데이터를 담은 시리즈 생성
rs = pd.Series(np.random.randint(1, 100, 10000))
print("len(rs) = ", len(rs))
# 앞부분과 뒤부분 데이터 보기
print("rs.head() =\n", rs.head(n=10), sep="")
print("rs.tail() =\n", rs.tail(), sep="")
print()

# rs 데이터에 일괄 연산 적용
# 다음 처럼 루프를 돌리는것 보다
for k, v in rs.iteritems():
    rs.loc[k] = v + 2
print("rs.tail() =\n", rs.tail(), sep="")
# 벡터화 연산(vectorization operation:루프없이 연산 한번에 끝낸다.)을 지원해 더 빠르다.
rs += 10
print("rs.tail() =\n", rs.tail(), sep="")
