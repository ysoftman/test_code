# author: ysoftman
# python version : 2.x 3.x
# desc : path test
import glob
import os

print("__file__:", __file__)

print("os.curdir:", os.curdir)
print("os.path.abspath:", os.path.abspath(__file__))
print("os.path.dirname:", os.path.dirname(os.path.abspath(__file__)))

print('glob.glob("*.py")')
for f in glob.glob("*.py"):
    print(f)
