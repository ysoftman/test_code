# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : tuple test


def tuple_test():
    # 튜플 생성(packing)
    tp = ("ysoftman", 20, 123, 111, 222, 333, '123-456-789')
    print("tp = ", tp)
    # 튜플을 변수로 할당(unpacking)
    # etc 에는 age, phone 사이의 값들이 list 타입으로 들어간다.
    name, age, *etc, phone = tp
    print("name,age,etc,phone=",name, age, etc, phone)

    # 튜플이 리스트와 다른점 1
    # 표현시 () 를 사용한다. 리스트는 [] 사용
    tp = (1, 'ysoftman', 7, 'abc')
    print('tuple = ', tp)
    # 기본은 값에 대한 iterate
    for v in tp:
        print("iterate tp(tuple):", v)

    # 인덱스로 iterate 하려면 range 사용
    for i in range(len(tp)):
        print("iterate tp(tuple)[{}]:{}".format(i, tp[i]))


    # 튜플이 리스트와 다른점 2
    # 튜플은 데이터 수정을 할 수 없지만 리스트보다 조회 속도가 빠른다.
    # 삭제시 에러 발생
    # del tp[1]
    # 추가시 에러 발생
    # tp.add("aaa")
    # 반면 리스트는 수정할 수 있다.
    ls = [1, 'ysoftman', 7, 'abc']
    print('list = ', ls)
    del ls[1]
    print('list = ', ls)


if __name__ == '__main__':
    tuple_test()
