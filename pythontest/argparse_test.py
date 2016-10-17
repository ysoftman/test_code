# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : argparse 테스트 

import argparse


def ArgParse():
    print "parse argument test"

    parser = argparse.ArgumentParser()
    # 사용할 수 있는 아큐먼트 키 추가(자동으로 usage, -h help 포맷 생성)
    # help : -h 시 표시할 문구
    parser.add_argument("-a", help = "any value1")
    # required : -b 옵션은 꼭 필요한지 설정
    parser.add_argument("-b", required=False, help = "any value2")
    # -v 의 값은 명시된것으로 처리
    parser.add_argument("-v", action="store_true", help="verbose")

    # 아규먼트 파싱하기
    args = parser.parse_args()

    return args

if __name__ == '__main__':
    args = ArgParse()

    # 옵션 예시 
    # python argparse_test.py -h
    # python argparse_test.py -a 1 -b 2
    # python argparse_test.py -a 1
    print args.a
    print args.b


