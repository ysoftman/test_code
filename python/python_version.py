# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : python 2/3 버전 체크해 분기
import sys

print(sys.version_info)

python_major_version = sys.version_info[0]

# 3.x 버전대
if python_major_version >= 3:
    print("python", python_major_version)
else:
    print("python", python_major_version)
