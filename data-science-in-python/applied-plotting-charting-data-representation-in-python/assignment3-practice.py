"""
Practice Assignment: Understanding Distributions Through Sampling
This assignment is optional, and I encourage you to share your solutions with me and your peers in the discussion forums!

To complete this assignment, create a code cell that:

Creates a number of subplots using the pyplot subplots or matplotlib gridspec functionality.
Creates an animation, pulling between 100 and 1000 samples from each of the random variables (x1, x2, x3, x4) for each plot and plotting this as we did in the lecture on animation.
Bonus: Go above and beyond and "wow" your classmates (and me!) by looking into matplotlib widgets and adding a widget which allows for parameterization of the distributions behind the sampling animations.
Tips:

Before you start, think about the different ways you can create this visualization to be as interesting and effective as possible.
Take a look at the histograms below to get an idea of what the random variables look like, as well as their positioning with respect to one another. This is just a guide, so be creative in how you lay things out!
Try to keep the length of your animation reasonable (roughly between 10 and 30 seconds).
"""

# pip3 install mplleaflet
import matplotlib.animation as animation
from matplotlib import cm
import mpl_toolkits.axes_grid1.inset_locator as mpl_il
import pandas as pd
import mplleaflet
from matplotlib.artist import Artist
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

# generate 4 random variables from the random, gamma, exponential, and uniform distributions
x1 = np.random.normal(-2.5, 1, 10000)
x2 = np.random.gamma(2, 1.5, 10000)
x3 = np.random.exponential(2, 10000) + 7
x4 = np.random.uniform(14, 20, 10000)

colors = ["red", "green", "blue", "cyan"]

# plot the histograms
plt.figure(figsize=(9, 3))

# The 'normed' kwarg was deprecated in Matplotlib 2.1 and will be removed in 3.1. Use 'density' instead
# plt.hist(x1, normed=True, bins=20, alpha=0.5, color=colors[0])
# plt.hist(x2, normed=True, bins=20, alpha=0.5, color=colors[1])
# plt.hist(x3, normed=True, bins=20, alpha=0.5, color=colors[2])
# plt.hist(x4, normed=True, bins=20, alpha=0.5, color=colors[3])
plt.hist(x1, density=True, bins=20, alpha=0.5, color=colors[0])
plt.hist(x2, density=True, bins=20, alpha=0.5, color=colors[1])
plt.hist(x3, density=True, bins=20, alpha=0.5, color=colors[2])
plt.hist(x4, density=True, bins=20, alpha=0.5, color=colors[3])
plt.axis([-7, 21, 0, 0.6])

plt.text(x1.mean() - 1.5, 0.5, "x1\nNormal")
plt.text(x2.mean() - 1.5, 0.5, "x2\nGamma")
plt.text(x3.mean() - 1.5, 0.5, "x3\nExponential")
plt.text(x4.mean() - 1.5, 0.5, "x4\nUniform")


#####


x1 = np.random.normal(-2.5, 1, 10000)
x2 = np.random.gamma(2, 1.5, 10000)
x3 = np.random.exponential(2, 10000) + 7
x4 = np.random.uniform(14, 20, 10000)
xdata = [x1, x2, x3, x4]

colors = ["red", "green", "blue", "cyan"]
# 2x2 subplot 으로 표현
fig, ([ax1, ax2], [ax3, ax4]) = plt.subplots(2, 2)
ax1.hist(x1, density=True, bins=20, alpha=0.5, color=colors[0])
ax2.hist(x2, density=True, bins=20, alpha=0.5, color=colors[1])
ax3.hist(x3, density=True, bins=20, alpha=0.5, color=colors[2])
ax4.hist(x4, density=True, bins=210, alpha=0.5, color=colors[3])
axes = [ax1, ax2, ax3, ax4]

titles = ["x1\nNormal", "x2\nGamma", "x3\nExponential", "x4\nUniform"]
ax2.set_title(titles[0])
ax2.set_title(titles[1])
ax3.set_title(titles[2])
ax4.set_title(titles[3])
# subplot 들의 파라미터에 따라 레이아웃을 자동 조정한다.
plt.tight_layout()


# 매 프레임 마다 호출될 update 함수 작성
def update(curr):
    # 마지막 프레임인 경우 애니메이션을 멈춘다.
    # 10번 호출
    if curr == 10:
        a.event_source.stop()
    # 4개의 subplot 에 대해서
    for i in range(len(axes)):
        # subplot 지우기
        axes[i].cla()
        # xdata[i]의 1000개씩 10번그려진다. => 10000, 막대그래프 개수 100개
        axes[i].hist(xdata[i][: 1000 * curr], bins=100, alpha=0.5, color=colors[i])
        axes[i].set_title(titles[i])
    plt.tight_layout()


# 1s 마다 update() 함수를 호출한다.
a = animation.FuncAnimation(fig, update, interval=1000)
plt.show()

# animation 파일로 저장
# Writer = animation.writers['ffmpeg']
# writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)
# a.save("assignment3-practice.mp4", writer=writer)
a.save("assignment3-practice.mp4")
