# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.6
# desc : collection(컨테이너) 중 counter 테스트

# import os
# import sys
import collections
import operator

l1 = [1,-2,3,5,3,2,1,0,2,3,-2,-1]
print(f"l1:{l1}")

# element 가 해싱키가 되고 element 의 개수가 값으로 저장된다.
counter = collections.Counter(l1)
print(f"counter:{counter}")
print(f"counter[-1]:{counter[-1]}")
print(f"counter[0]:{counter[0]}")
print(f"counter[1]:{counter[1]}")
print(f"counter[2]:{counter[2]}")
print(f"counter[9]:{counter[9]}") # 없으면 개수가 0으로 나온다.

counter2 = collections.Counter(a=1,b=3,c=5)
print(f"counter2:{counter2}")
print(f"counter2.elements():{counter2.elements()}")
print(f"sorted(counter2.elements()):{sorted(counter2.elements())}")
