# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : pandas test
import numpy as np
import pandas as pd

# Energy Indicators.xls DataFrame 생성
# skiprows, skipfooter 인덱스 0부터 시작
# 처음 18개 라인, 마지막 38개 라인은 제외하고 읽기
df_energy = pd.read_excel("Energy Indicators.xls", skiprows=17, skipfooter=38)
# 의미 없는 공백 컬럼 첫 2개 삭제
df_energy = df_energy.drop(df_energy.columns[[0, 1]], axis=1)
# 컬럼들 이름 설정
df_energy.columns = ['Country', 'Energy Supply',
                     'Energy Supply per Capita', '% Renewable']
# ... 로 된 문자 NaN으로 변경
df_energy = df_energy.replace(['...'], [np.NaN])
# 나라 이름에 '(xxx)' 부분제거
df_energy['Country'] = df_energy['Country'].str.replace(r"\(.*\)", "")
# 나라 이름에 숫자 부분제거
df_energy['Country'] = df_energy['Country'].str.replace(r"\d+", "")
# 문자열 앞뒤 공백 제거
df_energy['Country'] = df_energy['Country'].str.strip()
# 다음 이름들 변경(Republic of Korea -> South Korea) 로 변경
df_energy = df_energy.replace(["Republic of Korea",
                               "United States of America",
                               "United Kingdom of Great Britain and Northern Ireland",
                               "China, Hong Kong Special Administrative Region"
                               ],
                              ["South Korea",
                               "United States",
                               "United Kingdom",
                               "Hong Kong"
                               ]
                              )
# 'Energy Supply per Capita' 의 단위가 gigajoules 단위라서
# 'Energy Supply' 의 petajoule -> gigajoules 단위로 맞추가
df_energy['Energy Supply'] *= 1000000
# print(df_energy)


# world_bank.csv DataFrame 생성
# 첫 4라인 스킵
df_gdp = pd.read_csv("world_bank.csv", skiprows=4)
# 컬럼이름 변경
df_gdp = df_gdp.rename(columns={'Country Name': 'Country'})
# 나라 이름 변경
df_gdp = df_gdp.replace(["Korea, Rep.",
                         "Iran, Islamic Rep.",
                         "Hong Kong SAR, China"],
                        ["South Korea",
                         "Iran",
                         "Hong Kong"]
                        )
# print(df_gdp)


# scimagojr-3.xlsx DataFrame 생성
df_scimen = pd.read_excel("scimagojr-3.xlsx")
# print(df_scimen)


# 위 3개의 dataframe 머지하고 Rank 15까지만 필터링
def answer_one():
    # df_energy, df_gdp 양쪽에 있는 Country 컬럼기준으로 inner 조인
    df = pd.merge(df_energy, df_gdp, how='inner', on=['Country'])
    # df, df_scimen 양쪽에 있는 Country 컬럼기준으로 inner 조인
    df = pd.merge(df, df_scimen, how='inner', on=['Country'])
    # Country 컬럼을 인데스로 설정하고
    df = df.set_index('Country')

    # Rank 15까지만 필터링
    df = df[df.Rank <= 15]
    # 다음 20개의 컬럼만 출력
    df = df[['Rank', 'Documents', 'Citable documents', 'Citations', 'Self-citations', 'Citations per document', 'H index',
             'Energy Supply', 'Energy Supply per Capita', '% Renewable', '2006', '2007', '2008', '2009', '2010', '2011', '2012', '2013', '2014', '2015']]
    return df


print(answer_one())


# 1번 문제 datafrme 3개 조인할때 제외된 로우의 개수
def answer_two():
    # 전체 합집합
    df1 = pd.merge(df_energy, df_gdp, how='outer', on=['Country'])
    df_outer = pd.merge(df1, df_scimen, how='outer', on=['Country'])

    # 모두 겹치는 집합
    # df_energy, df_gdp 양쪽에 있는 Country 컬럼기준으로 inner 조인
    df1 = pd.merge(df_energy, df_gdp, how='inner', on=['Country'])
    # df_energy, df_scimen 양쪽에 있는 Country 컬럼기준으로 inner 조인
    df_inner = pd.merge(df1, df_scimen, how='inner', on=['Country'])

    # 전체 합집합 - 전체 교집합
    return len(df_outer) - len(df_inner)


print(answer_two())


