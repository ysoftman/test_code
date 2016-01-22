# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : url request test


import urllib.request
# import urllib.response


def url_request(url):
    # URL 요청 후 응답 받기
    resp = urllib.request.urlopen(url)

    # 응답 내용 보기
    print("[resp.read()]\n", resp.read())


# url 요청
url_request("http://www.google.com")
url_request("http://www.naver.com")

