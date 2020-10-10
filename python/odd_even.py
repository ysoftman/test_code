# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : odd even
slot363 = [4, 26, 36, 40, 43, 49, 52, 55, 56,
           57, 60, 61, 65, 70, 83, 86, 88, 91, 93, 97]
slot356 = [2, 18, 38, 46, 58, 59, 74, 82, 84, 96]
slot357 = [1, 10, 12, 23, 29, 30, 50, 62, 64, 76]
slot359 = [8, 9, 13, 16, 19, 35, 37, 42, 45, 54, 68, 78, 85, 89, 99]
slot375 = [5, 7, 11, 14, 17, 24, 25, 27, 28,
           31, 39, 44, 53, 66, 67, 75, 77, 79, 87, 95]
print(slot363)
print(slot356)
print(slot359)
print(slot375)

slotall = []
slotall.extend(slot363)
slotall.extend(slot356)
slotall.extend(slot357)
slotall.extend(slot359)
slotall.extend(slot375)
slotall.sort()

print(slotall)

even_list = []
odd_list = []
for i in slotall:
    if i % 2 == 0:
        even_list.append(i)
    else:
        odd_list.append(i)

print('even list = {}'.format(even_list))
print('even cnt = ', len(even_list))
print('odd list = {}'.format(odd_list))
print('odd cnt = ', len(odd_list))
print('total cnt = ', len(slotall))
