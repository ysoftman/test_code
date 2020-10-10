import matplotlib.animation as animation
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


n = 100
x = np.random.randn(n)


# 매 프레임 마다 호출될 update 함수 작성
# 총 100번(프레임) 호출되고 매 프레임마다 
# 랜덤값 x(100개) 1개씩 추가되는 히스토그램을 새로 그린다.
# create the function that will do the plotting, where curr is the current frame
def update(curr):
    # 마지막 프레임인 경우 애니메이션을 멈춘다.
    # check if animation is at the last frame, and if so, stop the animation a
    if curr == n:
        a.event_source.stop()
    # 플롯 지우기
    plt.cla()
    bins = np.arange(-4, 4, 0.5)
    plt.hist(x[:curr], bins=bins)
    plt.axis([-4, 4, 0, 30])
    plt.gca().set_title('Sampling the Normal Distribution')
    plt.gca().set_ylabel('Frequency')
    plt.gca().set_xlabel('Value')
    plt.annotate('n = {}'.format(curr), [3, 27])


fig = plt.figure()
# 100ms 마다 update() 함수를 호출한다.
a = animation.FuncAnimation(fig, update, interval=100)
plt.show()
