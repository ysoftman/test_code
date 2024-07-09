import mpl_toolkits.axes_grid1.inset_locator as mpl_il
import pandas as pd
import matplotlib.gridspec as gridspec
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


# normal, random, gamma 분포의 랜덤 데이터로 dataframe 생성
normal_sample = np.random.normal(loc=0.0, scale=1.0, size=10000)
random_sample = np.random.random(size=10000)
gamma_sample = np.random.gamma(2, size=10000)
df = pd.DataFrame(
    {"normal": normal_sample, "random": random_sample, "gamma": gamma_sample}
)
df.describe()


# plt.figure()
# df normal 데이터를 박스플롯으로 그리기
# create a boxplot of the normal data, assign the output to a variable to suppress output
# _ = plt.boxplot(df['normal'], whis='range')
# clear the current figure
# plt.clf()

# df 3가지 데이터들 박스 플롯으로 그리기
# plot boxplots for all three of df's columns
# _ = plt.boxplot([df['normal'], df['random'], df['gamma']], whis='range')
# plt.show()


# gamma 데이터 히스토그램으로 그리기
# plt.figure()
# _ = plt.hist(df['gamma'], bins=100)

plt.figure()
# 박스그래프 자세한 설명은 인터넷 설명 참고!!!
# whis 옵션을 주지 않으면 outerlier(박스의 양 끝범위를 넘어선 최대,최소값)이 모두 표시된다.
# if `whis` argument isn't passed, boxplot defaults to showing 1.5*interquartile (IQR) whiskers with outliers
# plt.figure()
# _ = plt.boxplot([ df['normal'], df['random'], df['gamma'] ] )
# df 3가지 데이터들 박스 플롯으로 그리고
plt.boxplot([df["normal"], df["random"], df["gamma"]], whis="range")
# loc=2(왼쪽 상단) 위치에 부모(박스플롯)의 60%x40% 크기로 gamma 히스토그램 추가(overlay) ---> ax2로 그래프 컨트롤
# overlay axis on top of another
ax2 = mpl_il.inset_axes(plt.gca(), width="60%", height="40%", loc=2)
ax2.hist(df["gamma"], bins=100)
ax2.margins(x=0.5)
# y축 왼쪽 부분의 ticks(눈금표시)를 y축 오른쪽 부분으로 옮긴다.
# switch the y axis ticks for ax2 to the right side
ax2.yaxis.tick_right()
# interquartile(4등분)
plt.show()
