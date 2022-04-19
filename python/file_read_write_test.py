# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 파이썬 기본 테스트

import os
# import sys

filename = os.path.basename(__file__)
filename += ".text"


def test_file_write(val):
    myfile = open(filename, "w", encoding="utf8")
    for idx in range(1, 5):
        # 숫자를 문자열로 변경하여 문자열 합치기
        strMsg = str(idx) + " " + val + "\n"
        # write 함수를 통한 파일 쓰기
        myfile.write(strMsg)
        # print 함수를 통한 파일 쓰기
        # 3.x
        # print(strMsg, end='', file=myfile)
        # print(strMsg, end='', file=sys.stdout)
        # print(strMsg, end='', file=sys.stderr)
        # 2.x
        myfile.write(strMsg)
    myfile.close()
    return None


def test_file_read1():
    myfile = open(filename, "r")
    line = myfile.readline()
    while line:
        print(line)
        # 라인별 읽기
        line = myfile.readline()


def test_file_read2():
    myfile = None
    try:
        myfile = open(filename, "r")
        # 버퍼로 한번에 읽어 놓기
        linebuffer = myfile.readlines()
        for temp in linebuffer:
            # 3.x
            # print(temp, end='')
            # 2.x
            print(temp)
    except IOError as err:
        print("can't open file...." + str(err))
        # pass 아무것도 하지 않고 그냥 넘어간다.
        # 위 print 없다면 에러가 발생하기 때문에 pass 로 존재만 유지
        pass
    except Exception as err:
        print("알수 없는 에러 발생!" + str(err))
    finally:
        if myfile is not None:
            myfile.close()


test_file_write("파일에 쓰기 테스트")
print('-----')
test_file_read1()
print('-----')
test_file_read2()
os.remove(filename)
