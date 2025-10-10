# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : arr init test

# aaaaaaaaaa 생성
arr_str = "a" * 10
print(type(arr_str))
print(arr_str)

print("-----")

# 값이 0인 원소 10개를 생성
arr1 = [0] * 10
print(type(arr1))
arr1[1] = 0
arr1[1] = 1
arr1[2] = 2
print(arr1)

print("-----")


# 값이 0인 2차원 배열 생성
# 2d array 에서 * 로 생성하면 shallow list 라 실제 오브젝트 1개를 참조하게 된다.
# https://www.geeksforgeeks.org/python-using-2d-arrays-lists-the-right-way/
arr2 = [[0, 0]] * 10
# 또는
arr2 = [[0] * 2] * 10
print(type(arr2))
arr2[0][0] = 2
# 원소의 주소값을 보면 모두 같아서 하나를 바꾸면 모두 바뀌게 된다.
print(id(arr2[0]))
print(id(arr2[1]))
print(arr2)

print("-----")

# 값이 0인 2차원 배열 arr comprehension 방식으로 생성
arr2_arr_comprehension = [[0, 0] for _ in range(10)]
print(type(arr2_arr_comprehension))
# 원소의 주소값이 모두 다르다.
print(id(arr2_arr_comprehension[0]))
print(id(arr2_arr_comprehension[1]))
arr2_arr_comprehension[0][0] = 2
print(arr2_arr_comprehension)
