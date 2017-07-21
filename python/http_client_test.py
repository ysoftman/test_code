# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : http client library test

# pip install httpclient
import http.client


def http_test(url):
    if url == "":
        return None

    # HTTP 연결
    hCon = http.client.HTTPConnection(url)
    # h2 = http.client.HTTPConnection('www.python.org:80')
    # h3 = http.client.HTTPConnection('www.python.org', 80)
    # h4 = http.client.HTTPConnection('www.python.org', 80, timeout=10)

    # 요청하기
    hCon.request("GET", "/")

    # 응답 받기
    resp = hCon.getresponse()
    print("[resp.status]\n", resp.status)
    print("[resp.reason]\n", resp.reason)
    print("[resp.headers]\n", resp.headers)

    hCon.close()


http_test("www.python.org:80")

