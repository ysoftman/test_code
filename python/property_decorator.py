# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.5 이상
# desc : @property 테스트


class Fruit:
    def __init__(self, name) -> None:
        # _변수는 (사실 접근은 되지만) private 으로 외부엣 접근하지 말라는 약속
        self._name = name

    # 리팩토링으로 getter, setter 를 추가했다.
    # @property decorator 를 이용하면 Name 멤버변수 다루듯이 외부에서 get,set 할 수 있다.
    # getter
    @property
    def Name(self):
        print("- getName(self) -")
        return self._name

    # setter
    @Name.setter
    def Name(self, name):
        print("- setName(self,name) -")
        self._name = name


f = Fruit("lemon")
# _변수는 (사실 접근은 되지만) private 으로 외부엣 접근하지 말라는 약속이니 다음과 같이 사용하지는 말자.
# f._name="apple"
# print(f._name)

# getter, setter 가 property decorator 등록되어 있어
# 다음과 같이 멤버 변수 접근하듯이 사용할 수 있다.
f.Name = "apple"
print(f.Name)
