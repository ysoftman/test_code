# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : regular expression test

import re


def do_regular_expression():
    data = """bill 777-999-111
ysoftman 123-456-789
aabill 777-999-111
billyoon 777-999-111
"""
    print(data)

    # bi 로시작하는 단어 찾기(정규식문자는 raw string 으로)
    print(re.findall(r"^bi\w*", data))
    # 멀티라인의 경우 각 ^ 는 각 라인의 처음을 의미
    print(re.findall(r"^bi\w*", data, re.MULTILINE))

    # bill 부분을  z 로 변경
    print(re.sub("bill", "z", data))


if __name__ == "__main__":
    do_regular_expression()
