# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# pandas 에는 Timestamp, DatetimeIndex, Period, PeriodIndex 클래스가 있다.

# 타임스탬프 형식들
print(pd.Timestamp('2/15/2019 07:20PM'))
print(pd.Timestamp('2019-02-15 07:20PM'))
# 한달 후 계산
print(pd.Timestamp('2/15/2019 07:20PM') + pd.DateOffset(months=1))
# 1월달로 설정
print(pd.Timestamp('2/15/2019 07:20PM') + pd.DateOffset(month=1))
# 10일 후 계산
print(pd.Timestamp('2/15/2019 07:20PM') + pd.DateOffset(days=10))
# 10일로 설정
print(pd.Timestamp('2/15/2019 07:20PM') + pd.DateOffset(day=10))
# datetime 형식으로 변경
dt = pd.Timestamp('2019-02-15 07:20PM').to_pydatetime()
print(dt.year)
print(dt.month)
print(dt.day)
print(dt.hour)
print(dt.minute)
print(dt.second)
print()

# period 는 일정 기간을 나타내는 형식으로, 특정 날이나, 달을 나타낸다.
# 'M' 달을 나타낸다.
print(pd.Period('02/2019'))
# 'D' 일을 나타낸다.
print(pd.Period('02/15/2019'))
print()
#  timestamp 로 series 를 생성
t1 = pd.Series(list('abc'), [pd.Timestamp(
    '2016-09-01'), pd.Timestamp('2016-09-02'), pd.Timestamp('2016-09-03')])
print(t1)
# timestamp 인덱스는 datetimeindex 로 지정되어 있다.
print(type(t1.index))
print()

# period 인덱스는 periodindex 로 지정되어 있다.
t2 = pd.Series(list('def'), [pd.Period('2016-09'),
                             pd.Period('2016-10'), pd.Period('2016-11')])
print(t2)
print(type(t2.index))
print()


d1 = ['2 June 2013', 'Aug 29, 2014', '2015-06-26', '7/12/16']
ts3 = pd.DataFrame(np.random.randint(10, 100, (4, 2)),
                   index=d1, columns=list('ab'))
print(ts3)
print()

# 인덱스를 datetime 포맷으로 변경할 수 있다.
ts3.index = pd.to_datetime(ts3.index)
print(ts3)
print()

# 일을 우선 표기하고 안하고 차이
# 2012-04-07 00:00:00
print(pd.to_datetime('4.7.12'))
# 2012-07-04 00:00:00
print(pd.to_datetime('4.7.12', dayfirst=True))
print()

# 타임스탬프 차이
print(pd.Timestamp('9/3/2016') - pd.Timestamp('9/1/2016'))
# Timedelta 로 12일 3시간 후 계산
print(pd.Timestamp('9/2/2016 8:10AM') + pd.Timedelta('12D 3H'))
print()


# DataFrame 의 문자로 된 날짜를 datetime 형식으로 바꾸기
df = pd.DataFrame(data=['2019-01-02', '2109-01-02',
                        '2019-01-03'], columns=['sample date'])
print(df)
print(df['sample date'].astype('datetime64'))
print()


# 2016-10-01 부터 2주간격 날짜 9개 생성
dates = pd.date_range('2016-10-01', periods=9, freq='2W-SUN')
print(dates)
print()


# count1 컬럼: 100 +(-5 부터 10까지 숫자 9개 랜덤).(이전원소값+현재원소값=>현재원소값)
# count2 컬럼: 100 +(-5 부터 10까지 숫자 9개 랜덤)
# 2개의 컬럼을 ㄴ가진 DataFrame 생성
df = pd.DataFrame({'Count 1': 100 + np.random.randint(-5, 10, 9).cumsum(),
                   'Count 2': 120 + np.random.randint(-5, 10, 9)}, index=dates)
print(df)
# 모든 인덱스는 datetime 이고 weekday_name 은 일요일이다.
print(df.index)
print(df.index.weekday_name)
# 컬럼에서 이전값과의 차이를 나타낸다.
print(df.diff())
print()

# dataframe 의 각 달(month)별 평균 계산
print(df.resample('M').mean())

# datetime 으로 인덱싱을 되어 다음과 같은 조회가 가능하다.
# 2016 연도만 찾기
print(df['2016'])
# 2016 11월만 찾기
print(df['2016-11'])
# 2017 1월 이후만 찾기
print(df['2017-01':])
# 2주간격 인덱스를 -> 1주간격 인덱스로 바꾸고, NaN 은 이전 값으로 채우기(ffill)
print(df.asfreq('W', method='ffill'))

# 그래프로 그리기
# (주피터 노트북 사용시)
# %matplotlib inline
df.plot()
plt.show()
