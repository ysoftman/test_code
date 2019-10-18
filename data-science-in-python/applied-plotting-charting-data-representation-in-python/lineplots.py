import pandas as pd
from matplotlib.artist import Artist
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

# matplotlib 에서 백엔드는 그래프를 출력을 위한 시스템을 말하며
# agg, Qt, GTK, macosx 등이 있고 macosx 를 제외하곤 대부분 agg 기반이다.
# matplotlib 가 어떤 백엔드를 사용하고 있는지 파악
print(mpl.get_backend())
# agg 백엔드 사용(백엔드 이름은 대소문자 구분 안한다.)
# mpl.use('agg')

linear_data = np.array([1, 2, 3, 4, 5, 6, 7, 8])
exponential_data = linear_data**2

# 새 그림(그래프) 생성
plt.figure()
# 선형 데이터, 기하급수적 데이터
# plot the linear data and the exponential data
# 라인 스타일 : https://matplotlib.org/gallery/lines_bars_and_markers/line_styles_reference.html
# - (실선) 으로 표시
# plt.plot(linear_data, '-', exponential_data, '-')
# - (실선), o(마커는 동그라미로)  -o-o-o 으로 각 점을 실선으로 이어 표시
plt.plot(linear_data, '-o', exponential_data, '-o')
# -- (dash), r(red) 빨간색의 점선으로 표시
# plot another series with a dashed red line
plt.plot([22, 44, 55], '--r')

# x,y축 레이블, 타이틀 추가
plt.xlabel('Some data')
plt.ylabel('Some other data')
plt.title('A title')
# 범례 추가
# add a legend with legend entries (because we didn't have labels when we plotted the data series)
plt.legend(['Baseline', 'Competition', 'Us'])


# 선형 데이터, 기하급수적 데이터 사이를 파란색으로 채우기, 투명도는 0.25
# fill the area between the linear data and exponential data
plt.gca().fill_between(range(len(linear_data)),
                       linear_data, exponential_data,
                       facecolor='blue',
                       alpha=0.25)


plt.show()


# 새 그래프 생성
plt.figure()
observation_dates = np.arange(
    '2017-01-01', '2017-01-09', dtype='datetime64[D]')
plt.plot(observation_dates, linear_data, '-o',
         observation_dates, exponential_data, '-o')

plt.show()


# 새 그래프 생성
plt.figure()
observation_dates = np.arange(
    '2017-01-01', '2017-01-09', dtype='datetime64[D]')
# convert the map to a list to get rid of the error
observation_dates = list(map(pd.to_datetime, observation_dates))
plt.plot(observation_dates, linear_data, '-o',
         observation_dates, exponential_data, '-o')
x = plt.gca().xaxis
# x 축 레이블을 45 각도로 회전
# rotate the tick labels for the x axis
for item in x.get_ticklabels():
    item.set_rotation(45)

# x 축 레이블이 길이 잘리는것 방지 하기 위해 아래쪽 공간을 늘려준다.
# adjust the subplot so the text doesn't run off the image
plt.subplots_adjust(bottom=0.25)
# 축정보 가져와 수정
ax = plt.gca()
ax.set_xlabel('Date')
ax.set_ylabel('Units')
ax.set_title('Exponential vs. Linear performance')
# 제목목에 수학적 표현 추가
# you can add mathematical expressions in any text element
ax.set_title("Exponential ($x^2$) vs. Linear ($x$) performance")
plt.show()
