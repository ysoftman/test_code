# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 파이썬 기본 테스트

import os

# import sys

filename = os.path.basename(__file__)
filename += ".text"


def write_file(val):
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


def read_file_by_line():
    myfile = open(filename, "r")
    line = myfile.readline()
    while line:
        print(line)
        # 라인별 읽기
        line = myfile.readline()


def read_file_at_once():
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


def get_file_size():
    with open(filename, "r") as f:
        # fileObject.seek(offset[, whence]) 파일스트림에서 위치 옮기기
        # offset - This is the position of the read/write pointer within the file.
        # whence - This is optional and defaults to 0 which means absolute file positioning, other values are 1 which means seek relative to the current position and 2 means seek relative to the file's end.
        # 파일의 끝에서의 0번째(오프셋) 위치 => 파일 크기
        f.seek(0, 2)
        # 파일 스트림에서의 위치 현재 위치
        return f.tell()


write_file("파일에 쓰기 테스트")
print("-----")
read_file_by_line()
print("-----")
read_file_at_once()
print("-----")
print(f"get_file_size:{get_file_size()}")


os.remove(filename)
print(f"{filename} has been removed.")