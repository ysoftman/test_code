# -*- coding: utf-8 -*-
# author : ysoftman
# title : beautifulsoup test
# python version : 2.x
import sys

# http://docs.python-requests.org/en/master/
import requests

# https://www.crummy.com/software/BeautifulSoup/
# pip install beautifulsoup4
from bs4 import BeautifulSoup


def parse_html():
    print parse_html.func_name
    html = '''<html>
<head>
<title>
ysoftman
</title>
</head>
<body>
<p class="title">
<b>
    ysfotman
</b>
</p>
<p class="myclass1">
<a class="abc" href="http://ysoftman.com/abc" id="link1">
    test abc
</a>
</p>
</body>
</html>
'''
    # print "html =", html
    result = BeautifulSoup(html, 'html.parser')
    # 파싱 결과 출력
    print result.title
    print result.title.string
    print result.a

def parse_url(url):
    print parse_url.func_name
    print "url =", url
    resp = requests.get(url)
    
    # 컨텐츠에서 해당 파싱하기
    result = BeautifulSoup(resp.content, 'html.parser')
    # 파싱 결과 출력
    print result.title
    print result.title.string
    
    # selector 로 찾기
    # class="navbar" 에서 태그 부분만
    selector = ".navbar a"
    result2 = result.select(selector)
    # 여러개의 a 태그중 첫번째의 텍스트부분 출력
    print result2[0].text

if __name__ == '__main__':
    print("beautifulsoup test")
    parse_html()
    print("\n")
    parse_url("https://www.w3.org/TR/WD-html40-970917/htmlweb.html")
