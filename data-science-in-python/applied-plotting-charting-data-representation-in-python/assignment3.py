"""
Assignment 3 - Building a Custom Visualization
In this assignment you must choose one of the options presented below and submit a visual as well as your source code for peer grading. The details of how you solve the assignment are up to you, although your assignment must use matplotlib so that your peers can evaluate your work. The options differ in challenge level, but there are no grades associated with the challenge level you chose. However, your peers will be asked to ensure you at least met a minimum quality for a given technique in order to pass. Implement the technique fully (or exceed it!) and you should be able to earn full grades for the assignment.

      Ferreira, N., Fisher, D., & Konig, A. C. (2014, April). Sample-oriented task-driven visualizations: allowing users to make better, more confident decisions.       In Proceedings of the SIGCHI Conference on Human Factors in Computing Systems (pp. 571-580). ACM. (video)

In this paper the authors describe the challenges users face when trying to make judgements about probabilistic data generated through samples. As an example, they look at a bar chart of four years of data (replicated below in Figure 1). Each year has a y-axis value, which is derived from a sample of a larger dataset. For instance, the first value might be the number votes in a given district or riding for 1992, with the average being around 33,000. On top of this is plotted the 95% confidence interval for the mean (see the boxplot lectures for more information, and the yerr parameter of barcharts).

Figure 1 from (Ferreira et al, 2014)

A challenge that users face is that, for a given y-axis value (e.g. 42,000), it is difficult to know which x-axis values are most likely to be representative, because the confidence levels overlap and their distributions are different (the lengths of the confidence interval bars are unequal). One of the solutions the authors propose for this problem (Figure 2c) is to allow users to indicate the y-axis value of interest (e.g. 42,000) and then draw a horizontal line and color bars based on this value. So bars might be colored red if they are definitely above this value (given the confidence interval), blue if they are definitely below this value, or white if they contain this value.

Figure 2c from (Ferreira et al. 2014). Note that the colorbar legend at the bottom as well as the arrows are not required in the assignment descriptions below.

Easiest option: Implement the bar coloring as described above - a color scale with only three colors, (e.g. blue, white, and red). Assume the user provides the y axis value of interest as a parameter or variable.

Harder option: Implement the bar coloring as described in the paper, where the color of the bar is actually based on the amount of data covered (e.g. a gradient ranging from dark blue for the distribution being certainly below this y-axis, to white if the value is certainly contained, to dark red if the value is certainly not contained as the distribution is above the axis).

Even Harder option: Add interactivity to the above, which allows the user to click on the y axis to set the value of interest. The bar colors should change with respect to what value the user has selected.

Hardest option: Allow the user to interactively set a range of y values they are interested in, and recolor based on this (e.g. a y-axis band, see the paper for more details).
"""

# pip3 install mplleaflet
from matplotlib import cm
import mpl_toolkits.axes_grid1.inset_locator as mpl_il
import pandas as pd
import mplleaflet
from matplotlib.artist import Artist
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

# 표준 분포 생성시 시드
# 고정된 시드를 사용해 항상 같은 랜덤값이 나오도록 의도했음.
np.random.seed(12345)

# 표준분포 생성
# np.random.normal(loc=32000 mean=분포의 중간값,
#  scale=200000 분포의 범위,
#  size=3650 데이터 개수)
# print(np.random.normal(32000, 200000, 3650))
# [ -8941.53189694 127788.66761151 -71887.74301135 ... -67319.76648853 113377.29934233  -4494.87853753]
df = pd.DataFrame([np.random.normal(32000, 200000, 3650),
                   np.random.normal(43000, 100000, 3650),
                   np.random.normal(43500, 140000, 3650),
                   np.random.normal(48000, 70000, 3650)],
                  index=[1992, 1993, 1994, 1995])


print(df)
# 1992 ~1995년도(df.columns) 기준으로 변경
df = df.transpose()
print(df)

plt.figure()
# xticks(데이터인덱스리스트, 데이터값리스트, 옵션들...)
plt.xticks(range(len(df.columns)), df.columns)
plt.ylabel('Votes')
plt.xlabel('Years')
# confidence interval : 신뢰 구간
plt.title('Votes Mean(95% confidence interval)')

# y 축 95% 신뢰도 구간
# 1.96 => 95% 신뢰도, 2.25 => 99% 신뢰도
yerr = 1.96*(df.std()/np.sqrt(3650))
print(yerr)

# y=40000 임의 값을 기준으로 삼는다.
sampleY = 40000
# y=값 위치에 수평선 추가
# 참고 https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.axes.Axes.axhline.html
plt.axhline(y=sampleY, color='black')

# 1992~1995년도를 막대 그래프 표시
bars = plt.bar(range(len(df.columns)), df.mean(),
               yerr=yerr, align='center', alpha=0.5)

# 컬러값 참고 https://matplotlib.org/examples/color/named_colors.html
# 1992~1995 bars 에 대해
for i, bar in enumerate(bars):
    # 오차범위가 sampleY 보다 작으면 blue bar 로 표시
    if (bar.get_height() + yerr.iloc[i] < sampleY):
        bar.set_color('blue')
    # 오차범위가 sampleY 보다 크면 red bar 로 표시
    elif (bar.get_height() - yerr.iloc[i] > sampleY):
        bar.set_color('red')
    # 오차범위내에서 sampleY 있으면 green bar 로 표시
    elif (bar.get_height() - yerr.iloc[i] < sampleY < bar.get_height() + yerr.iloc[i]):
        bar.set_color('green')

ax = plt.gca()
# ink junk(데이터 필요에 불편한 잉크들) 제거하기 위해서 위쪽, 오른쪽 테두리를 제거
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)


# 컬러맵 설정
# https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.colors.LinearSegmentedColormap.html#matplotlib.colors.LinearSegmentedColormap.from_list
lscm = mpl.colors.LinearSegmentedColormap.from_list(
    "cm", ["blue", "green", "red"])
# 스칼라데이터(리스트같은)를 RGBA 로 매핑하기 위한 오브젝트 생성
# https://matplotlib.org/3.1.1/api/cm_api.html#matplotlib.cm.ScalarMappable
sm = mpl.cm.ScalarMappable(cmap=lscm)
# 
sm.set_array([])
# 컬러맵으로 컬러바 범주(0~1 사이 값 12개)표시
plt.colorbar(sm, orientation="horizontal", alpha=0.5, boundaries=np.linspace(0, 1, 12))

plt.show()
# plt.savefig("assignment3.png")