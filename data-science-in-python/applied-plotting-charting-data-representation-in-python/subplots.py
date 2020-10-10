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


plt.figure()
# 1row, 2columns의 서브 그래프 공간에서 1번째 그래프에 그리기
# subplot with 1 row, 2 columns, and current axis is 1st subplot axes
plt.subplot(1, 2, 1)
linear_data = np.array([1, 2, 3, 4, 5, 6, 7, 8])
plt.plot(linear_data, '-o')

exponential_data = linear_data**2
# 1row, 2columns의 서브 그래프 공간에서 2번째 그래프에 그리기
# subplot with 1 row, 2 columns, and current axis is 2nd subplot axes
plt.subplot(1, 2, 2)
plt.plot(exponential_data, '-o')

# 1번째 서브 그래프에 exponential_data 추가
# plot exponential data on 1st subplot axes
plt.subplot(1, 2, 1)
plt.plot(exponential_data, '-x')

plt.show()


plt.figure()
ax1 = plt.subplot(1, 2, 1)
plt.plot(linear_data, '-o')
# 2개의 서브 그래프가 같은 y축을 공유, 2개의 그래그 y축 표시가 같아 상대적 차이를 쉽게 알 수 있다.
# pass sharey=ax1 to ensure the two subplots share the same y axis
ax2 = plt.subplot(1, 2, 2, sharey=ax1)
plt.plot(exponential_data, '-x')
plt.show()

# plt.figure()
# # 서브 그래프 생성시, row,column,currentplot 을 , 를 빼고 명시해도 된다.
# # the right hand side is equivalent shorthand syntax
# plt.subplot(1,2,1) == plt.subplot(121)


# 3x3 그리드 형태의 서브 그래프를 다음과 같이 수성할 수도 있다.
# create a 3x3 grid of subplots
fig, ((ax1, ax2, ax3), (ax4, ax5, ax6), (ax7, ax8, ax9)
      ) = plt.subplots(3, 3, sharex=True, sharey=True)
# 5번째(1row,1col 에 있는 subplot) 그래프
# plot the linear_data on the 5th subplot axes
ax5.plot(linear_data, '-')
plt.show()


# 위 3x3 서브 그래프들의 레이블 표시
# set inside tick labels to visible
for ax in plt.gcf().get_axes():
    for label in ax.get_xticklabels() + ax.get_yticklabels():
        label.set_visible(True)
# 시스템에 따라 canvas를 업데이트 해야 할 수도 있다.
# 윈도우 wsl 환경에서는 보이지 않는다.
# necessary on some systems to update the plot
# plt.gcf().canvas.draw()
plt.show()
