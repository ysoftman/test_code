import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as stats

# 이항분포 : p 확률로 성공하는 n 번의 독립적인 시행에서 확률변수 x의 분포
# 50% 확률로 성공(앞면을 성공으로 가정)한는 동전던지기를 1번 수행했을때 성공 횟수가 리턴된다.
# n=1 : 독립적인 수행 횟수
# p=0.5 : 성공확률( n > 0)
# 0.5 확률로 1이 나온다.(0.5 확률로 0이 나온다.)
print(np.random.binomial(1, 0.5))
# 1~1000 번의 수행했을 50% 확률로 성공한 x 들의 개수(500 에 가까운 값들이 나온다.)
print(np.random.binomial(1000, 0.5))
# size=10: 이항분포를 10번 수행한 결과를 리스트로 리턴
print(np.random.binomial(1000, 0.5, 10))


# 50%확률로 성공하는 동전던지기를 20회 수행했을때 성공한 이항분포를 10000 번 수행한
# 결과들 중 15 이상값들의 평균
x = np.random.binomial(20, 0.5, 10000)
print([i if i >= 15 else "_" for i in x])
print([i for i in x if i >= 15])
print((x >= 15).mean())


# 토네이도가 0.01% 발생한다고 했을때
# chance_of_tornado = 0.01/100
chance_of_tornado = 0.0001
# 10만년동안 토네이도가 발생할 횟수
print(np.random.binomial(100000, chance_of_tornado))


# 토네이도가 1% 발생한다고 했을때
chance_of_tornado = 0.01
# 토네이도 발생 이항분포를 1000000(약 3천년에 해당하는 일수) 번 수행
tornado_events = np.random.binomial(1, chance_of_tornado, 1000000)
two_days_in_a_row = 0
# 3000년에 토네이도가 이틀 연속으로 발생하는 확률 파악
for j in range(1, len(tornado_events) - 1):
    # 두날이 모두 토네이도가 발생(==1)하면
    if tornado_events[j] == 1 and tornado_events[j - 1] == 1:
        # 이틀 연속으로 토네이도가 발생한것
        two_days_in_a_row += 1
# 2739.72602739726년 마다 토네이도가 x 번 발생한다.
print("{} tornadoes back to back in {} years".format(two_days_in_a_row, 1000000 / 365))


# 균등 분포
# low=0, high=1 사이에 값 하나를 균등하게 분포
print(np.random.uniform(0, 1))
# 정규분포(가우시안분포)
# loc=0.75 정규분포 평균
# scale=1 표준편차
print(np.random.normal(0.75))

# 표준편차 구하는 공식
distribution = np.random.normal(0.75, size=1000)
print(np.sqrt(np.sum((np.mean(distribution) - distribution) ** 2) / len(distribution)))
# 표준편차 함수
print(np.std(distribution))

# kurtosis(첨도, 분포의 뾰족한 정도)
print(stats.kurtosis(distribution))
# skewness(왜도, 분포에서 치우친 정도)
print(stats.skew(distribution))

# chisquare(카이제곱 x**2 분포)
chi_squared_df2 = np.random.chisquare(2, size=10000)
print(stats.skew(chi_squared_df2))
chi_squared_df5 = np.random.chisquare(5, size=10000)
print(stats.skew(chi_squared_df5))
# 그래프 그려보기
output = plt.hist(
    [chi_squared_df2, chi_squared_df5],
    bins=50,
    histtype="step",
    label=["2 degrees of freedom", "5 degrees of freedom"],
)
plt.legend(loc="upper right")
plt.show()
