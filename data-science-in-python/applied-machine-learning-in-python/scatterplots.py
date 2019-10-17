from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

x = np.array([1, 2, 3, 4, 5, 6, 7, 8])
y = x
# 새 그림 생성
plt.figure()
# x,y 같은 값이 점찍기 y=x 그래프
# similar to plt.plot(x, y, '.'), but the underlying child objects in the axes are not Line2D
# plt.plot(x, y, '.')
plt.scatter(x, y)
# plot 을 표시
# plt.show()


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
# plt.show()


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

# x값들, y값들로 각각 뽑는다.
zip_generator = zip([1, 2, 3, 4, 5], [6, 7, 8, 9, 10])
# let's turn the data back into 2 lists
# This is like calling zip((1, 6), (2, 7), (3, 8), (4, 9), (5, 10))
x, y = zip(*zip_generator)
print(x)
print(y)
# the above prints:
# (1, 2, 3, 4, 5)
# (6, 7, 8, 9, 10)
