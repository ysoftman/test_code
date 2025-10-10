# ysoftman
# python versioni 3.9


import time
from functools import cache


def factorial(n) -> int:
    if n == 0 or n == 1:
        return n
    return n * factorial(n - 1)


# lru 기반 최 1000 계산 결과를 캐싱
# @functools.lru_cache(maxsize=1000)
# 제한없이 캐싱
@cache
def factorial_using_cache(n) -> int:
    if n == 0 or n == 1:
        return n
    return n * factorial(n - 1)


start = time.perf_counter()
print(factorial(100))
print(time.perf_counter() - start)

start = time.perf_counter()
print(factorial_using_cache(100))
print(time.perf_counter() - start)
