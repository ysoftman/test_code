# coding: utf-8
# ysoftman
# python version : 3.x

import numpy as np
import tensorflow as tf

# tensorflow 는 graph 를 구성하고 이를 실행(session)하는 구조다.
# graph 의 node 는 tensor(다차원 배열)을 가지고 연산(operation)을 하는 곳이다.


# 1. graph 구성
# 별도의 graph 를 생성하지 않는다면 기본적으로 default graph 를 이용하게 된다.
# 1x2 텐서를 가진 노드 생성
# constant 별도의 입력이 필요없다.
matrix1 = tf.constant([[1, 2]])

# 2x1 텐서를 가진 노드 생성
matrix2 = tf.constant([[1], [2]])

# 위의 2개의 노드를 행렬곱(production) 연산을 노드 생성
matproduction = tf.matmul(matrix1, matrix2)


# 2. graph 실행
# 위의 노드들은 default graph 에 속해있다.
# default graph 를 실행하기
# 실행은 위한 session 생성
sess = tf.Session()

# cpu 첫번째 코어에서 실행
tf.device("cpu:0")

# session 의 run() 으로 default graph 실행
# matproduction 노드는 matrix1, matrix2 노드를 연산하기 때문에 총 3개의 노드모두가 실행된다고 볼 수 있다.
result = sess.run(matproduction)

print(result)

# 더이상 실행할 노드가 없다면 세션 종료
sess.close()


#####

# 위 과정을 다음과 같이 할 수 있다.
# with 가 끝나면 sess.close() 가 자동 호출된다.
with tf.Session() as sess:
    with tf.device("cpu:0"):
        matrix1 = tf.constant([[1, 2]])
        matrix2 = tf.constant([[1], [2]])
        matproduction = tf.matmul(matrix1, matrix2)
        result = sess.run(matproduction)
        print(result)
