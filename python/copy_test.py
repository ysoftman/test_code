# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : copy test
import copy


def copy_test():
    mylist1 = [1, "str"]

    # 기본적으로 객체 참조(얕은 복사)
    mylist2 = mylist1
    # deep 복사로 mylist3 를 만들 수 있다.
    mylist3 = copy.deepcopy(mylist1)

    print("mylist1 = ", mylist1)
    print("mylist2 = ", mylist2)
    print("mylist3 = ", mylist3)

    # 객체 참조로 mylist2 도 변경된다.
    # mylist3 는 변경되지 않는다.
    mylist1.append("zzz")
    print("mylist1 = ", mylist1)
    print("mylist2 = ", mylist2)
    print("mylist3 = ", mylist3)


if __name__ == "__main__":
    copy_test()