# 1번의 답인 15개 나라에 대해 최근 10년간 gdp 평균(missing value 는 제외), 내림차순
def answer_three():
    df = answer_one()
    # 최근 10년 컬럼이름 파악을 위해
    # print(df_gdp.columns)
    # 최근 10년 gdp 평균 컬럼만 필터링

    # .copy() 하지 않으면 아래와 같은 경고 발생
    # A value is trying to be set on a copy of a slice from a DataFrame.
    # Try using .loc[row_indexer,col_indexer] = value instead
    df2 = df[['2006', '2007', '2008', '2009',
              '2010', '2011', '2012', '2013', '2014', '2015']].copy()
    # 컬럼들의 평균 구해서 새 컬럼으로 추가
    # 2006 컬럼들의 axis=0(인덱스,세로)기준으로 평균
    # df2['10year_gdp_mean'] = df2['2006'].mean(axis=0)
    # axis=1(컬럼, 가로)기준으로 평균
    df2['10year_gdp_mean'] = df2.mean(axis=1)

    # print(df2)
    # 내림차순으로 정렬, 컬럼(series 데이터타입)으로 리턴
    return df2['10year_gdp_mean'].sort_values(ascending=False)


print(answer_three())


# 1번 결과에서 10년에 걸쳐 gdp 변환가 큰것 중에 6번째
# (3번 문제에서 6번째 나라의 2006-2015 의 GDP 차이)
def answer_four():
    df = answer_one()
    # 최근 10년 컬럼이름 파악을 위해
    # print(df_gdp.columns)
    # 최근 10년 gdp 평균 컬럼만 필터링
    df2 = df[['2006', '2007', '2008', '2009',
              '2010', '2011', '2012', '2013', '2014', '2015']].copy()

    # 2006 컬럼들의 axis=0(인덱스,세로)기준으로 평균
    # df2['10year_gdp_mean'] = df2['2006'].mean(axis=0)

    # 컬럼들의 평균 구해서 새 컬럼으로 추가
    # axis=1(컬럼, 가로)기준으로 평균
    df2['10year_gdp_mean'] = df2.mean(axis=1)
    # 내림차순 정렬하기
    df2.sort_values(['10year_gdp_mean'], ascending=False, inplace=True)
    # 2006 컬럼값 - 2015 컬럼값
    return abs(df2.iloc[5, df2.columns.get_loc('2006')] - df2.iloc[5, df2.columns.get_loc('2015')])


print(answer_four())


# 1번결과에서 Energy Supply per Capita 평균
def answer_five():
    df = answer_one()
    # 컬럼 과 값을 출력
    # return df[['Energy Supply per Capita']].mean(axis=0)
    # 값만 출력
    return df['Energy Supply per Capita'].mean(axis=0)


print(answer_five())


# 신재생에너지(% Renewable'가 최대인 나라의 페센티지
# tuple 타입으로 리턴
def answer_six():
    df = answer_one()
    # row(인데스) 자체가 나라로 되어 있어 인덱스를 찾으면 된다.
    return (df['% Renewable'].idxmax(), df['% Renewable'].max())


print(answer_six())
print(type(answer_six()))


# 'Self-citations / Citations' 비율 계산해서 가장 큰 나라
# tuple 타입으로 리턴
def answer_seven():
    df = answer_one()
    tmp_df = df['Self-citations'] / df['Citations']
    return (tmp_df.idxmax(), tmp_df.max())


print(answer_seven())
print(type(answer_seven()))


# 'Energy Supply' 'Energy Supply per Capita' 를 이용해 'estimates' 컬럼을 생성하고
# 3번째로 인구가 많은 나라 출력
# string 타입으로 리턴
def answer_eight():
    df = answer_one()
    df['estimate'] = df['Energy Supply'] / df['Energy Supply per Capita']
    # 'estimate' 컬럼으로 내림차순 정렬해서 3번째 로우(인덱스, 나라이름)
    return df.sort_values(['estimate'], ascending=False).index[2]


print(answer_eight())
print(type(answer_eight()))


# 8번의 문제의 'estimate' 에 대한 'Citable document' 을 'Citable documents per person' 로 계산하고
# 'Energy Supply per Capita' 컬럼 피어슨 상관계수
# 'Energy Supply per Capita'
# string 타입으로 리턴
def answer_nine():
    df = answer_one()
    df['estimate'] = df['Energy Supply'] / df['Energy Supply per Capita']
    # 'estimate' 에 대한 'Citable document' 을 'Citable documents per person' 로 계산하고
    df['Citable documents per person'] = df['Citable documents'] / df['estimate']
    # 'Citable documents per person' 컬럼과 'Energy Supply per Capita' 컬럼의 피어슨 상관계수
    return df['Citable documents per person'].corr(df['Energy Supply per Capita'], method='pearson')


print(answer_nine())
print(type(answer_nine()))


