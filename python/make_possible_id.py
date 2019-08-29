# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : gugudan

# 영문2자리 숫자2자리의 가능한 모든 id 생성하기(eg. aa11)
lowercase = 'abcdefghijklmnopqrstuvwxyz'
digits = '0123456789'
# for l1 in lowercase:
#     for l2 in lowercase:
#         for d1 in digits:
#             for d2 in digits:
#                 print(l1+l2+d1+d2)
answer = [l1+l2+d1+d2 for l1 in lowercase for l2 in lowercase for d1 in digits for d2 in digits]
print(answer)
