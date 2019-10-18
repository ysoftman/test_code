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

x = np.array([1, 2, 3, 4, 5, 6, 7, 8])
y = x
# 새 그래프 생성
plt.figure()

# scatter(산포 그래프)
# x,y 같은 값이 점찍기 y=x 그래프
# similar to plt.plot(x, y, '.'), but the underlying child objects in the axes are not Line2D
# plt.plot(x, y, '.')
plt.scatter(x, y)
# plot 을 표시
plt.show()


# y=x 점들이 green, green ... 마지막 점만 red 색깔로 표시
x = np.array([1, 2, 3, 4, 5, 6, 7, 8])
y = x
# create a list of colors for each point to have
# ['green', 'green', 'green', 'green', 'green', 'green', 'green', 'red']
colors = ['green']*(len(x)-1)
colors.append('red')
plt.figure()
# plot the point with size 100 and chosen colors
plt.scatter(x, y, s=100, c=colors)
plt.show()


# zip(반복되는데이터) 동일한 개수의 자료들을 묶어준다.
# [(1, 6), (2, 7), (3, 8), (4, 9), (5, 10)] (x,y) 좌표 리스트 생성
# convert the two lists into a list of pairwise tuples
zip_generator = zip([1, 2, 3, 4, 5], [6, 7, 8, 9, 10])
print(list(zip_generator))
# the above prints:
# [(1, 6), (2, 7), (3, 8), (4, 9), (5, 10)]

# * 를 사용하면 [] 를 제거할 수 있다.
zip_generator = zip([1, 2, 3, 4, 5], [6, 7, 8, 9, 10])
# The single star * unpacks a collection into positional arguments
print(*zip_generator)
# the above prints:
# (1, 6) (2, 7) (3, 8) (4, 9) (5, 10)

# zip() 으로 2개의 값을 가진 튜플 5개를 -> 5개의 값을 가진 튜플 2개로 변환
# use zip to convert 5 tuples with 2 elements each to 2 tuples with 5 elements each
print(list(zip((1, 6), (2, 7), (3, 8), (4, 9), (5, 10))))
# the above prints:
# [(1, 2, 3, 4, 5), (6, 7, 8, 9, 10)]

# 튜플 2개를 각각 x값들, y값들로 사용할 수 있다.
zip_generator = zip([1, 2, 3, 4, 5], [6, 7, 8, 9, 10])
# let's turn the data back into 2 lists
# This is like calling zip((1, 6), (2, 7), (3, 8), (4, 9), (5, 10))
x, y = zip(*zip_generator)
print(x)
print(y)
# the above prints:
# (1, 2, 3, 4, 5)
# (6, 7, 8, 9, 10)


# 새 그래프 생성
plt.figure()
# 마커의 크기는 100, (x1,y1) (x2,y2) 까지는 마커의 색상은 빨간색, 이후는 파란색으로 표시
# plot a data series 'Tall students' in red using the first two elements of x and y
plt.scatter(x[:2], y[:2], s=100, c='red', label='Tall students')
# plot a second data series 'Short students' in blue using the last three elements of x and y
plt.scatter(x[2:], y[2:], s=100, c='blue', label='Short students')
# plot 을 표시
plt.show()

# x,y,타이틀을 변경
# add a label to the x axis
plt.xlabel('The number of times the child kicked a ball')
# add a label to the y axis
plt.ylabel('The grade of the student')
# add a title
plt.title('Relationship between ball kicking and grades')

# 범례 추가
# add a legend (uses the labels from plt.scatter)
# plt.legend()
# 범베를 그래프의 오른쪽 아래 부분에 표시한다.
# add the legend to loc=4 (the lower right hand corner), also gets rid of the frame and adds a title
plt.legend(loc=4, frameon=False, title='Legend')


# get children from current axes (the legend is the second to last item in this list)
plt.gca().get_children()
# get the legend from the current axes
legend = plt.gca().get_children()[-2]
# you can use get_children to navigate through the child artists
legend.get_children()[0].get_children()[1].get_children()[0].get_children()


# 아티스트(캔버스에 레더링하는 오브젝트들) 내부 구조 파악하는 rec_gc 를 만들보자.
# import the artist class from matplotlib
def rec_gc(art, depth=0):
    if isinstance(art, Artist):
        # increase the depth for pretty printing
        print("  " * depth + str(art))
        for child in art.get_children():
            rec_gc(child, depth+2)


# Call this function on the legend artist to see what the legend is made up of
rec_gc(plt.legend())

# plot 을 표시
plt.show()
