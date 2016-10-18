# -*- coding: utf-8 -*-
# author : ysoftman
# title : string test
# python version : 2.x
import sys


# 큰 따옴표 "  를 포함 시키고 싶을때
str = '"ysoftman"'
print str

# 작은 따옴표 ' 를 포함시키고 싶은 경우
str = "'ysoftman'"
print str

# 여러줄로 표현하고 싶은 경우
str = 'yoon\nbyoung\nhoon'
print str

# 이스케이프 문자 없이 여러줄료 표현하고 싶은 경우
str = """yoon
byhoun
hoon"""
print str

str = '''yoon
byhoun
hoon'''
print str


# 스트링 포맷팅
data = {'first': 'bill', 'second': 'yoon'}
print '{first} {second}'.format(**data)
print "{first} {second}".format(**data)


# 스트링 복사
str = 'abc'
str2 = str
print 'str =', str
print 'str2 =', str2

str = 'zzz'
print 'str =', str
print 'str2 =', str2



