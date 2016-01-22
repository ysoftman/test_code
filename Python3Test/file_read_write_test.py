# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : 파이썬 기본 테스트

# import os
# import sys


def test_file_write(val):
    myfile = open('test.txt', "w")
    for idx in range(1, 5):
        # 숫자를 문자열로 변경하여 문자열 합치기
        strMsg = str(idx) + " " + val + "\n"
        # write 함수를 통한 파일 쓰기
        myfile.write(strMsg)
        # print 함수를 통한 파일 쓰기
        print(strMsg, end='', file=myfile)
    myfile.close()
    return None


def test_file_read():
    myfile = None
    try:
        myfile = open("test.txt", "r")
        linebuffer = myfile.readlines()
        for temp in linebuffer:
            print(temp, end='')
    except IOError as err:
        print("can't open file...." + str(err))
        pass
    finally:
        if myfile is not None:
            myfile.close()


test_file_write("파일에 쓰기 테스트")
test_file_read()
