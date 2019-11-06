# pip3 install scipy pandas
from random import randint
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

# matplotlib 에서 백엔드는 그래프를 출력을 위한 시스템을 말하며
# agg, Qt, GTK, macosx 등이 있고 macosx 를 제외하곤 대부분 agg 기반이다.
# matplotlib 가 어떤 백엔드를 사용하고 있는지 파악
print(mpl.get_backend())
# agg 백엔드 사용(백엔드 이름은 대소문자 구분 안한다.)
# mpl.use('agg')

# see the pre-defined styles provided.
plt.style.available

# seaborn-colorblind 사용해 더 많은 컬러로 표현할 수 있다.
# use the 'seaborn-colorblind' style
plt.style.use('seaborn-colorblind')


np.random.seed(123)
# cumsum() 는 열들의 값을 더한다.
# A, B, C 3개의 열을 생성
df = pd.DataFrame({'A': np.random.randn(365).cumsum(0), 
                   'B': np.random.randn(365).cumsum(0) + 20,
                   'C': np.random.randn(365).cumsum(0) - 20}, 
                  index=pd.date_range('1/1/2017', periods=365))
df.head()

# ; 을 붙이면 원치 않는 출력을 막아준다.
# add a semi-colon to the end of the plotting call to suppress unwanted output
df.plot(); 
# plt.show()

"""
kind:
'line' : line plot (default)
'bar' : vertical bar plot
'barh' : horizontal bar plot
'hist' : histogram
'box' : boxplot
'kde' : Kernel Density Estimation plot
'density' : same as 'kde'
'area' : area plot
'pie' : pie plot
'scatter' : scatter plot
'hexbin' : hexbin plot
"""
# 산포도 그래프 그리기
df.plot('A','B', kind = 'scatter');
# plt.show()

# create a scatter plot of columns 'A' and 'C', with changing color (c) and size (s) based on column 'B'
df.plot.scatter('A', 'C', c='B', s=df['B'], colormap='viridis')
# plt.show()

ax = df.plot.scatter('A', 'C', c='B', s=df['B'], colormap='viridis')
# 가로, 세로 비율을 같도록 변경
ax.set_aspect('equal')
# plt.show()

# 박스 플롯
df.plot.box();
# plt.show()

# 히스토그램
df.plot.hist(alpha=0.7);
# plt.show()

# kde 커널 밀도 추정 그래프
df.plot.kde();
# plt.show()

iris = pd.read_csv('iris.csv')
print(iris.head())


# 윈도우에서는 AttributeError: module 'pandas' has no attribute 'tools' 에러 발생
# 산점도 매트릭스는 다른 변수와 대각선을 따라 있는 히스토그램 사이의 산점도 그래프를 만든다.
# pd.tools 는 deprecated 됐다.
# pd.tools.plotting.scatter_matrix(iris);
pd.plotting.scatter_matrix(iris)

plt.figure()
# 평행?병렬? 좌표 그래프
# pd.tools.plotting.parallel_coordinates(iris, 'Name');
pd.plotting.parallel_coordinates(iris, 'Name');
plt.show()
