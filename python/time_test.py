# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : time test

import time
import datetime

if __name__ == "__main__":

    # epoch time
    print(time.time())

    # suspend for 1 sec
    time.sleep(1)

    # 프로세스 시간(초)
    start = time.perf_counter()

    # 현재 시간을 struct_time 형식으로 리턴
    print(time.localtime())
    print(time.localtime().tm_year)
    print(time.localtime().tm_mon)
    print(time.localtime().tm_mday)
    print(time.localtime().tm_hour)
    print(time.localtime().tm_min)
    print(time.localtime().tm_sec)

    day_of_week = {
        0: "monday",
        1: "tuesday",
        2: "wednesday",
        3: "thursday",
        4: "friday",
        5: "saturday",
        6: "sunday",
    }
    # 요일 (월요일:0~일요일:6)
    wday = time.localtime().tm_wday
    print(f"{wday} -> {day_of_week.get(wday)}")

    end = time.perf_counter()
    print(f"elapsed time : {end - start} sec")

    # 현재 타임스탬프
    print(datetime.date.fromtimestamp(time.time()))
    # 10일 후 날짜 표시
    td = datetime.timedelta(days=10)
    print(datetime.date.today() + td)

    # 특정 포맷으로 출력
    now = datetime.datetime.now()
    print(now.strftime("%H:%M:%S"))
    print(now.astimezone())
    print(now.astimezone().tzinfo)
    print(now.astimezone().utcoffset)

    # utc 시간 포맷
    utc_now = datetime.datetime.utcnow()
    print("utc_now:", utc_now)
    utc_now_str = utc_now.strftime("%Y-%m-%dT%H:%M:%SZ")
    print("utc_now_str:", utc_now_str)
    # utc -> local time 으로 변경
    t = datetime.datetime.strptime(utc_now_str, "%Y-%m-%dT%H:%M:%S%z")
    print("utc:", t.isoformat())
    print("local:", t.astimezone())

    # 문자->datetime 타입으로 변환
    now = "2020-12-31T15:30:50+09:00"
    new_now = datetime.datetime.strptime(now, "%Y-%m-%dT%H:%M:%S%z")
    print(
        f"new_now: {type(new_now)}, {new_now}, {new_now.date()}, {new_now.time()}, {new_now.timestamp()}"
    )
