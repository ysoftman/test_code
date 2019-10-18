from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl

# matplotlib 에서 백엔드는 그래프를 출력을 위한 시스템을 말하며
# agg, Qt, GTK, macosx 등이 있고 macosx 를 제외하곤 대부분 agg 기반이다.
# matplotlib 가 어떤 백엔드를 사용하고 있는지 파악
print(mpl.get_backend())
# agg 백엔드 사용(백엔드 이름은 대소문자 구분 안한다.)
# mpl.use('agg')

# jupyter notebook 사용시 설명 보기
# plt.plot?

# x=3, y=2 위치에 점찍기
# 디폴트 라인스타일이 - 라서 보이지 않는다.
# because the default is the line style '-',
# nothing will be shown if we only pass in one point (3,2)
# plt.plot(3, 2)
# . 마커로 점을 표시하면 보인다.
plt.plot(3, 2, ".")

# plot 을 표시
plt.show()
# png 파일로 저장시
# plt.savefig("test1.png")

# figure 생성
# First let's set the backend without using mpl.use() from the scripting layer
# create a new figure
fig = Figure()

# fig 를 백엔드에 연결
# associate fig with the backend
canvas = FigureCanvasAgg(fig)
# add a subplot to the fig
ax = fig.add_subplot(111)
# plot the point (3,2)
ax.plot(3, 2, '.')
# 백엔드 그려진 내용을 test.png 파일로 출력
# save the figure to test.png
# you can see this figure in your Jupyter workspace afterwards by going to
# https://hub.coursera-notebooks.org/
canvas.print_png('test.png')


# 새 그래프 생성
# create a new figure
plt.figure()
# o 마커를 이용해서 x=3,y=2 지점에 점찍기
# plot the point (3,2) using the circle marker
plt.plot(3, 2, 'o')
# 현재 축(설정) 가져오기
# get the current axes
ax = plt.gca()
# 현재 축ㅈ을 x=0~6, y=0~10 의 범위를 갖도록 한다.
# Set axis properties [xmin, xmax, ymin, ymax]
ax.axis([0, 6, 0, 10])

plt.show()


# 새 그래프 생성
# create a new figure
plt.figure()

# 각각의 위치에 o 로 점 찍기
# plot the point (1.5, 1.5) using the circle marker
plt.plot(1.5, 1.5, 'o')
# plot the point (2, 2) using the circle marker
plt.plot(2, 2, 'o')
# plot the point (2.5, 2.5) using the circle marker
plt.plot(2.5, 2.5, 'o')

plt.show()


# 현재 축(설정) 가져오기
# get current axes
ax = plt.gca()
# 축 정보
# get all the child objects the axes contains
print(ax.get_children())
