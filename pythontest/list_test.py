# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
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

# 특정 위치 원소 삭제하기
del val1[0]

# 끝에 원소 추가
val1.append('korean')

# 특정 위치에  원소 추가
val1.insert(0, 'english')

# 값으로 원소 삭제 
val1.remove('english')

# 원소 위치 파악
print "index of 'bbb' =", val1.index('bbb')

# 리스트 내용 출력
test_print_list(val1)



# 튜플(원소 수정 불가)
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

