# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.6
# desc : iter, next test

# 연속 데이터에를 iter 객체로 만들면 next 로 하나씩 순회 할 수 있다.
val1 = iter(range(5))
print(f"val1:{val1}")
# 현재 원소를 리턴하고 다음 원소로 이동
x = next(val1)
print(x)
x = next(val1)
print(x)
x = next(val1)
print(x)

print("------")
val1 = iter(["apple", "lemon", "orange"])
print(f"val1:{val1}")
x = next(val1)
print(x)
x = next(val1)
print(x)
x = next(val1)
print(x)
# x = next(val1) # iter 마지막을 지났기 때문에 StopIteration 예외 발생
x = next(val1, "aaa")  # StopIteration 발생 하지 않고 기본값 aaa 반환
print(x)

print("------")
val1 = iter(["apple", "lemon", "orange"])
# lemon 값까지 반복
ret = next(e for e in val1 if e == "lemon")
print(f"ret:{ret}")
