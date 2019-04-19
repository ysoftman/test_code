# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : urlencoding test
import urllib
import urlparse
import sys

reload(sys)
sys.setdefaultencoding('utf-8')


if __name__ == "__main__":
    url = "ysoftman 한글 123"
    # 공백을 %20 로 표기한다
    urlenc = urllib.quote(url)
    print urlenc
    # url 디코딩
    urldec = urllib.unquote(url)
    print urldec

    # dictionary 데이터는 urlencode 을 사용
    url = {"key1": "1 2",  "key2": "value2한글"}
    # 공백을 %20 대신 + 로 표기한다
    urlenc = urllib.urlencode(url)
    print urlenc
    urldec = urlparse.parse_qsl(urlenc)
    urldec = dict(urldec)
    print urldec
