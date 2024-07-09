"""
Assignment 2
Before working on this assignment please read these instructions fully. In the submission area, you will notice that you can click the link to Preview the Grading for each step of the assignment. This is the criteria that will be used for peer grading. Please familiarize yourself with the criteria before beginning the assignment.

An NOAA dataset has been stored in the file data/C2A2_data/BinnedCsvs_d400/fb441e62df2d58994928907a91895ec62c2c42e6cd075c2700843b89.csv. The data for this assignment comes from a subset of The National Centers for Environmental Information (NCEI) Daily Global Historical Climatology Network (GHCN-Daily). The GHCN-Daily is comprised of daily climate records from thousands of land surface stations across the globe.

Each row in the assignment datafile corresponds to a single observation.

The following variables are provided to you:

id : station identification code
date : date in YYYY-MM-DD format (e.g. 2012-01-24 = January 24, 2012)
element : indicator of element type
TMAX : Maximum temperature (tenths of degrees C)
TMIN : Minimum temperature (tenths of degrees C)
value : data value for element (tenths of degrees C)
For this assignment, you must:

Read the documentation and familiarize yourself with the dataset, then write some python code which returns a line graph of the record high and record low temperatures by day of the year over the period 2005-2014. The area between the record high and record low temperatures for each day should be shaded.
Overlay a scatter of the 2015 data for any points (highs and lows) for which the ten year record (2005-2014) record high or record low was broken in 2015.
Watch out for leap days (i.e. February 29th), it is reasonable to remove these points from the dataset for the purpose of this visualization.
Make the visual nice! Leverage principles from the first module in this course when developing your solution. Consider issues such as legends, labels, and chart junk.

The data you have been given is near Ann Arbor, Michigan, United States, and the stations the data comes from are shown on the map below.
"""

# pip3 install mplleaflet
# data/C2A2_data/BinnedCsvs_d400/fb441e62df2d58994928907a91895ec62c2c42e6cd075c2700843b89.csv 에 파일이 저장되어 있어 로컬에서 에러 발생한다.
# jupyter notebook 에서 실행해야 한다.
import pandas as pd
import mplleaflet
from matplotlib.artist import Artist
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np


# def leaflet_plot_stations(binsize, hashid):
#     df = pd.read_csv('data/C2A2_data/BinSize_d{}.csv'.format(binsize))
#     station_locations_by_hash = df[df['hash'] == hashid]
#     lons = station_locations_by_hash['LONGITUDE'].tolist()
#     lats = station_locations_by_hash['LATITUDE'].tolist()
#     plt.figure(figsize=(8, 8))
#     plt.scatter(lons, lats, c='r', alpha=0.7, s=200)
#     return mplleaflet.display()


# leaflet_plot_stations(
#     400, 'fb441e62df2d58994928907a91895ec62c2c42e6cd075c2700843b89')


binsize = 400
hashid = "fb441e62df2d58994928907a91895ec62c2c42e6cd075c2700843b89"

# 2005~2015 기후 데이터 dataframe 으로 읽어 오기
df = pd.read_csv("data/C2A2_data/BinnedCsvs_d{}/{}.csv".format(binsize, hashid))
df = df.sort_values(by=["ID", "Date"])
# (년, 월-일) 튜플로 구성
tempDate = df["Date"].apply(lambda string: (string[:4], string[5:]))
# (년), (월-일) 튜플로 분리해서 ,df 에 컬럼으로 추가
df["year"], df["monthday"] = zip(*tempDate)

# 2월 29 데이터는 제외
df = df[df["monthday"] != "02-29"]
df["Data_Value"] *= 1 / 10
# ID, Date 제거
df.drop(["ID", "Date"], axis=1, inplace=True)

# 2015년 데이터
df_2015 = df[df["year"] == "2015"]
# 2005~2014년 데이터
df_2005to2014 = df[df["year"] != "2015"]

