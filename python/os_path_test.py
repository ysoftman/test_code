# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : os path test
import os

print __file__

print "os.curdir:", os.curdir

cur_abs_path = os.path.abspath(__file__)
print "cur_abs_path:", cur_abs_path
cur_abs_path_dirname = os.path.dirname(cur_abs_path)
print "cur_abs_path_dirname:", cur_abs_path_dirname

