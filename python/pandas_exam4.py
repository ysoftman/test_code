# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import ttest_ind

# Use this dictionary to map state names to two letter acronyms
states = {'OH': 'Ohio', 'KY': 'Kentucky', 'AS': 'American Samoa', 'NV': 'Nevada', 'WY': 'Wyoming', 'NA': 'National', 'AL': 'Alabama', 'MD': 'Maryland', 'AK': 'Alaska', 'UT': 'Utah', 'OR': 'Oregon', 'MT': 'Montana', 'IL': 'Illinois', 'TN': 'Tennessee', 'DC': 'District of Columbia', 'VT': 'Vermont', 'ID': 'Idaho', 'AR': 'Arkansas', 'ME': 'Maine', 'WA': 'Washington', 'HI': 'Hawaii', 'WI': 'Wisconsin', 'MI': 'Michigan', 'IN': 'Indiana', 'NJ': 'New Jersey', 'AZ': 'Arizona', 'GU': 'Guam', 'MS': 'Mississippi', 'PR': 'Puerto Rico', 'NC': 'North Carolina',
          'TX': 'Texas', 'SD': 'South Dakota', 'MP': 'Northern Mariana Islands', 'IA': 'Iowa', 'MO': 'Missouri', 'CT': 'Connecticut', 'WV': 'West Virginia', 'SC': 'South Carolina', 'LA': 'Louisiana', 'KS': 'Kansas', 'NY': 'New York', 'NE': 'Nebraska', 'OK': 'Oklahoma', 'FL': 'Florida', 'CA': 'California', 'CO': 'Colorado', 'PA': 'Pennsylvania', 'DE': 'Delaware', 'NM': 'New Mexico', 'RI': 'Rhode Island', 'MN': 'Minnesota', 'VI': 'Virgin Islands', 'NH': 'New Hampshire', 'MA': 'Massachusetts', 'GA': 'Georgia', 'ND': 'North Dakota', 'VA': 'Virginia'}


# university_towns.txt (도시\n도시에 있는 대학...\n도시\n도시에 있는 대학...)파일에서 다음 형식의 dataframe 생성
# DataFrame([["Michigan", "Ann Arbor"], ["Michigan", "Yipsilanti"]],columns=["State", "RegionName"])
def get_list_of_university_towns():
    '''Returns a DataFrame of towns and the states they are in from the
      university_towns.txt list. The format of the DataFrame should be:
      DataFrame( [ ["Michigan", "Ann Arbor"], ["Michigan", "Yipsilanti"] ],
      columns=["State", "RegionName"]  )

      The following cleaning needs to be done:

      1. For "State", removing characters from "[" to the end.
      2. For "RegionName", when applicable, removing every character from " (" to the end.
      3. Depending on how you read the data, you may need to remove newline character '\n'. '''

    f = open('university_towns.txt')
    ct_ut = []
    for line in f:
        # \n 삭제
        line = line.strip()
        if '[edit]' in line:
            # [edit] 삭제해서 도시 이름 파악
            city = line.replace('[edit]', '')
        else:
            # (대학 풀 네임)][숫자] 부분 삭제해서 대학 이름 파악
            university = line.split(' (')[0]
            ct_ut.append((city, university))

    return pd.DataFrame(data=ct_ut, columns=['State', 'RegionName'])


print(get_list_of_university_towns())
# State 컬럼을 인덱스로 설정해서 Michigan 주 대학들 조회
# df = get_list_of_university_towns().copy()
# df = df.reset_index()
# df = df.set_index(['State'])
# print(df.loc['Michigan'])


# 2000년대 GDP dataframe 생성
def create_gdp_dataframe():
    gdp = pd.ExcelFile('gdplev.xls')
    # 2000년1분기부터 읽는다.(220번째 줄부터)
    gdp = gdp.parse("Sheet1", skiprows=219)
    # '1999q4', 9926.1 값 이부터의 시리즈를 DataFrame 으로 생성
    df_gdp = pd.DataFrame(gdp[['1999q4', 9926.1]])
    df_gdp.columns = ['quarter', 'gdp']
    # 그래프로 그려보기
    # df_gdp.plot.bar(title='GDP in Qurters', figsize=(30, 10), x='quarter', y='gdp')
    # plt.show()
    return df_gdp


