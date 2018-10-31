#!/usr/bin/env python
# coding: utf-8
# ysoftman
# python version : 3.x

import numpy as np
import tensorflow as tf

# mkdir MNIST_DATA
# cd MNIST_DATA
# wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
# wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
# wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
# wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
from tensorflow.examples.tutorials.mnist import input_data
# read_data_sets 에서 mnist data 를 자동으로 다운로드된다.
mnist = input_data.read_data_sets("./MNIST-data/", one_hot=True)

tf.convert_to_tensor(mnist.train.images).get_shape()

# 가중치Weight, 편향bias는 학습할 값으로 계속 변하기 때문에 변수 텐서(노드)로 선언
#  0~9 10개의 종류가 있고 각 이미지는 28x28=784 크기를 가지는 벡터
W = tf.Variable(tf.zeros([784, 10]))
# 0~9 10개의 각 숮에 대한 편향값
b = tf.Variable(tf.zeros([10]))
# x 는 이미지(784차원 벡터) 입력값
x = tf.placeholder(tf.float32, [None, 784])
# x, w, b 로 0~9 중 하나를 선택할 수 있도록 해주는 확률 계산으로 softman 함수 적용
# softman 로 예측가능한 확률 y 를 구할 수 있다.
y = tf.nn.softmax(tf.matmul(x, W) + b)
# y' 는 원핫(인코딩)벡터로 실제 정답 데이터
y_ = tf.placeholder(tf.float32, [None, 10])

# cross entropy 는 우리가 만든 가설(예측한 확률 분포, y)이 실제값(y_)을 설명하기에 얼마니 비효율적인지 측정
cross_entropy = -tf.reduce_sum(y_ * tf.log(y))
# cross entropy (loss) 를 가장 작게 하는게 훈련의 목적이다.
# loss minimize 를 위해서는 경사하강법을 사용하고 이때의 경사하강법시 움직이는 폭(학습비율은) 0.01로 잡는다.
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)

# 전역 변수 초기화를 위한 노드
# init = tf.initialize_all_variables() # deprecated
init = tf.global_variables_initializer()
# 실행 준비
sess = tf.Session()
sess.run(init)


# 학습 획수 500번
for i in range(500):
    # 100개 묶음(배치) 데이터를 가져온다.
    batch_xs, batch_ys = mnist.train.next_batch(100)
    # 위 placeholder 로 생성한 노드들 자리에 배치데이터를 셋팅
    sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
    # 입력y와 실제 정답y  각각에서 최대값을 찾아서 이둘이 같으면 예측이 맞은것이다.(정답을 찾은경우)
    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
    # correct_prediction 를 1.0. 0.0 등의 수치로 캐스팅하여 이들의 평균을 계산하면 정확도(accuracy)가
    # 된다.
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    # 100번의 훈련마다
    if i % 100 == 0:
        # 현재의 훈련 스텝에서의 정확도를 출력
        print("[%d/%d]" % (i, 500), sess.run(accuracy, feed_dict={
              x: mnist.test.images, y_: mnist.test.labels}))

sess.close()
