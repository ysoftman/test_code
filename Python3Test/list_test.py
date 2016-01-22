# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : 리스트 테스트

#import os
#import sys

def test_print_list(val):
#     print("func1")
    for idx in val:
        # 리스트가 형식이면
        if isinstance(idx, list):
            test_print_list(idx)
        else:
            print("element = ", idx)


val1 = ["한글", 123, "bbb" ]

#  리스트 내용 출력
test_print_list(val1)

val1 = "한글 , def , 123 ,456"

# 구분자로 구분하기
print(val1.split(","))


val1 = [7,8,6,8,4,3,2,1]
# va1 리스트 출력
print(val1)

# 2~3번째만 출력하기
print(val1[2:4])

# 원본 데이터는 그대로 두고 val2 에 정렬
val2 = sorted(val1)
print(val2)
print(val1)

# 원본 데이터 자체를 오름 차순 정렬
val1.sort(key=None, reverse=False)
print(val1)

# 원본 데이터 자체를 내림 차순 정렬
val1.sort(key=None, reverse=True)
print(val1)

# 중복 데이터 제거
val1 = set(val1)
print(val1)

# 마지막 원소 삭제
val1.pop()
print(val1)

