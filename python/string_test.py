# -*- coding: utf-8 -*-
# author : ysoftman
# title : string test
# python version : 2.x
import sys


def modify_data(str):
    str = 'kkk'
    print 'modified'
    return str


if __name__ == '__main__':

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
byoung
hoon"""
    print str

    str = '''yoon
byoung
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

    str = modify_data(str)
    print 'str =', str
    print 'str2 =', str2

    str = 'yOOn Byoung hooN'
    print str
    # 모두 소문자로
    str = str.lower()
    print str
    # 모두 대문자로
    str = str.upper()
    print str
    # 첫문자만 대문자로
    str = str.capitalize()
    print str

    str = "윤\n병\n훈"
    print 'str = {}'.format(str)
    # raw 문자: escape 문자의 기능이 적용되지 않고 문자 그대로 출력
    str = r"윤\n병\n훈"
    print 'str = {}'.format(str)

    # 멀티라인에서 포맷팅
    str = """
        "number:{},
        "name":{}
    """.format(123, "ysoftman")
    print 'str =', str

    # 멀티라인에서 {} 자체를 출력하기 위해선 {{ }} 사용
    str = """
    {{
        "number:{},
        "name":{}
    }}
    """.format(123, "ysoftman")
    print 'str =', str
