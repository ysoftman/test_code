# -*- coding: utf-8 -*-
# author : ysoftman
# title : beautifulsoup test
# python version : 2.x

# http://docs.python-requests.org/en/master/
import requests

# https://www.crummy.com/software/BeautifulSoup/
# pip install beautifulsoup4
from bs4 import BeautifulSoup


def parse_html():
    print(parse_html.func_name)
    html = """<html>
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
"""
    # print ("html =", html)
    result = BeautifulSoup(html, "html.parser")
    # 파싱 결과 출력
    print(result.title)
    print(result.title.string)
    print(result.a)


def parse_url(url):
    print(parse_url.func_name)
    print("url =", url)
    resp = requests.get(url)

    # 컨텐츠에서 해당 파싱하기
    result = BeautifulSoup(resp.content, "html.parser")
    # 파싱 결과 출력
    print(result.title)
    print(result.title.string)

    # selector 로 찾기
    # <div class="navbar"> 하위에서 <a href="xxx"> 태그 부분만
    selector = ".navbar a"
    result2 = result.select(selector)
    # 여러개의 a 태그중 첫번째의 텍스트부분 출력
    print(result2[0].text)


def parse_url2(url):
    print(parse_url2.func_name)
    print("url =", url)
    resp = requests.get(url)

    # 컨텐츠에서 해당 파싱하기
    result = BeautifulSoup(resp.content, "html.parser")
    # 파싱 결과 출력
    print(result.title)
    print(result.title.string)

    # selector 로 찾기
    # copy selector string using chrome dev tool
    # #mArticle > div.search_cont > div.card_word.\23 word.\23 eng > div.search_box.\23 box > div > ul > li:nth-child(1) > span.txt_search
    selector = ".search_cont .card_word div ul span.txt_search"
    result2 = result.select(selector)
    print(result2[0].text)


if __name__ == "__main__":
    print("beautifulsoup test")
    parse_html()
    print("\n")
    parse_url("https://www.w3.org/TR/WD-html40-970917/htmlweb.html")
    print("\n")
    parse_url2("http://dic.daum.net/search.do?q=love")
