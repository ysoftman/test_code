# pip3 install scipy pandas seaborn
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib as mpl
import seaborn as sns


# matplotlib 에서 백엔드는 그래프를 출력을 위한 시스템을 말하며
# agg, Qt, GTK, macosx 등이 있고 macosx 를 제외하곤 대부분 agg 기반이다.
# matplotlib 가 어떤 백엔드를 사용하고 있는지 파악
print(mpl.get_backend())
# agg 백엔드 사용(백엔드 이름은 대소문자 구분 안한다.)
# mpl.use('agg')


np.random.seed(1234)
v1 = pd.Series(np.random.normal(0, 10, 1000), name='v1')
v2 = pd.Series(2*v1 + np.random.normal(60, 15, 1000), name='v2')

np.random.seed(1234)
v1 = pd.Series(np.random.normal(0, 10, 1000), name='v1')
v2 = pd.Series(2*v1 + np.random.normal(60, 15, 1000), name='v2')

# 히스토그램 그리기
# plot a kernel density estimation over a stacked barchart
plt.figure()
plt.hist([v1, v2], histtype='barstacked', normed=True)
plt.show()
# seaborn 으로 KDE(kernel density estimation) 그래프 생성
# kde 는 히스토그램들의 높이를 잇는 선을 그린다.
v3 = np.concatenate((v1, v2))
sns.kdeplot(v3)

plt.figure()
# we can pass keyword arguments for each individual component of the plot
sns.distplot(v3, hist_kws={'color': 'Teal'}, kde_kws={'color': 'Navy'})

plt.show()
sns.jointplot(v1, v2, alpha=0.4)
grid = sns.jointplot(v1, v2, alpha=0.4)
grid.ax_joint.set_aspect('equal')
sns.jointplot(v1, v2, kind='hex')

# 모든 그래픔에 seaborn white 스타일 적용
# set the seaborn style for all the following plots
sns.set_style('white')

sns.jointplot(v1, v2, kind='kde', space=0)
iris = pd.read_csv('iris.csv')
iris.head()
sns.pairplot(iris, hue='Name', diag_kind='kde', size=2)
plt.figure(figsize=(8, 6))
plt.subplot(121)
sns.swarmplot('Name', 'PetalLength', data=iris)
plt.subplot(122)
sns.violinplot('Name', 'PetalLength', data=iris)
