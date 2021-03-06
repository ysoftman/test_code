"""
Assignment 4
Before working on this assignment please read these instructions fully. In the submission area, you will notice that you can click the link to Preview the Grading for each step of the assignment. This is the criteria that will be used for peer grading. Please familiarize yourself with the criteria before beginning the assignment.

This assignment requires that you to find at least two datasets on the web which are related, and that you visualize these datasets to answer a question with the broad topic of weather phenomena (see below) for the region of Ann Arbor, Michigan, United States, or United States more broadly.

You can merge these datasets with data from different regions if you like! For instance, you might want to compare Ann Arbor, Michigan, United States to Ann Arbor, USA. In that case at least one source file must be about Ann Arbor, Michigan, United States.

You are welcome to choose datasets at your discretion, but keep in mind they will be shared with your peers, so choose appropriate datasets. Sensitive, confidential, illicit, and proprietary materials are not good choices for datasets for this assignment. You are welcome to upload datasets of your own as well, and link to them using a third party repository such as github, bitbucket, pastebin, etc. Please be aware of the Coursera terms of service with respect to intellectual property.

Also, you are welcome to preserve data in its original language, but for the purposes of grading you should provide english translations. You are welcome to provide multiple visuals in different languages if you would like!

As this assignment is for the whole course, you must incorporate principles discussed in the first week, such as having as high data-ink ratio (Tufte) and aligning with Cairo’s principles of truth, beauty, function, and insight.

Here are the assignment instructions:

State the region and the domain category that your data sets are about (e.g., Ann Arbor, Michigan, United States and weather phenomena).
You must state a question about the domain category and region that you identified as being interesting.
You must provide at least two links to available datasets. These could be links to files such as CSV or Excel files, or links to websites which might have data in tabular form, such as Wikipedia pages.
You must upload an image which addresses the research question you stated. In addition to addressing the question, this visual should follow Cairo's principles of truthfulness, functionality, beauty, and insightfulness.
You must contribute a short (1-2 paragraph) written justification of how your visualization addresses your stated research question.
What do we mean by weather phenomena? For this category you might want to consider seasonal changes, natural disasters, or historical trends.

Tips
Wikipedia is an excellent source of data, and I strongly encourage you to explore it for new data sources.
Many governments run open data initiatives at the city, region, and country levels, and these are wonderful resources for localized data sources.
Several international agencies, such as the United Nations, the World Bank, the Global Open Data Index are other great places to look for data.
This assignment requires you to convert and clean datafiles. Check out the discussion forums for tips on how to do this from various sources, and share your successes with your fellow students!
Example
Looking for an example? Here's what our course assistant put together for the Ann Arbor, MI, USA area using sports and athletics as the topic. Example Solution File
"""

# pip3 install mplleaflet
from matplotlib import cm
from matplotlib.ticker import FuncFormatter
import mpl_toolkits.axes_grid1.inset_locator as mpl_il
import pandas as pd
import mplleaflet
from matplotlib.artist import Artist
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import sys

"""
1. region and domain 
region: China, Japan, Korea 
domain: Air transport, passengers carried (1970~2017)

2. Create a research question about the domain category and region that you identified.
Since 1970, How many passengers carried by air transport in China, Japan and Korea.

3. Links
china http://data.un.org/Data.aspx?d=WDI&f=Indicator_Code:IS.AIR.PSGR;Country_Code:CHN;Time_Code:1970,1971,1972,1973,1974,1975,1976,1977,1978,1979,1980,1981,1982,1983,1984,1985,1986,1987,1988,1989,1990,1991,1992,1993,1994,1995,1996,1997,1998,1999,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017&c=0,1,2,3,4,5&s=Country_Name:asc,Year:desc&v=1

japan http://data.un.org/Data.aspx?d=WDI&f=Indicator_Code:IS.AIR.PSGR;Country_Code:JPN;Time_Code:1970,1971,1972,1973,1974,1975,1976,1977,1978,1979,1980,1981,1982,1983,1984,1985,1986,1987,1988,1989,1990,1991,1992,1993,1994,1995,1996,1997,1998,1999,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017&c=0,1,2,3,4,5&s=Country_Name:asc,Year:desc&v=1

korea http://data.un.org/Data.aspx?d=WDI&f=Indicator_Code:IS.AIR.PSGR;Country_Code:KOR;Time_Code:1970,1971,1972,1973,1974,1975,1976,1977,1978,1979,1980,1981,1982,1983,1984,1985,1986,1987,1988,1989,1990,1991,1992,1993,1994,1995,1996,1997,1998,1999,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017&c=0,1,2,3,4,5&s=Country_Name:asc,Year:desc&v=1

4.Provide a short (1-2 paragraphs) justification of how your visual addresses your research question.
This visualization was concerned with answering the question how many people carried by air transport. Due to the large difference in passenger numbers by country, the y-axis of the graph is displayed as 'e' by default, which is expressed in millions(M) for better readability. The x-axis of the graph used vertical lines to represent the last 2017 years of data. And I used the dot grid to guide you through the yearly data.
This graph shows the increase in aircraft use by Korean, Chinese and Japanese passengers from 1970 to 2017. Korean and Japanese passenger growth has been modest, while Chinese passengers have increased rapidly since 2000.

5.Describe your design choices for your visual in regards to Cairo's principle of truthfulness.
Describe your design choices for your visual in regards to Cairo's principle of beauty.
Describe your design choices for your visual in regards to Cairo's principle of functionality.
Describe your design choices for your visual in regards to Cairo's principle of insightfulness.

truthfulness : The number of passengers in different countries is expressed as it is.
beauty : I used harmonious colors.
functionality : Different country colors and legends were used to distinguish them.
insightfulness : It clearly shows the difference between the number of Chinese passengers and the number of passengers in other countries.


"""


