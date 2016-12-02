# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : 쉘 명령어르 실행하고 결과 받아오기 테스트
import os

# 쉘 명령 실행
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

# 쉘 명령 출력 결과 얻기
print '----- test4 -----'
output = os.popen('find . -name "*.py"').read()
print output
# 라인구분으로 리스트로 만들기
linelist = output.split('\n')
for line in linelist: 
    print line + " --> ok."
