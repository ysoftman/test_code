# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : list comprehensions test

# 영문2자리 숫자2자리의 가능한 모든 id 생성하기(eg. aa11)
import random

lowercase = "abcdefghijklmnopqrstuvwxyz"
digits = "0123456789"
# for l1 in lowercase:
#     for l2 in lowercase:
#         for d1 in digits:
#             for d2 in digits:
#                 print(l1+l2+d1+d2)

# list comprehensions(파이썬에서는 함축 이라는 의미로 사용한다.) 방법
answer = [
    l1 + l2 + d1 + d2
    for l1 in lowercase
    for l2 in lowercase
    for d1 in digits
    for d2 in digits
]
print(answer)


# 1~100 랜덤숫자 100개의 리스트 생성
rlist = [random.randint(1, 100) for i in range(100)]
print("rlist=", rlist)
# if else 모두 써양 하는 경우
# 90 이상인곳 표시
print("rlist=", [i if i >= 90 else "_" for i in rlist])
# else 없이 if 만 쓸 경우
# 90 이상인 숫자들만 리스트로 담기
print("rlist=", [i for i in rlist if i >= 90])
