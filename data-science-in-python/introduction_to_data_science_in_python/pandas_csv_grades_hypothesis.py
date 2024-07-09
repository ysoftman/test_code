import numpy as np
import pandas as pd
import scipy.stats as stats
import matplotlib
import matplotlib.pyplot as plt

# 과제 제출에 따른 등급 csv 파일
df = pd.read_csv("grades.csv")
print(df)
print(len(df))


# 2015-12-31 이전에 과제1(assignment1_submission)을 제출한 학생의 등급
# assignment1_submission 는 datetime 으로 되어 있어 날짜 계산할 수 있다.
early = df[df["assignment1_submission"] <= "2015-12-31"]
# 2015-12-31 이후에 과제1(assignment1_submission)을 제출한 학생의 등급
late = df[df["assignment1_submission"] > "2015-12-31"]
# print(early[['assignment1_submission']])
print(early.mean())
print(late.mean())


# hypothesis(가설)은 2개가 있다.
# - 대립가설(alternative hypotheses) : 두 그룹간 차이가 있다
# - 귀무가설(null hypothesis) : 두 그룹간 차이가 없다.(대립가설의 반대)
# 귀무가설이 참이면 대립가설의 신빙성이 조금 더 높다는 의미
# 역치(threshold, alpha, 기대하는 값)로 보통 0.05(5%) 또는 0.01(1%)으로 상황에 맞게 두자.
# TTest 두 집단이 서로 다른 평균을 가지고 있는지 비교
# a: 과제1 일찍 제출 그룹 데이터
# b: 과제2 늦게 제출 그룹 데이터
# return values
# statistic : 두집단의 차이 평균차/두집단의 편차=tscore
# pvalue : 유의확률, 분포의 양쪽 끝에 tscore 를 기준으로 양쪽 밖(왼쪽은 작은쪽으로, 오른쪽은 큰쪽으로)의 값)

# assignment1_grade 평균 74.972741, assignment1_grade 평균 74.017429 으로 평균이 다르지만
# p=0.16148283016060577 > alpha(0.05)로 귀문가설을 기각(reject)할 수 없다.=> 두 집간의 차이가 없다는것을 의미
print(stats.ttest_ind(early["assignment1_grade"], late["assignment1_grade"]))
# assignment2_grade 평균 67.252190, assignment2_grade 평균 66.370822 으로 평균이 다르지만
# p=0.18563824610067967 > alpha(0.05)로 귀문가설을 기각(reject)할 수 없다.=> 두 집간의 차이가 없다는것을 의미
print(stats.ttest_ind(early["assignment2_grade"], late["assignment2_grade"]))
# assignment3_grade 평균 61.129050, assignment3_grade 평균 60.023244 으로 평균이 다르지만
# p=0.08710151634155668 < alpha(0.05)로 귀문가설을 기각(reject)할 수 있다.=> 두 집간의 차이가 있다는것을 의미
print(stats.ttest_ind(early["assignment3_grade"], late["assignment3_grade"]))
# assignment4_grade 평균 54.157620, assignment4_grade 평균 54.058138 으로 평균이 다르지만
# p=0.8710666110447575 > alpha(0.05)로 귀문가설을 기각(reject)할 수 없다.=> 두 집간의 차이가 없다는것을 의미
print(stats.ttest_ind(early["assignment4_grade"], late["assignment4_grade"]))
# assignment5_grade 평균 48.634643, assignment5_grade 평균 48.599402 으로 평균이 다르지만
# p=0.9516513635792874 > alpha(0.05)로 귀문가설을 기각(reject)할 수 없다.=> 두 집간의 차이가 없다는것을 의미
print(stats.ttest_ind(early["assignment5_grade"], late["assignment5_grade"]))
# assignment6_grade 평균 43.838980, assignment6_grade 평균 43.844384 으로 평균이 다르지만
# p=0.9922074255698552 > alpha(0.05)로 귀문가설을 기각(reject)할 수 없다.=> 두 집간의 차이가 없다는것을 의미
print(stats.ttest_ind(early["assignment6_grade"], late["assignment6_grade"]))


# 위 6개의 데이터에서 3번과제만 귀무가설을 기각해 두집단간의 차이가 있다고 나오고 나머지 5개의 경우는 차이가 없다고 결과가 나왔다.
# 따라서 많은 데이터에 대해서 확인이 필요하다.