# 2015년 최고 기온(TMAX) 일별(monthday) 최고 기온값 집계
df_max_2015 = (
    df_2015[df_2015["Element"] == "TMAX"]
    .groupby("monthday")
    .agg({"Data_Value": np.max})
)
# 2015년 최저 기온(TMIN) 일별(monthday) 최저 기온값 집계
df_min_2015 = (
    df_2015[df_2015["Element"] == "TMIN"]
    .groupby("monthday")
    .agg({"Data_Value": np.min})
)
# 2005~2014년 최고 기온(TMAX) 일별(monthday) 최고 기온값 집계
df_max_2005to2014 = (
    df_2005to2014[df_2005to2014["Element"] == "TMAX"]
    .groupby("monthday")
    .agg({"Data_Value": np.max})
)
# 2005~2014년 최저 기온(TMIN) 일별(monthday) 최저 기온값 집계
df_min_2005to2014 = (
    df_2005to2014[df_2005to2014["Element"] == "TMIN"]
    .groupby("monthday")
    .agg({"Data_Value": np.min})
)
# print(df_max_2005to2014)
# 2015 기온이 2005~2014(평년) 에 비해 낮은 날, 높은 날 인덱스 파악
maxs = np.where(df_max_2015 > df_max_2005to2014)[0]
mins = np.where(df_min_2015 < df_min_2005to2014)[0]
# print(maxs)
# print(mins)


# 그래프 그리기
# figure 크기 참고 https://matplotlib.org/api/_as_gen/matplotlib.pyplot.figure.html#matplotlib.pyplot.figure
# plt.figure()
# x축 레이블이 눈금이 많아 더 width 를 더 크게 한다.
# figsize=[width, height]
plt.figure(figsize=[10, 5])
# 컬러값 참고
# https://matplotlib.org/examples/color/named_colors.html
# 평년의 높은기온(red), 낮은 기온(blue) 선그래프로 그리기, 선두께(50%)
plt.plot(
    df_max_2005to2014.values, c="red", lw=0.5, label="High Temperatures in 2005~2014"
)
plt.plot(
    df_min_2005to2014.values, c="blue", lw=0.5, label="Low Temperatures in 2005~2014"
)

# 2015년 평긴 기온보다 높은날 낮은날을 df_min(max)_2015 에서 찾아
# 산포 그래프로 그리기, circle(maker=0) 로 마크, 마커 크기는 20
plt.scatter(
    maxs,
    df_max_2015.iloc[maxs],
    marker="o",
    s=20,
    c="cyan",
    label="Broken High Temperatures in 2015",
)
plt.scatter(
    mins,
    df_min_2015.iloc[mins],
    marker="o",
    s=20,
    c="magenta",
    label="Broken Low Temperatures in 2015",
)

# 평년 max,min 선 그래프 사이를 채운다.
plt.fill_between(
    range(len(df_min_2005to2014)),
    df_min_2005to2014["Data_Value"],
    df_max_2005to2014["Data_Value"],
    facecolor="violet",
    alpha=0.2,
)

# x,y 레이블, 타이틀 설정, x축 간격이 작아 레이블을 45도 기울인다.
plt.xlabel("Month-Day")
# print(len(df_min_2005to2014))
# x 축 간격 15일 마다 눈금
# xticks(데이터인덱스리스트, 데이터값리스트, 옵션들...)
plt.xticks(
    range(0, len(df_min_2005to2014), 15),
    df_min_2005to2014.index[range(0, len(df_min_2005to2014), 15)],
    rotation="45",
)
plt.ylabel("Temperature in Celsius(°C)")
plt.title("Temperature in Ann Arbor, Michigan, United States")
# 범례 표시
# 범례 위치 참고 https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.legend.html
plt.legend(loc="best")
# plt.legend(loc='lower right')

ax = plt.gca()
# ink junk(데이터 필요에 불편한 잉크들) 제거하기 위해서 위쪽, 오른쪽 테두리를 제거
ax.spines["top"].set_visible(False)
ax.spines["right"].set_visible(False)

plt.show()
# plt.savefig("assignment2.png")
