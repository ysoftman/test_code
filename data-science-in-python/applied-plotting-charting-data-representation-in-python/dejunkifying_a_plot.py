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


# dejunk(간소화) - stackoverflow 프로그래밍 인기 데이터로 테스트

# 새 그래프 생성
plt.figure()
# stackoverflow 프로그래밍 인기 데이터로 막대 그래프 그리기
languages = ['Python', 'SQL', 'Java', 'C++', 'JavaScript']
pos = np.arange(len(languages))
popularity = [56, 39, 34, 34, 29]
plt.bar(pos, popularity, align='center')
plt.xticks(pos, languages)
plt.ylabel('% Popularity')
plt.title('Top 5 Languages for Math & Data \nby % Popularity on Stack Overflow')
plt.show()


# 새 그래프 생성
plt.figure()
languages = ['Python', 'SQL', 'Java', 'C++', 'JavaScript']
pos = np.arange(len(languages))
popularity = [56, 39, 34, 34, 29]
# 막대 그래프의 색깔을 모드 그레이로 변경하고
# change the bar color to be less bright blue
bars = plt.bar(pos, popularity, align='center',
               linewidth=0, color='lightslategrey')
# 첫번째 막대 그래프가 잘 보일 수 있도록 푸른색으로 변경
# change one bar, the python bar, to a contrasting color
bars[0].set_color('#1F77B4')
# 모든 막대 그래프 색깔 투명도(두께) 조정
# soften all labels by turning grey
plt.xticks(pos, languages, alpha=0.8)
# y레이블, 타이틀 변경
# remove the Y label since bars are directly labeled
plt.ylabel('% Popularity', alpha=0.8)
plt.title(
    'Top 5 Languages for Math & Data \nby % popularity on Stack Overflow', alpha=0.8)
# x 축 레이블만 남기고 다른곳은 모두 제거 - wsl(windows subsystem for linux) 에선 다 지워지진 않는다.
# remove all the ticks (both axes), and tick labels on the Y axis
plt.tick_params(top='off', bottom='off', left='off',
                right='off', labelleft='off', labelbottom='on')
# 그래프 박스 테두리(frame) 제거
# remove the frame of the chart
for spine in plt.gca().spines.values():
    spine.set_visible(False)
# 막대 그래프 마다 텍스트(인기도비율%)을 추가
# direct label each bar with Y axis values
for bar in bars:
    height = bar.get_height()
    plt.gca().text(bar.get_x() + bar.get_width()/2, bar.get_height() - 5, str(int(height)) + '%',
                   ha='center', color='w', fontsize=11)
plt.show()