# 2000년대 불황 시작 파악
def get_recession_start():
    '''Returns the year and quarter of the recession start time as a
    string value in a format such as 2005q3'''
    df = create_gdp_dataframe()
    # df 의 컬럼은
    # 0 -> quater 분기이름
    # 1 -> gdp 값이다.
    for i in range(2, len(df)):
        # 이이전분기 > 이전분기 > 현재분기, 연속해서 GDP 가 떨어지면 이이전이 불황의 시작된 분기이다.
        if (df.iloc[i-2][1] > df.iloc[i-1][1]) and (df.iloc[i-1][1] > df.iloc[i][1]):
            return df.iloc[i-2][0]
    return ''


print(get_recession_start())


# 2000년대 불황 끝 파악
def get_recession_end():
    '''Returns the year and quarter of the recession end time as a
    string value in a format such as 2005q3'''

    df = create_gdp_dataframe()

    # 불화의 시작 지점(분기) 파악
    recession_start = 0
    for i in range(2, len(df)):
        # 이이전분기 > 이전분기 > 현재분기, 연속해서 GDP 가 떨어지면 이이전이 불황의 시작된 분기이다.
        if (df.iloc[i-2][1] > df.iloc[i-1][1]) and (df.iloc[i-1][1] > df.iloc[i][1]):
            # df.iloc[i-2][0]
            recession_start = i-2
            break
    # print(recession_start)

    # 불화의 시작 지점(분기) 파악(기존 결과를 DataFrame 에서 검색한다.)
    # recession_start = get_recession_start()
    # recession_start_index = df[df['quarter'] == recession_start].index.tolist()[0]
    # print(recession_start_index)
    for i in range(recession_start, len(df)):
        # 현재분기 < 다음분기 < 다다음분기 현재, 연속해서 GDP 가 올라가면 현재분기가 불황의 끝이 된다.
        if (df.iloc[i][1] < df.iloc[i+1][1]) and (df.iloc[i+1][1] < df.iloc[i+2][1]):
            return df.iloc[i+2][0]

    return ''


print(get_recession_end())


# 불황 기간에서 최고조 일때
def get_recession_bottom():
    '''Returns the year and quarter of the recession bottom time as a 
    string value in a format such as 2005q3'''

    df = create_gdp_dataframe()

    # 불황의 시작 지점(분기) 파악
    recession_start = get_recession_start()
    recession_start_index = df[df['quarter'] == recession_start].index.tolist()[
        0]
    # print(recession_start_index)

    # 불황의 종료 지점(분기) 파악
    recession_end = get_recession_end()
    recession_end_index = df[df['quarter'] == recession_end].index.tolist()[0]
    # print(recession_end_index)

    # print(df.iloc[recession_start_index:recession_end_index+1, 1])
    # print(df.iloc[recession_start_index:recession_end_index+1]['gdp'])
    # 불황 기간 중 GDP 가 가장 낮은 분기가 불황 최고조분기다.
    min_index = df.iloc[recession_start_index:recession_end_index+1, 1].idxmin()

    return df.iloc[min_index][0]


print(get_recession_bottom())


# housing 데이터 2000 1분기 ~ 2016 3분기 평균 DataFrame 생성
def convert_housing_data_to_quarters():
    '''Converts the housing data to quarters and returns it as mean 
    values in a dataframe. This dataframe should be a dataframe with
    columns for 2000q1 through 2016q3, and should have a multi-index
    in the shape of ["State","RegionName"].

    Note: Quarters are defined in the assignment description, they are
    not arbitrary three month periods.

    The resulting dataframe should have 67 columns, and 10,730 rows.
    '''
    # csv -> dataframe 로 읽고
    df_cityhome = pd.read_csv('City_Zhvi_AllHomes.csv')

    # 위에 선언한 states 딕션어리로 2자리약어 -> 풀네임으로 State 값 변경
    df_cityhome['State'] = df_cityhome['State'].map(states)
    # 'State', 'RegionName' 컬럼을 인덱스로
    df_cityhome.set_index(['State', 'RegionName'], inplace=True)
    # [라인:전체, 컬럼:'2000-01'컬림 이후] 으로만 필터링
    df_cityhome = df_cityhome.loc[:, '2000-01':]

    print(df_cityhome)

    # 분기(3개월)이름 만들기
    quarter_column = []
    for col in range(2000, 2017):
        for q in ['q1', 'q2', 'q3', 'q4']:
            quarter_column.append(str(col) + q)
    # 2016-08 까지 있기 때문에 2016q4 는 제거한다.
    quarter_column = quarter_column[:-1]
    # print(quarter_column)

    # 분기 평균값을 갖는 새컬럼 추가
    i = 0
    for newcol in quarter_column:
        # [라인은 모두, 컬럼은 3개씩 평균] 을 새
        df_cityhome[newcol] = df_cityhome.iloc[:, i:i+3].mean(axis=1)
        i = i + 3

    return df_cityhome.loc[:, '2000q1':]


