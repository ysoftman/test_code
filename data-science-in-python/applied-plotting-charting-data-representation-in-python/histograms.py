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


# 2x2 그리드 형태으 서브 그래프 구성
# create 2x2 grid of axis subplots
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, sharex=True)
axs = [ax1, ax2, ax3, ax4]
# n=10, n=100, n=1000, n=10000 일대의 정규 분포를 4개의 서브 그패르에 표시
# draw n = 10, 100, 1000, and 10000 samples from the normal distribution and plot corresponding histograms
for n in range(0, len(axs)):
    sample_size = 10**(n+1)
    sample = np.random.normal(loc=0.0, scale=1.0, size=sample_size)
    axs[n].hist(sample)
    axs[n].set_title('n={}'.format(sample_size))
plt.show()


# bin(막대의 개수)를 100 로 주면 n 의 크기에따라 더 세밀한 히스토그램을 볼 수 있다.(추이를 분석시 너무 세밀하다고 막대그래프는 큰 도움이 안된다.)
# repeat with number of bins set to 100
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, sharex=True)
axs = [ax1, ax2, ax3, ax4]
for n in range(0, len(axs)):
    sample_size = 10**(n+1)
    sample = np.random.normal(loc=0.0, scale=1.0, size=sample_size)
    axs[n].hist(sample, bins=100)
    axs[n].set_title('n={}'.format(sample_size))
plt.show()


# 10000개의 랜덤 값을
plt.figure()
Y = np.random.normal(loc=0.0, scale=1.0, size=10000)
X = np.random.random(size=10000)
# 산포도 그래프로 표시
# plt.scatter(X, Y)


plt.figure()
gspec = gridspec.GridSpec(3, 3)
# 3x3 서브플롯 구조 생성
# 0row,1col위치
top_histogram = plt.subplot(gspec[0, 1:])
# 1row, 0col 위치
side_histogram = plt.subplot(gspec[1:, 0])
# 1row, 1col 위치
lower_right = plt.subplot(gspec[1:, 1:])
# 10000개의 랜덤 데이터 생성
Y = np.random.normal(loc=0.0, scale=1.0, size=10000)
X = np.random.random(size=10000)
# 오른쪽아래서브플롯에 산포그래프로 표시
lower_right.scatter(X, Y)
# 위쪽서브플롯에 히스토그램으로 표시
top_histogram.hist(X, bins=100)
# 왼쪽서브플롯에 히스트로그램으로 표시
s = side_histogram.hist(Y, bins=100, orientation='horizontal')
# clear the histograms and plot normed histograms
top_histogram.clear()
# matplotlibe 3.1 부터 normed -> density
# top_histogram.hist(X, bins=100, normed=True)
top_histogram.hist(X, bins=100, density=True)
side_histogram.clear()
# side_histogram.hist(Y, bins=100, orientation='horizontal', normed=True)
side_histogram.hist(Y, bins=100, orientation='horizontal', density=True)
# x 축 기준으로 뒤집기
# flip the side histogram's x axis
side_histogram.invert_xaxis()
# x,y  축 값 범위 수정
# change axes limits
for ax in [top_histogram, lower_right]:
    ax.set_xlim(0, 1)
for ax in [side_histogram, lower_right]:
    ax.set_ylim(-5, 5)
plt.show()
