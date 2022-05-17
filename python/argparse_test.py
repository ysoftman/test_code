# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : argparse 테스트

import argparse


# *args : arguments 로 여러개의 인자를 받아 tuple 로 처리
# **kwargs : keyword arguments 로 여러개의 인자를 받아 dictionary 로 처리
def generalArg(*args, **kwargs):
    print("args:", args)
    for i in range(len(args)):
        print(f"args[{i}]: {args[i]}")
    print(kwargs)
    print(kwargs.get("a", "a_devault_value"))
    print(kwargs.get("b", "b_default_value"))
    print(kwargs.get("c", "c_default_value"))
    print(kwargs.get("d", ""))  # default value: empty
    print(kwargs.get("e"))  # default value: None
    for k, v in kwargs.items():
        print(f"kwargs[{k}]: {v}")


def ArgParse():
    print("parse argument test")

    parser = argparse.ArgumentParser()
    # 사용할 수 있는 아큐먼트 키 추가(자동으로 usage, -h help 포맷 생성)
    # help : -h 시 표시할 문구
    parser.add_argument("-a", help="any value1")
    # required : -b 옵션은 꼭 필요한지 설정
    parser.add_argument("-b", required=False, help="any value2")
    # -v 의 값은 명시된것으로 처리
    parser.add_argument("-v", action="store_true", help="verbose")

    # 아규먼트 파싱하기
    args = parser.parse_args()

    return args


if __name__ == "__main__":
    # 빌트인 사용시
    generalArg(123, 456, 123, a=123, b="ysoftman")

    # argparse 사용시
    args = ArgParse()
    # 옵션 예시
    # python argparse_test.py -h
    # python argparse_test.py -a=1
    # python argparse_test.py -a=1 -b 2
    print(args.a)
    print(args.b)
