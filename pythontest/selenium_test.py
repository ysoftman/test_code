# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : 셀레니움 테스트

# 설치
# pip install selenium
# 문서
# http://selenium-python.readthedocs.io/
import time
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
# from selenium.webdriver.firefox.firefox_binary import FirefoxBinary

if __name__ == '__main__':
    print "selenium test"

    # 크롬 드라이버 다운로드받아서 사용해야 한다.
    # https://sites.google.com/a/chromium.org/chromedriver/getting-started
    # 크롬 드라이버 위치명시하여 웹드라이버 생성
    driver = webdriver.Chrome("./chromedriver")
    driver.get("http://www.google.com")

    # 이름으로 엘리먼트 찾기
    elem = driver.find_element_by_name("q")
    # 해당 엘리먼트 클리어
    elem.clear()

    time.sleep(1)
    # 엘리먼트에 키입력
    elem.send_keys("ysoftman")
    # 엘리먼트에 엔터 입력
    elem.send_keys(Keys.RETURN)
    # 결과가 없는 경우 assert 
    assert "No results found." not in driver.page_source

    # 브라우저 결과 확인을 위해 바로 닫하기 전 5초간 여유를 둔다.
    time.sleep(5)
    # 브라우저 닫기
    driver.close()
