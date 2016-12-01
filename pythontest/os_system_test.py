# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : os system test
import os

# os.system() 로 명령 실행
print '----- test1 -----'
# 종료코드 리턴
ret = os.system("ls")
print 'exitcode=' + str(ret)

print '----- test2 -----'
ret = os.system("ll")
print 'exitcode=' + str(ret)

print '----- test3 -----'
ret = os.system("echo 'ysoftman'")
print 'exitcode=' + str(ret)
