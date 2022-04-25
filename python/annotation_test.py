# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.5 이상
# desc : annotation(type hint) 테스트

# annotation 은 힌트일 뿐이라서 실제 타입이 달라로 에러가 발생하진 않는다.
# a: int = "1" # 변수 타입 힌트를 명시할대는 : 타입사용
a: int = 1
b: str = "ysoftman"
# 리턴 타입을 힌트로 명시할때는 -> 사용
def func1(param1: int, param2: float, param3: str) -> bool:
    print("{}-{}-{}".format(param1, param2, param3))
    return True


if __name__ == "__main__":
    ret = func1(123, 1.23, "lemon")
    print("ret:", ret)
    # 파이썬은 동적타이핑이라 param1 int 타입이라도 힌트(annotation)이 있지만 실제 다른 값을 넘길 수도 있다.
    ret = func1("apple", 1.23, 999)
    print("ret:", ret)
