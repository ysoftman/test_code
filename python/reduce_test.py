# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : reduce


from functools import reduce


data = [1, 2, 3, 4, 5]
print(f"data:{data}")


def add(a, b):
    return a + b


# reduce(집계함수, 순회 가능한 데이터, 초기값(optional))
print(reduce(add, data, 10))
print(reduce(add, data))


data = [
    {"name": "apple", "cost": 100},
    {"name": "lemon", "cost": 200},
    {"name": "orange", "cost": 300},
]
print(f"data:{data}")


# acc 초기값 0설정 필요
print(reduce(lambda acc, d: acc + d["cost"], data, 0))

# acc 초기값 ""설정 필요
print(
    reduce(
        lambda acc, d: acc + d["name"] if len(acc) == 0 else acc + " " + d["name"],
        data,
        "",
    )
)
