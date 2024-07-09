# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd


df = pd.DataFrame(
    [
        {"Name": "Chris", "Item Purchased": "Sponge", "Cost": 22.50},
        {"Name": "Kevyn", "Item Purchased": "Kitty Litter", "Cost": 2.50},
        {"Name": "Filip", "Item Purchased": "Spoon", "Cost": 5.00},
    ],
    index=["Store 1", "Store 1", "Store 2"],
)
print(df)
print()

df["Date"] = ["December 1", "January 1", "mid-May"]
df["Delivered"] = True
df["Feedback"] = ["Positive", None, "Negative"]
print(df)
print()

# reset_index() 으로 0..n (sequential index) 디폴트 인덱스 설정
# 기존 인덱스 'Store 1', 'Store 1', 'Store 2' 들은 index 컬럼으로 변경된다.
df2 = df.reset_index()
# Date 컬럼 값을 시리즈로 각 인덱스별 값을 지정할 수 있다.
# 1번 인덱스에 해당하는 값이 없어 1: NaN으로 표기된다.
df2["Date"] = pd.Series({0: "December 1", 2: "mid-May"})
print(df2)
print()


staff_df = pd.DataFrame(
    [
        {"Name": "Kelly", "Role": "Director of HR"},
        {"Name": "Sally", "Role": "Course liasion"},
        {"Name": "James", "Role": "Grader"},
    ]
)
staff_df = staff_df.set_index("Name")
student_df = pd.DataFrame(
    [
        {"Name": "James", "School": "Business"},
        {"Name": "Mike", "School": "Law"},
        {"Name": "Sally", "School": "Engineering"},
    ]
)
student_df = student_df.set_index("Name")
print(staff_df.head())
print()
print(student_df.head())

# outer join(머지) 모든 데이터 합치기, 공통 인덱스가 없어 값이 비게 되는 경우(missing value) NaN(Not A Number) 으로 설정
# join 키로 left_index, right_index 를 사용한다.
print(pd.merge(staff_df, student_df, how="outer", left_index=True, right_index=True))
print()
# left_index=True, right_on="Name" 과 같이 사용할 수도 있다.
print(pd.merge(staff_df, student_df, how="outer", left_index=True, right_on="Name"))
print()
# 여러개의 컬럼을 사용할 경우 left_on=['col1','col2'] 리스트로도 설정할 수 있다.
print(pd.merge(staff_df, student_df, how="left", left_on="Name", right_on="Name"))
print()
# inner join(머지) 공통 인덱스가 있는 경우만 합치기
print(pd.merge(staff_df, student_df, how="inner", left_index=True, right_index=True))
print()
# left join(머지) 왼쪽 기준으로 합치기, 공통 인덱스가 부분은 NaN 으로 설정
print(pd.merge(staff_df, student_df, how="left", left_index=True, right_index=True))
print()
# right join(머지) 오른쪽 기준으로 합치기, 공통 인덱스가 부분은 NaN 으로 설정
print(pd.merge(staff_df, student_df, how="right", left_index=True, right_index=True))
print()
# 인덱스 대신 공통 컬럼 이름으로도 조인 할 수 있다.
print(pd.merge(staff_df, student_df, how="left", on="Name"))
print()

staff_df = pd.DataFrame(
    [
        {"Name": "Kelly", "Role": "Director of HR", "Location": "State Street"},
        {"Name": "Sally", "Role": "Course liasion", "Location": "Washington Avenue"},
        {"Name": "James", "Role": "Grader", "Location": "Washington Avenue"},
    ]
)
student_df = pd.DataFrame(
    [
        {"Name": "James", "School": "Business", "Location": "1024 Billiard Avenue"},
        {"Name": "Mike", "School": "Law", "Location": "Fraternity House #22"},
        {"Name": "Sally", "School": "Engineering", "Location": "512 Wilson Crescent"},
    ]
)
print(staff_df)
print()
print(student_df)
print()
# Name 컬러으로 left 조인시 양쪽에 Location 컬럼이 중복되어
# Location_x(왼쪽컬럼에서 온것) Location_y(오른족에서 온것)으로 컬럼명이 바뀐다.
print(pd.merge(staff_df, student_df, how="left", left_on="Name", right_on="Name"))
print()
