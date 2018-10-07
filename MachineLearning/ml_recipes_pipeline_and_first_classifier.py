# coding: utf-8
# ysoftman
# 참고
# tensorflow vs scikit-learn
# tensorflow 가 deep learning 의 low level 수준의 기능을 제공하는 반면
# scikit-learn 은 이미 정립된 머신러닝 분류(결증트리,svm, p), 회귀, 클러스터링등의 알고리즘을 제공한다.
# scikit-learn 으로 딥러닝, 강화학스등을 구현하기에는 적절하지 않다.
# Machine Learning Recipes with Josh Gordon
# pipeline -> https://www.youtube.com/watch?v=84gqSbLcBFE
# first classifier -> https://www.youtube.com/watch?v=AoeEHqVSNOw
# sudo pip install sklearn scikit-learn numpy graphviz
import random
from scipy.spatial import distance


# 유클리드 기하학(피타고라스의 정리)로 두 점(특징) 사이의 거리를 계산
def euc(a, b):
    return distance.euclidean(a, b)


# KNN classifier 을 만들어보자.
# KNN : 테스트 데이터와 (이웃하는) 가장 가까운 특징 데이터(거리가 같다면 가까운 점들의 개수K가 많은쪽을 선택)을
# 레이블(정답)으로 선택하는 알고리즘
class ScrappyKNN():

    # training 을 위한 함수로, training data 파타미터를 받는다.
    def fit(self, x_train, y_train):
        # training 데이터를 멤버변수로 기억해 둔다.
        self.x_train = x_train
        self.y_train = y_train

    # training 된 classifier 로 test(feature) 데이터를 받아 예측 수행하여 결과(label) 출력
    def predict(self, x_test):
        predictions = []
        # 훈련데이터의 label 을 하나를 랜덤하게 선태해 예측결과로 사용한다.
        # for d in x_test:
        #     y = random.choice(self.y_train)
        #     predictions.append(y)

        # 가장 가깐운 거리의 점(특징 데이터)으로 예측(레이블) 한다.
        for d in x_test:
            y = self.closeset(d)
            predictions.append(y)

        return predictions

    # 테스트데이터(d) 에 대해서 가장 가까운 위치의 특징데이터 찾아 결과(label) 출력
    def closeset(self, d):
        # 가까운 거리를 찾을때 기준의 되는 초기 거리를 하나 정한다.
        best_dist = euc(d, self.x_train[0])
        best_index = 0
        # 모든 training data 들 대해서
        for i in range(1, len(self.x_train)):
            # 가까운 거리를 가지는것을 찾는다.
            dist = euc(d, self.x_train[i])
            if dist < best_dist:
                best_dist = dist
                best_index = i

        # 가장 가까운 거리의 데이터의 레이블 리턴
        return self.y_train[best_index]

import numpy as np
import graphviz
from sklearn import tree
# 아이리스 꽃 샘플 데이터가 scikit-learn 에 포함되어 있으니 임포트하자
# http://scikit-learn.org/stable/datasets/index.html#iris-dataset
from sklearn import datasets
iris = datasets.load_iris()

# 다음과 같은 과정(pipeline)을 실습
# 데이터를 train,test 구분 -> 분류기를 만들어 훈련 -> test 데이터로 분류가의 정확도 계산

# 아이리스 data(특징값 배열), target(꽃이름)을 함수로 표한하기 위해
#  x(feature), y(label) 로 명명, f(x) = y , f 는 classifier
x = iris.data
y = iris.target

# 위 x,y 데이터들을 train(x_train, y_train), test(x_test, y_test) 로 나눈다.
# test_size=.5 는 랜덤하게 반을 테스트로 데이터로 사용하겠다는 의미
# 총 150개의 아이리스 데이터가 있고 train 75, test 75 개로 나뉜다.
# from sklearn.cross_validation import train_test_split # scikit-learn v0.16
from sklearn.model_selection import train_test_split  # scikit-learn v0.20
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=.5)

# decisiontree classifier 생성
from sklearn import tree
dt_clf = tree.DecisionTreeClassifier()
# classifier 를 training
dt_clf.fit(x_train, y_train)

# test 데이터로 예측해보자
# 75 개의 예측결과(아이리스 이름(0 or 1 or 2) 가 출력된다.
predictions = dt_clf.predict(x_test)
print "using decisiontree classifier - tests : ", len(predictions)
print predictions

# classifier 얼마나 정확한지 test 데이터(아이리스 이름:정담) 과 예측결과를 점수로 계산해보자.
from sklearn.metrics import accuracy_score
print "accuracy : ", accuracy_score(y_test, predictions)


# 이번에는 KNeighbors 분류자를 사용해서 pipeline 를 처리해보자.
from sklearn.neighbors import KNeighborsClassifier
kn_clf = KNeighborsClassifier()
kn_clf.fit(x_train, y_train)
predictions = kn_clf.predict(x_test)
print "using KNeighbors classifier - tests : ", len(predictions)
print predictions
print "accuracy : ", accuracy_score(y_test, predictions)


# 이번에는 직접 만든 classifier 분류자를 사용해서 pipeline 를 처리해보자.
scknn_clf = ScrappyKNN()
scknn_clf.fit(x_train, y_train)
predictions = scknn_clf.predict(x_test)
print "using ScrappyKNN classifier - tests : ", len(predictions)
print predictions
print "accuracy : ", accuracy_score(y_test, predictions)