print(convert_housing_data_to_quarters())


# 불황 기간에 대학별 도시 데이터와 대학없는 도시 데이터간의 T-테스트를 수행해 튜플(different, p, better) 리턴
def run_ttest():
    '''First creates new data showing the decline or growth of housing prices
    between the recession start and the recession bottom. Then runs a ttest
    comparing the university town values to the non-university towns values, 
    return whether the alternative hypothesis (that the two groups are the same)
    is true or not as well as the p-value of the confidence. 

    Return the tuple (different, p, better) where different=True if the t-test is
    True at a p<0.01 (we reject the null hypothesis), or different=False if 
    otherwise (we cannot reject the null hypothesis). The variable p should
    be equal to the exact p value returned from scipy.stats.ttest_ind(). The
    value for better should be either "university town" or "non-university town"
    depending on which has a lower mean price ratio (which is equivilent to a
    reduced market loss).'''

    # 불황의 시작 지점(분기) 파악
    recession_start = get_recession_start()
    # 최대 불황 지점(분기) 파악
    recession_bottom = get_recession_bottom()
    # 주거 dataframe 파악
    df_cityhome = convert_housing_data_to_quarters(
    ).loc[:, recession_start:recession_bottom]
    #  [State, RegionName] 인덱스에서 해제하고 컬럼으로 변경한다.
    df_cityhome.reset_index(inplace=True)
    #  불황기간 가격이 몇 %나 떨어졌는지(올랐는지) 계산해 새컬럼으로 추가한다.
    df_cityhome['price_ratio'] = (
        df_cityhome[recession_start] - df_cityhome[recession_bottom]) / df_cityhome[recession_start]
    # print(df_cityhome)

    # 도시별 대학 dataframe 파악
    df_university_town = get_list_of_university_towns()
    # 지역 이름만 리스트로 생성
    region_list = df_university_town['RegionName'].tolist()
    # print(region_list)

    # 대학이 있는 도시 여부를 새컬럼으로 추가
    df_cityhome['isUniversityTown'] = df_cityhome.RegionName.apply(
        lambda x: x in region_list)
    # NaN(미싱데이터) 제거하고 isUniversityTown=True 인 데이터만 새로 생성
    uni_city = df_cityhome[df_cityhome.isUniversityTown].copy().dropna()
    # NaN(미싱데이터) 제거하고 isUniversityTown=False 인 데이터만 새로 생성
    no_uni_city = df_cityhome[~df_cityhome.isUniversityTown].copy().dropna()

    # print(uni_city)
    # print(no_uni_city)

    # 대학이 있는 도시와 그렇지 않는 도시와의 주택가격 등락률에 대해서 ttest 수행
    tt_result = ttest_ind(uni_city['price_ratio'], no_uni_city['price_ratio'])
    # print(tt_result)

    # p 값이 0.01 작으면 대학에 따른 주택 가격 등락률 차이가 있는것으로 판단
    # different=True 이면 귀무가설(null hypothesis) 을 reject 할 수 있다.
    different = False
    if tt_result[1] < 0.01:
        different = True
    # 대학이 있는 도시의 주택 가격 등락률 평균과 그렇지 않는 곳중 어디가 작은지
    better = 'non-university town'
    # print(uni_city['price_ratio'].mean())
    # print(no_uni_city['price_ratio'].mean())
    if uni_city['price_ratio'].mean() < no_uni_city['price_ratio'].mean():
        better = 'university town'
    # tuple 데이터로 리턴
    return (different, tt_result[1], better)


print(run_ttest())
