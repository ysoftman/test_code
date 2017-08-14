# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : url request test


# python version 3.x
# import urllib.request
# import urllib.response
# def url_request(url):
#     # URL 요청 후 응답 받기
#     resp = urllib.request.urlopen(url)
#     # 응답 내용 보기
#     print("[resp.read()]\n", resp.read())



# 참고 http://docs.python-requests.org/en/master/
import requests 

def url_request(url):
    resp = requests.get(url)
    
    # 4xx client error or 5xx server error 응답시 raise 발생 
    resp.raise_for_status()
    print '['+url+']'
    print 'encoding:', resp.encoding
    print 'text:', resp.text
    print 'headers:', resp.headers
    print 'headers[server]:', resp.headers['server']

# url 요청
url_request("http://www.google.com")
url_request("http://www.naver.com")

