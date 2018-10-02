# coding: utf-8
# ysoftman
# Machine Learning Recipes with Josh Gordon
# https://www.youtube.com/watch?v=cKxRvEZd3Mw

# sudo pip install sklearn scikit-learn
from sklearn import tree

fruites = ["apple", "orange"]


def toFruiteName(n):
    if n >= len(fruites):
        return "error"
    return fruites[n]

# datas
# [weigth(g), texture(bumpy=0, smooth=1)
features = [
    [140, 1],
    [130, 1],
    [150, 0],
    [170, 0],
]
# apple=0, orange=1
labels = [0, 0, 1, 1]

# classifier
# 빈(결정 조건이 아무것도 없는) 결정트리를 구성
clf = tree.DecisionTreeClassifier()
# 위 데이터를 가지고 훈련하여 결정트리를 완성하자.
clf = clf.fit(features, labels)

# make predictions
# 151g, smooth(1), 175g smooth(1) 인 경우는 사과일수도 오렌지 일수도 있어 결과가 매번 다를 수 있다.
result = clf.predict([[180, 0], [123, 1], [151, 1], [175, 1]])
for i in result:
    print toFruiteName(i)
