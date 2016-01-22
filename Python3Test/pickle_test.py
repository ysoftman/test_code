# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : 피클 라이브러리 테스트

import pickle

def test_pickle_dump(filename, data):
    # with 를 사용하면 close 따로 처리 필요 없음
    # 피클링 데이터 파일은 바이너리모드로 read/write
    with open(filename, "wb") as dumpfile:
        pickle.dump(data, dumpfile)


def test_pickle_load(filename):
    try:
        with open(filename, "rb") as dumpfile:
            data = pickle.load(dumpfile)
            return data
    except IOError as err:
        print(str(err))



# 피클링 저장 및 로드 테스트

val1 = ["한글", 123, "bbb" ]

strFileName = "dump_test"
test_pickle_dump(strFileName, val1)

val1 = test_pickle_load(strFileName)
print(val1)


