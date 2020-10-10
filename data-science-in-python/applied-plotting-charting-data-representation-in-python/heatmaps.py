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


# heatmaps 지도위에 날씨 데이터를 겹쳐 표시하는 3차원 데이터 시작화에 효과적이다.
plt.figure()
# hist2d 로 표시
Y = np.random.normal(loc=0.0, scale=1.0, size=10000)
X = np.random.random(size=10000)
_ = plt.hist2d(X, Y, bins=25)
plt.show()

# bin을 크게해ㅐ서 더 자세하게 표시
plt.figure()
_ = plt.hist2d(X, Y, bins=100)
# 오른쪽에 컬러바 범례 표시
# add a colorbar legend
plt.colorbar()
plt.show()
