# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : urlencoding test
import urllib

if __name__ == "__main__":
    url = {"key1":"1 2",  "key2":"value2"}
    # 공백을 %20 대신 + 로 표기한다
    print urllib.urlencode(url)
