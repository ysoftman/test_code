# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : urlencoding test
from urllib.parse import urlencode, parse_qsl, quote


# python version : 2.x 일때
# import urllib
# import sys
# import urlparse
# reload(sys)
# sys.setdefaultencoding("utf-8")


if __name__ == "__main__":
    url = "ysoftman 한글 123"
    # 공백을 %20 로 표기한다
    # urlenc = urllib.quote(url)  # => python version : 2.x 일때
    urlenc = quote(url)
    print(urlenc)
    # url 디코딩
    # urldec = urllib.unquote(url) # => python version : 2.x 일때
    urldec = quote(url)
    print(urldec)

    # dictionary 데이터는 urlencode 을 사용
    url = {"key1": "1 2", "key2": "value2한글"}
    # 공백을 %20 대신 + 로 표기한다
    # urlenc = urllib.urlencode(url) # => python version : 2.x 일때
    urlenc = urlencode(url)
    print(urlenc)
    # urldec = urlparse.parse_qsl(urlenc) # => python version : 2.x 일때
    urldec = parse_qsl(urlenc)
    urldec = dict(urldec)
    print(urldec)