# dataframe 에서 필요없는 컬럼, 로우 제거
def remove_extra_cols_rows(df):
    df = df[df['Indicator Code'] != 'footnoteSeqID']
    df = df[df['Indicator Code'] != '1']
    # axis=1:컬럼, 0:로우
    df.drop(['Indicator Code', 'Time Code',
             'Value Footnotes'], axis=1, inplace=True)
    return df

# 너쿠 커서 자연상수(e) 표시를 M(million,100만) 단위로 포맷팅
# https://matplotlib.org/examples/pylab_examples/custom_ticker1.html


def millions(x, pos):
    # return '%1.1fM' % (x*1e-6)
    return '%1dM' % (x*1e-6)


plt.figure()
plt.style.use('seaborn-colorblind')

df1 = pd.read_csv('UNdata_Export_china.csv')
df1 = remove_extra_cols_rows(df1)
df2 = pd.read_csv('UNdata_Export_japan.csv')
df2 = remove_extra_cols_rows(df2)
df3 = pd.read_csv('UNdata_Export_korea.csv')
df3 = remove_extra_cols_rows(df3)
# df row 로 합치기, 기존 인덱스 무시
df = pd.concat([df1, df2, df3], ignore_index=True, axis=0)

# 컬럼 이름 변경
for col in df.columns:
    if col == 'Country or Area':
        df.rename(columns={col: 'country'}, inplace=True)
    elif col == 'Year':
        df.rename(columns={col: 'years'}, inplace=True)
    elif col == 'Value':
        df.rename(columns={col: 'passengers'}, inplace=True)

# print(df)
# print(df.dtypes)
# 정수형으로 변환
# print(df)
# print(df.dtypes)
df['passengers'] = df['passengers'].astype('int64')
print(df)


# 최소, 최대 승객 수 파악
df_temp = df.sort_values(by=['passengers'])
minPassengers = df_temp['passengers'].iloc[0]
maxPassengers = df_temp['passengers'].iloc[len(df_temp)-1]
# print(df_temp)
# minPassengers: 710000
# maxPassengers: 551234509
print("minPassengers:", minPassengers)
print("maxPassengers:", maxPassengers)

# 나라 별로 분리
df_china = df[df['country'] == 'China']
df_japan = df[df['country'] == 'Japan']
df_korea = df[df['country'] == 'Korea']
# print(df_korea)
# print(df_korea[['year', 'value']])

# years, passengers 로 튜플 구성
tu_china = [tuple(x) for x in df_china[['years', 'passengers']].values]
tu_japan = [tuple(x) for x in df_japan[['years', 'passengers']].values]
tu_korea = [tuple(x) for x in df_korea[['years', 'passengers']].values]

# year(xval) 별 value(yval) 으로 구분
labels = ['Chinese passengers', 'Japanese passengers', 'Korean passengers']
# 마커 사용 https://matplotlib.org/3.1.1/api/markers_api.html
markers = ['-s', '-X', '-o']
tu_list = []
tu_list.append(tu_china)
tu_list.append(tu_japan)
tu_list.append(tu_korea)
i = 0
for tu in tu_list:
    xval = [x[0] for x in tu]
    yval = [x[1] for x in tu]
    plt.plot(xval, yval, markers[i], label=labels[i])
    i = i+1

# 범례 표시
plt.legend(loc='best')
ax = plt.gca()
# 축 이름 설정
ax.set_xlabel('years')
ax.set_ylabel('passengers')
# 타이틀 설정
ax.set_title('Air transport, passengers carried (1970~2017)')

# 배경 격자 설정
# https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.grid.html
plt.grid(color='r', linestyle=':', linewidth=1, alpha=0.5)


# 축 범위
# Set axis properties [xmin, xmax, ymin, ymax]
ax.axis([1970, 2020, minPassengers, maxPassengers])
# x 눈끔 간격 5 로 설정
plt.xticks(np.arange(1970, 2017, 5))
# 2017년 위치에 수직선으로 표시
plt.axvline(x=2017, color='black')
# 수직선 위치(x,y, 텍스트, 90도회전)에 2017 텍스트 표시
plt.text(2017.1, maxPassengers/2, '2017', rotation=90)

# 너무 커서 자연상수(e)로 표현되는것을 막기
# plt.ticklabel_format(style='plain')
formatter = FuncFormatter(millions)
# 너무 커서 자연상수(e)로 표현되는것을 백만(M)단위로 표시
ax.yaxis.set_major_formatter(formatter)

# ink junk(데이터 필요에 불편한 잉크들) 제거하기 위해서 위쪽, 오른쪽 테두리를 제거
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.show()
# plt.savefig("assignment4.png")
