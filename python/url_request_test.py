# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : url request test


# python 3.x
# import requests
# import urllib.request
# import urllib.response
# from urllib import parse


# def url_request(url):
#     # URL 요청 후 응답 받기
#     resp = urllib.request.urlopen(url)
#     # 응답 내용 보기
#     print(("[resp.read()]\n", resp.read()))


# url_request("http://www.google.com")
# exit(0)


##########


# python 2.x
import requests
from urlparse import urlparse, parse_qs

# 참고 http://docs.python-requests.org/en/master/


def url_request(url):
    resp = requests.get(url)

    # 4xx client error or 5xx server error 응답시 raise 발생
    resp.raise_for_status()
    print("[" + url + "]")
    print("resp.status_code:", resp.status_code)
    print("resp.encoding:", resp.encoding)
    print("resp.headers:", resp.headers)
    print("resp.headers[server]:", resp.headers["server"])
    # 내용 출력이 많아 생략
    # print ('text:', resp.text)


def url_post_request(url):
    # dictionary 로 표현
    data = {"mydata1": "123", "mydata2": "aaaa"}
    headers = {"Content-Type": "application/json"}
    cookies = {"mycookie": "this is test 쿠키"}
    # resp = requests.post(url, data=data, headers=headers, cookies=cookies)
    # 또는
    resp = requests.request("POST", url, data=data, headers=headers, cookies=cookies)
    print("[" + url + "]")
    print("resp.status_code:", resp.status_code)
    print("resp.encoding:", resp.encoding)
    print("resp.headers:", resp.headers)
    print("resp.text:", resp.text)


def url_parse_param(url):
    # params = parse.urlsplit(url)  # python3
    # url을 scheme(http,https), netloc(www.google.com), path(/search),
    # query(a=1&b=aaa) 로 분리
    result = urlparse(url)
    print(result)
    # 쿼리 파라미터를 dictionary 로 파싱
    params = parse_qs(result.query)
    print(params)
    # 각 파라미터의 값은 여러개가 될 수 있어 list 형태로 담겨있다.
    print(params["a"])
    print(params["a"][0])
    print(params["b"])
    print(params["b"][0])


# url 요청
url_request("http://www.google.com")
print("")
url_post_request("http://httpbin.org/post")
print("")
url_parse_param("http://www.google.com/search?a=1&b=aaa")
print("")
