# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : jinja test
# install : pip install jinja2

import os
from jinja2 import Template
from jinja2 import Environment, FileSystemLoader


def jinja_test():
    # 템플릿변수 설정 하기
    tm = Template("my nickname is {{ name }}")
    print(tm.render(name='ysoftman'))

    # jinja(템플릿)파일 읽어 변수 설정하기
    env = Environment(loader=FileSystemLoader(os.curdir))
    tm2 = env.get_template("jinja_template.j2")

    mylist = [1, 2, "aa", "bb", "cc"]
    print(tm2.render(
        name="Bill",
        phone=999,
        mylist=mylist
    ))


if __name__ == '__main__':
    jinja_test()
