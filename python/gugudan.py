# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : gugudan

if __name__ == "__main__":
    # 구구단 출력
    for x in range(2, 10):
        for y in range(1, 10):
            print(str(x) + " * " + str(y) + " = " + str(x * y))
        print("")

    # 리스트로 구구단 결과 출력
    print([x * y for x in range(2, 10) for y in range(1, 10)])
