# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : numpy 테스트

# pip install np
import numpy as np

# start=1 부터 stop=10 까지 num=20개 값을 균일하게 생성
linlsit = np.linspace(1, 10, 20)
print(linlsit)
# start=1 부터 stop=10 까지 num=20개 값을 균일하게 생성, int 값으로
linlsit = np.linspace(1, 10, 20, dtype=int)
print(linlsit)
