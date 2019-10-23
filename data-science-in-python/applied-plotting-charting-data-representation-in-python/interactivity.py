from random import shuffle
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


plt.figure()
data = np.random.rand(10)
plt.plot(data)


# 윈도우 wsl(window subsystem for linux) 환경에서 이벤트 처리가 안된다?


# 마우스 클릭 이벤트 발생을 처리할 함수
def onclick(event):
    plt.cla()
    plt.plot(data)
    plt.gca().set_title('Event at pixels {},{} \nand data {},{}'.format(
        event.x, event.y, event.xdata, event.ydata))


# 캔버스가 마우스 클릭을 감지하면 button_press_event 을 발생하고 onclick 를 호출하도록 한다.
# tell mpl_connect we want to pass a 'button_press_event' into onclick when the event is detected
plt.gcf().canvas.mpl_connect('button_press_event', onclick)
plt.show()


################


origins = ['China', 'Brazil', 'India', 'USA', 'Canada',
           'UK', 'Germany', 'Iraq', 'Chile', 'Mexico']
shuffle(origins)
df = pd.DataFrame({'height': np.random.rand(10),
                   'weight': np.random.rand(10),
                   'origin': origins})
plt.figure()
# 산포 점위치와 5픽셀로 가까운 곳의 마우스 클릭만 유효하도록 한다.
# picker=5 means the mouse doesn't have to click directly on an event, but can be up to 5 pixels away
plt.scatter(df['height'], df['weight'], picker=5)
plt.gca().set_ylabel('Weight')
plt.gca().set_xlabel('Height')


def onpick(event):
    origin = df.iloc[event.ind[0]]['origin']
    plt.gca().set_title('Selected item came from {}'.format(origin))


# 캔버스가 마우스 클릭을 감지하면 pick_event 을 발생하고 onpick 를 호출하도록 한다.
# tell mpl_connect we want to pass a 'pick_event' into onpick when the event is detected
plt.gcf().canvas.mpl_connect('pick_event', onpick)
plt.show()
