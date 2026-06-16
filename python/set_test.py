# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : set 테스트

data = ["aaa", "bbb", "aaa", "ccc"]
print(list(data))
# set 은 중복 데이터를 제거한다.(순서없음)
set_data = set(data)
print(set_data)

# element 추가
set_data.add("lemon")
set_data.add("banana")
set_data.add("lemon")  # 중복 추가 안된다.
print(set_data)

# element 제거
set_data.remove("banana")
print(set_data)

# set 을 추가
set_data.update(set(["aaa", "zzz"]))
print(set_data)

# y, o 를 원소하는 set 을 추가
set_data.update("yo")
print(set_data)

# subset 여부 확인
if set(["aaa", "ccc"]).issubset(set_data):
    print("issubset == true")
else:
    print("issubset == false")
print(set_data)

# 임의의 element 제거
set_data.pop()
set_data.pop()
print(set_data)

# element 모두 제거
set_data.clear()
print(set_data)


# set([1, 3, 5]) 는 옛날 스타일(Python 2.6 이하). 2.7/3.1 부터 set 리터럴 {1, 3, 5} 사용 권장 (ruff C405).
# 단 빈 set 은 리터럴 표기가 없어서 set() 가 유일한 방법 (빈 {} 는 버전 무관 영원히 dict). set([]) 는 결과는 같지만 불필요한 형태.
seta = set([1, 3, 5])
setb = {1, 2, 4}
print(seta)
print(setb)

# 합집합
setc = seta | setb
print(setc)
setc = seta.union(setb)
print(setc)

# 차집합
setc = seta - setb
print(setc)
setc = seta.difference(setb)
print(setc)

# 교집합
setc = seta & setb
print(setc)
setc = seta.intersection(setb)
print(setc)
