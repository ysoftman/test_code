# coding: utf-8
# ysoftman
# 참고
# tensorflow vs scikit-learn
# tensorflow 가 deep learning 의 low level 수준의 기능을 제공하는 반면
# scikit-learn 은 이미 정립된 머신러닝 분류(결증트리,svm, p), 회귀, 클러스터링등의 알고리즘을 제공한다.
# scikit-learn 으로 딥러닝, 강화학스등을 구현하기에는 적절하지 않다.
# Machine Learning Recipes with Josh Gordon
# https://www.youtube.com/watch?v=84gqSbLcBFE
# sudo pip install sklearn scikit-learn numpy graphviz
import numpy as np
import graphviz
from sklearn import tree
# 아이리스 꽃 샘플 데이터가 scikit-learn 에 포함되어 있으니 임포트하자
# http://scikit-learn.org/stable/datasets/index.html#iris-dataset
from sklearn import datasets
iris = datasets.load_iris()

# 다음과 같은 과정(pipeline)을 실습
# 데이터를 train,test 구분 -> 분류기를 만들어 훈련 -> test 데이터로 분류가의 정확도 계산

# 아이리스 data(특징값 배열), target(꽃이름)을 함수로 표한하기 위해 x, y 로 명명, f(x) = y
# f(features) = lable 로 여기서 f 는 classifier
x = iris.data
y = iris.target

# 위 x,y 데이터들을 train(x_train, y_train), test(x_test, y_test) 로 나눈다.
# test_size=.5 는 반을 테스트로 데이터로 사용하겠다는 의미
# 총 150개의 아이리스 데이터가 있고 train 75, test 75 개로 나뉜다.
# from sklearn.cross_validation import train_test_split # scikit-learn v0.16
from sklearn.model_selection import train_test_split  # scikit-learn v0.20
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=.5)

# decisiontree classifier 생성
from sklearn import tree
dt_clf = tree.DecisionTreeClassifier()
# classifier 를 trainning
dt_clf.fit(x_train, y_train)

# test 데이터로 예측해보자
# 75 개의 예측결과(아이리스 이름(0 or 1 or 2) 가 출력된다.
predictions = dt_clf.predict(x_test)
print "using decisiontree classifier - tests : ", len(predictions)
print predictions

# classifier 얼마나 정확한지 test 데이터(아이리스 이름:정담) 과 예측결과를 점수로 계산해보자.
from sklearn.metrics import accuracy_score
print "accuracy : ", accuracy_score(y_test, predictions)


# 이번에는 KNeighbors 분류자를 사용해보자. 사용방법은 decisiontree 와 같아서 설명은 생략한다.
from sklearn.neighbors import KNeighborsClassifier
kn_clf = KNeighborsClassifier()
kn_clf.fit(x_train, y_train)
predictions = kn_clf.predict(x_test)
print "using KNeighbors classifier - tests : ", len(predictions)
print predictions
print "accuracy : ", accuracy_score(y_test, predictions)
