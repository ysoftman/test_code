# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : path test
import os
import glob

print("__file__:", __file__)

print("os.curdir:", os.curdir)
print("os.path.abspath:", os.path.abspath(__file__))
print("os.path.dirname:", os.path.dirname(os.path.abspath(__file__)))

print('glob.glob("*.py")')
for f in glob.glob("*.py"):
    print(f)
