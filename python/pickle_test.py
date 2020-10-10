# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 피클 라이브러리 테스트

import pickle


def test_pickle_dump(filename, data):
    # with (2.5 부터 지원)를 사용하면 블록 종료시 자동으로 close() 를 호출한다.
    # 클래스 경우 블럭의 시작,종료시 각각 __enter__() __exit__() 가 자동으로 호출되어
    with open(filename, "wb") as dumpfile:
        # 피클링 데이터 파일은 바이너리모드로 read/write
        pickle.dump(data, dumpfile)


def test_pickle_load(filename):
    try:
        with open(filename, "rb") as dumpfile:
            data = pickle.load(dumpfile)
            return data
    except IOError as err:
        print(str(err))


# 피클링 저장 및 로드 테스트
val1 = ["한글", 123, "bbb"]

strFileName = __file__ + ".dump"
test_pickle_dump(strFileName, val1)

val1 = test_pickle_load(strFileName)
print(val1)
print(val1[0])
print(val1[1])
print(val1[2])