def answer_ten():
    df = answer_one()
    # '% Renewable' 컬럼에서 중간값을 찾고
    m = df['% Renewable'].median()
    # 중간값보다 낮은 나라는 0, 높은 나라는 1로 하는 'HighRenew' 컬럼 생성
    df['HighRenew'] = [1 if x >= m else 0 for x in df['% Renewable']]
    # 'Rank' 오름 차순으로 'HightRenew' 컬럼 출력
    # return df.sort_values(['Rank'], ascending=True)
    return df.sort_values(['Rank'], ascending=True)['HighRenew']


print(answer_ten())
print(type(answer_ten()))


def get_df_continent_top15():
    # 대륙(Continent) 기준(인덱스) df_continent_top15 = df_top15 + df_continent 머지 dataframe 생성
    df_top15 = answer_one()
    df_top15['estimate'] = df_top15['Energy Supply'] / \
        df_top15['Energy Supply per Capita']
    ContinentDict = {'China': 'Asia',
                     'United States': 'North America',
                     'Japan': 'Asia',
                     'United Kingdom': 'Europe',
                     'Russian Federation': 'Europe',
                     'Canada': 'North America',
                     'Germany': 'Europe',
                     'India': 'Asia',
                     'France': 'Europe',
                     'South Korea': 'Asia',
                     'Italy': 'Europe',
                     'Spain': 'Europe',
                     'Iran': 'Asia',
                     'Australia': 'Australia',
                     'Brazil': 'South America'}
    # dictionary 로 부터 dataframe 생성
    # dictionary 의 키를 인덱스로 하는 경우 orient='index'
    # dictionary 의 키를 컬럼으로 하는 경우 orient='columns' (값이 여러개야 한다.)
    df_continent = pd.DataFrame.from_dict(ContinentDict, orient='index')
    # 인덱스 이름 'Country' 로 설정
    df_continent = df_continent.reindex(df_continent.index.rename('Country'))
    # 0번째 컬럼 이름 Continent 으로 변경
    df_continent = df_continent.rename(columns={0: 'Continent'})
    # 'Country' 인덱스 제거(대신 디폴트 인덱스로 변경)
    df_continent = df_continent.reset_index()
    # df_top 는 인덱스로, df_continent 는 'Country' 컬럼을 기준으로 inner 머지
    df_continent_top15 = pd.merge(
        df_top15, df_continent, how='inner', left_index=True, right_on='Country')
    # 'Continent' 컬럼을 인덱스 설정
    df_continent_top15 = df_continent_top15.set_index('Continent')
    return df_continent_top15


def answer_eleven():
    df = get_df_continent_top15()
    # df 다음 컬럼들 계산
    # Continent 인덱스 기준으로 대귝별 나라 개수 파악
    df['size'] = df.groupby(
        [df.index])['Country'].count()
    # estimante 합
    df['sum'] = df.groupby(
        [df.index])['estimate'].sum()
    # estimante 평균
    df['mean'] = df.groupby(
        [df.index])['estimate'].mean()
    # estimante 표준편차(standard deviation)
    # ddof(Delta Degrees of Freedom) 자유도(N-1)
    # 표준편차 계산시 분모(n-1, n 표본 개수)에서 1(디폴트) 대신 0설정
    df['std'] = df.groupby(
        [df.index])['estimate'].std(ddof=0)
    # 대륙 인덱스 중복 제거하고 대륙 오른차순 정렬
    return df[['size', 'sum', 'mean', 'std']].drop_duplicates().sort_index()


print(answer_eleven())
print(type(answer_eleven()))


def answer_twelve():
    df = get_df_continent_top15()
    # df 의 '%  Renewable' 컬럼에서 5개반 잘라 bins 컬럼으로 설정
    df['bins'] = pd.cut(df['% Renewable'], 5)
    # bins(구분지을때 사용하는 기준값) 컬럼 인덱스로 (기존+)추가
    df = df.set_index('bins', append=True)
    # print(df.index)
    # print(df.loc['Asia'])
    # print(df.loc['North America',])
    # 대륙별,bins별(멀티인덱스)로 그룹핑했을때 국가 개수
    df['country count'] = df.groupby(level=['Continent', 'bins'])[
        'Country'].count()
    # NaN 로우 제외하고 대륙별,bins별(멀티인덱스)로 정렬
    return df['country count'].where(df['country count'] > 1).dropna().sort_index()


print(answer_twelve())
print(type(answer_twelve()))


# estimate 값들을 천단위로 , 로구분, 반올림하지 않고
def answer_thirteen():
    df = answer_one()
    df['estimate'] = df['Energy Supply'] / df['Energy Supply per Capita']
    return df['estimate'].apply(lambda x: '{0:,}'.format(x))


print(answer_thirteen())
