# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : logging 테스트

import logging


def DoLogging():
    print("~로깅 테스트~")

    # 로깅 출력(디폴트 stdout)하고, 로그레벨(기본값은 WARNING) 설정
    # logging.basicConfig(filename='./logging.log', level=logging.DEBUG)

    # stdout, file 동시에 로깅하기
    filehandler = logging.StreamHandler()
    streamhandler = logging.FileHandler("./logging.log", mode="w")
    mylogger = logging.getLogger("ysoftman")
    # 파일, 스트림 핸들러 추가
    mylogger.addHandler(filehandler)
    mylogger.addHandler(streamhandler)

    # 로그 레벨 설정
    mylogger.setLevel(logging.DEBUG)

    # CRITICAL = 50
    # FATAL = CRITICAL
    # ERROR = 40
    # WARNING = 30
    # WARN = WARNING
    # INFO = 20
    # DEBUG = 10
    # NOTSET = 0
    mylogger.fatal("치명적인 에러 로그")
    mylogger.error("에러 로그")
    mylogger.warn("경고 로그")
    mylogger.info("정보 로그")
    mylogger.debug("디버그 로그")


if __name__ == "__main__":
    DoLogging()
