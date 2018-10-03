# coding: utf-8
# ysoftman
# Machine Learning Recipes with Josh Gordon
# https://www.youtube.com/watch?v=tNa99PG8hR8
# sudo pip install sklearn scikit-learn numpy graphviz
import numpy as np
import graphviz
from sklearn import tree
# 아이리스 꽃 샘플 데이터가 scikit-learn 에 포함되어 있으니 임포트하자
# http://scikit-learn.org/stable/datasets/index.html#iris-dataset
from sklearn.datasets import load_iris
iris = load_iris()

# 아이리스 특징들
print iris.feature_names
# 아이리스 종류(이름)
print iris.target_names

# 특징에 대한 값들을 배열로 가지고 있다.
# print iris.data[0]

# 아이리스의 종류
# print iris.target[0]
# print iris.target_names[iris.target[0]]

# 전체 데이터 출력(총 150개)
# for i in range(len(iris.target)):
# print "%d: label %s,  features %s" % (i,
# iris.target_names[iris.target[i]], iris.data[i])


# train data 생성(147개)
# 150 개의 데이터 중 0, 50, 100번째 데이터는 테스트 데이로 사용하기 위해서 뺀다
test_idx = [0, 50, 100]
train_target = np.delete(iris.target, test_idx)
train_data = np.delete(iris.data, test_idx, axis=0)
# print len(train_target)
# print len(train_data)

# test data 생성(3개)
test_target = iris.target[test_idx]
test_data = iris.data[test_idx]
# print len(test_target)
# print len(test_data)


# classifier
# 빈(결정 조건이 아무것도 없는) 결정트리를 구성
clf = tree.DecisionTreeClassifier()
# 위 데이터를 가지고 훈련하여 결정트리를 완성하자.
clf = clf.fit(train_data, train_target)

# test data 의 3개의 아이리스 이름
print test_target, iris.target_names[test_target]
# 결정트리 분류기로 test data 를 예층해보면 테스트 데이터의 이름(아이리스 이름, 정답)과 같다.
print clf.predict(test_data)


# decision tree 시각화해서 pdf 파일로 출력
# graph.render("iris")
dot_data = tree.export_graphviz(clf, out_file=None,
                                feature_names=iris.feature_names,
                                class_names=iris.target_names,
                                filled=True, rounded=True,
                                special_characters=True)
graph = graphviz.Source(dot_data)
graph.render("iris")
