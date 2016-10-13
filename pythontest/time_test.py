# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : time test 

import time

if __name__ == '__main__':

    # epoch time
    print time.time()

    # suspend for 1 sec
    time.sleep(1)

    # 프로세스 시간(초)
    start = time.clock()

    # 현재 시간을 struct_time 형식으로 리턴
    print time.localtime()
    print time.localtime().tm_year
    print time.localtime().tm_mon
    print time.localtime().tm_mday
    print time.localtime().tm_hour
    print time.localtime().tm_min
    print time.localtime().tm_sec

    day_of_week = {
        0:"monday",
        1:"tuesday",
        2:"wednesday",
        3:"thursday",
        4:"friday",
        5:"saturday",
        6:"sunday",
    }
    # 요일 (월요일:0~일요일:6)
    wday = time.localtime().tm_wday
    print wday, '->', day_of_week.get(wday)

    end = time.clock()
    print 'elapsed time : ', end - start , 'sec'
