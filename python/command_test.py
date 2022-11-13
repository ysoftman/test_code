# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : 쉘 명령어르 실행하고 결과 받아오기 테스트
import os
import subprocess

# 쉘 명령 실행
print("----- test1 -----")
# 종료코드 리턴
ret = os.system("ls")
print("exitcode=" + str(ret))

print("----- test2 -----")
ret = os.system("ll")
print("exitcode=" + str(ret))

print("----- test3 -----")
ret = os.system("echo 'ysoftman'")
print("exitcode=" + str(ret))

# 쉘 명령 출력 결과 얻기
print("----- test4 -----")
output = os.popen('find . -name "*.py"').read()
print(output)
# 라인구분으로 리스트로 만들기
linelist = output.split("\n")
for line in linelist:
    print(line + " --> ok.")
# 라인구분으로 리스토 얻어 오기 -> 각 요소마다 엔터 포함된다.
lines = os.popen('find . -name "*.py"').readlines()
print(lines)
for line in lines:
    print(line + " --> ok2.")

# subprocess.Popen 으로 실행하기
# 참고로 os.popen 은 python 2.6 부터 deprecated 되었다.
# https://docs.python.org/2/library/os.html
print("----- test5 -----")
args = ["ls", "-1"]
output = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = output.communicate()
print("[stdout]\n", stdout)
print("[stderr]\n", stderr)
# 라인 구분하여 리스트화 시키기
lines = str(stdout).split("\n")
for i in lines:
    print("line=" + i)
