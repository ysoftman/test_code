# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : 시스템 환경 파악 함수 작성
import os
import sys

# 시스템 환경 파악해 보기
def enviroment():
    print ("os.getcwd() = ", os.getcwd())
    print ("sys.platform = ", sys.platform)
    print ("sys.getprofile() = ", sys.getprofile())
    print ("sys.getfilesystemencoding() = ", sys.getfilesystemencoding())
    print ("sys.getallocatedblocks() = ", sys.getallocatedblocks())
    print("os.times() = ", os.times())
    print("__name__ = ",__name__)

    if len(sys.argv) > 0:
        idx = 0
        for val in sys.argv:
            print("arg[", idx,"] = ", val)
