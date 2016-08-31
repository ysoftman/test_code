# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 시스템 환경 파악 함수 작성
import os
import sys

# 시스템 환경 파악해 보기
def enviroment():
    print("__name__ = ",__name__)   
    print("os.getcwd() = ", os.getcwd())
    print("os.times() = ", os.times())   
    print("sys.platform = ", sys.platform)
    print("sys.getprofile() = ", sys.getprofile())
    print("sys.getfilesystemencoding() = ", sys.getfilesystemencoding())
    
    # python 3 에서 가능
    # print("sys.getallocatedblocks() = ", sys.getallocatedblocks())

    if len(sys.argv) > 0:
        idx = 0
        for val in sys.argv:
            print("arg[", idx,"] = ", val)
if __name__ == "__main__":
    enviroment()
