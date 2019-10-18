from random import randint
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

# 새 그래프 생성
plt.figure()
xvals = range(len(linear_data))
# 선형 데이터로 막그래프 그리기, 막대 폭 0.3
plt.bar(xvals, linear_data, width=0.3)
# x 값들에 새로운 x 값들 추가
new_xvals = []
# plot another set of bars, adjusting the new xvals to make up for the first set of bars plotted
for item in xvals:
    new_xvals.append(item+0.3)
# 기하급수적 데이터를 새로운 x값들로 설정해서, 막대그래프 그리기
plt.bar(new_xvals, exponential_data, width=0.3, color='red')
# 랜덤 데이터 생성해 y축에러바(오차범위) 표시
linear_err = [randint(0, 15) for x in range(len(linear_data))]
# This will plot a new set of bars with errorbars using the list of random error values
plt.bar(xvals, linear_data, width=0.3, yerr=linear_err)
plt.show()

# 막대그래프 쌓는(중첩) 형태로 보기
# stacked bar charts are also possible
plt.figure()
xvals = range(len(linear_data))
plt.bar(xvals, linear_data, width=0.3, color='b')
plt.bar(xvals, exponential_data, width=0.3, bottom=linear_data, color='r')
plt.show()


# 막그대프 수평 형태로 보기
# or use barh for horizontal bar charts
plt.figure()
xvals = range(len(linear_data))
plt.barh(xvals, linear_data, height=0.3, color='b')
plt.barh(xvals, exponential_data, height=0.3, left=linear_data, color='r')
plt.show()
