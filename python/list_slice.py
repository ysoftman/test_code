# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 리스트 테스트


def test_print_list(val):
    #     print("func1")
    for idx in val:
        # 리스트가 형식이면
        if isinstance(idx, list):
            test_print_list(idx)
        else:
            print("element = ", idx)


# list(리스트)는 []로 표현
val1 = ["한글", 123, "bbb"]
fruits_list = ["apple", "banana", "grape", "lemon", "fineapple"]

# 특정 위치 원소 삭제하기
del val1[0]

# 끝에 원소 추가
val1.append("korean")

# 특정 위치에  원소 추가
val1.insert(0, "english")

# 값으로 원소 삭제
val1.remove("english")

# 원소 위치 파악
print("index of 'bbb' =", val1.index("bbb"))

# 리스트에 리스트 추가
val1.extend(fruits_list)

# 리스트 내용 출력
test_print_list(val1)

print("------")

# list() builtin 함수로 리스트 만들기
# empty list
print("list() = ", list())
print("list('abcdefghij') =", list("abcdefghij"))
print("list('123456789') =", list("123456789"))
print("list(var+'0' for var in '123456789') =", list(var + "0" for var in "123456789"))

# list comprehensions(파이썬에서는 함축 이라는 의미로 사용한다.)로 리스트 만들기
print("[i for i in range(1, 10)] =", [i for i in range(1, 10)])

print("------")

val1 = [8, 7, 6, 5, 4, 3, 2, 1]
# val1 리스트 출력
print(val1)

# 리스트는 slicing(슬라이싱)이 가능하다.
# slice(start:stop[:step]) 의 형태(step 은 optional)
# 모든 요소
print(val1[:])
# 마지막 요소
print(val1[-1])
# 마지막 두번째 요소
print(val1[-2])
# 2~3번째만
print(val1[2:4])
# 4번째 이전(0~3)까지
print(val1[:4])
# 모든 요소에 대해서 1씩 증가하는 위치
print(val1[::])
# 모든 요소에 대해서 2씩 증가하는 위치
print(val1[::2])
# 0~4 위치에 대해서 2씩 증가하는 위치
print(val1[0:5:2])
# 모든 요소에 대해서 뒤에서 부터 -1씩 증가하는 위치
print(val1[::-1])
# 모든 요소에 대해서 뒤에서 부터 -2씩 증가하는 위치
print(val1[::-2])

print("------")

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
# list append(), pop() 으로 stack 처럼 사용가능
val1.pop()
print(val1)
