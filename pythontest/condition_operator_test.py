# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 삼항연산자 테스트

# and or 로 삼항연산
a = 'yoon'
out = a == 'ysoftman' and 'true' or 'false'
print out

a = 'ysoftman'
out = a == 'ysoftman' and 'true' or 'false'
print out

# if else 로 삼항연산(2.5부터 지원)
a = 'yoon'
out = 'true' if a == 'ysoftman' else 'false'
print out

a = 'ysoftman'
out = 'true' if a == 'ysoftman' else 'false'
print out
