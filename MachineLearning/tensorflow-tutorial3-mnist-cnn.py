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


#####
# CNN(Convolutional Neural Network) 만들기

# 가중치에 약간의 잡음(초기화)을 준다.
def weight_variable(shape):
    # standard deviation(표준 편차)는 0.1
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)


# 편향이 0이 되는것을 막기 위해 0.1 로 초기화
def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)


# convolution(합성곱) 설정
# x 는 4차원 [batch, in_height, in_width, in_channels] [batch,28,28,1] 손글씨 이미지를 가진 텐서
# filter(슬라이팅되면서 적용할 필터 윈도우) = [filter_height, filter_width, in_channels, out_channels] [3,3,1,32], 32개츼 출력 채널을 만든다.
# stride(d(차원)에서 슬라이딩,건너뛰는 정도,거리),[0],[3] 은 1여야 한다. [1],[2] 는 같은 값으로 1칸씩 슬라이딩
# padding(2d가장자리 채우는것)=SAME : 윈도우 왼쪽과 오른쪽 똑같이 0값 패딩(삽입)한다.
# 만약 열이 홀수면 오른쪽에 추가한다.
# 출력의 크기를 입력과 같게하는 효과가 있다.
def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding="SAME")


# pooling 설정
# batch(묶음)로 실행할때
# strides = ksize(kernelsize) = [one image, width, height, channel] 로
# 이미지 한개에 대해서 2x2 로 풀링(줄인다)한다.
def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding="SAME")


#####
# 첫번째 합성곱 계층(conv1)
# 가중치 설정 : 5(height)x5(width)x1(channels,depth) 윈도우 크기에 32개의 필터사용한 구조(shape)의 텐서 정의
W_conv1 = weight_variable([5, 5, 1, 32])
# 편향 설정
b_conv1 = bias_variable([32])


# 입력값x 를 conv2d 에 대입하기 위해 (나머지크기)x28(height)x28(width)x1(channel) 4차원(텐서)로 reshape
# 첫번째 -1 의미(나머지크기) : 2차원 28, 3차원 28, 4차원 1, 의 크기로 맞춘 나머지 크기를 1차원으로 설정한다.
# 일반적으로 이미지 입력은 [나머지, height, width, channel(depth)] shape 으로 나타낸다.
x_image = tf.reshape(x, [-1, 28, 28, 1])

# x_image 에 가중치와 합성곱후 편향을 더한뒤 ReLU(활성화 함수) 적용
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
# 맥스 풀링(여러개중에 하나를 선택하여 크기를 줄임, sampling)하여 출력
h_pool1 = max_pool_2x2(h_conv1)


#####
# 두번째 합성곱 계층(conv2)
# 5x5x32의 이미지에 대해 64개 필터
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

# 첫번째 계층에서 풀링된 h_pool1 에 가중치와 합성곱후 편향을 더한뒤 ReLU(활성화 함수) 적용
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
# 두번째 계층의 합성곱 활성화 함수 결과 h_conv2 에 대한 맥스 풀링 출력
h_pool2 = max_pool_2x2(h_conv2)


#####
# 완전 연결 계층(Fully Connected Layer)
# 위 2계층을 거쳐 7x7 로 줄어든 이미지에 1024개의 뉴런(노드)으로 완결 연결 계층을 구성
# 7*7*64 는 7x7 필터 64 를 1차원으로 시리얼하게 표현
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

# 두번째 계층에서 풀링된 h_pool2 에 대해서 나머지x(7*7*64)차원으로 변환
h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * 64])
# 완전 연결 계층에 마지막으로 행렬곱(production)결과에 ReLU함수 적용
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)


# overfitting 방지를 위한  dropout
# dropouput 되지 않을 확률을 placeholder 로 만들어 둔다.
# placeholder 로 만들어두면 훈련시에만 dropout 을 사용하고 테스트할때는 뺄 수 있다.
keep_prob = tf.placeholder(tf.float32)
# dropout 은 뉴런의 출력을 자동으로  scaling 해준다.
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)


# softmax
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])
y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

#####
# training
# 손실 최소화 방법으로 크로스엔트로피 사용
cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ *
                                              tf.log(y_conv), reduction_indices=[1]))
# 경사하강법 대신 ADAM 최적화 알고리즘으로 크로스엔트로피를 최소화 하는 구간을 찾는다.
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
# 입력(y_conv)과 정답(y_의 최대값) 같으면 맞춘것
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y_, 1))
# correct_prediction 평균을 구한면 정확도를 알 수 있다.
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

# 실행을 위한 세션 선언
sess = tf.Session()
# 훈련 시작전 전역변수들 모두 초기화
sess.run(tf.global_variables_initializer())
for i in range(1000):
    # 50묶음씩 처리
    batch = mnist.train.next_batch(50)
    # 100번마다 현재 훈련 정확도 상태 보기
    # 이전 nn 로 인식한것보다 (0.91%정도)보다 훈련 10번만에 0.99%(거의 100%)로 정확도가 높다.
    if i % 100 == 0:
        # 사용할 session을 명시해야만 에러가 발생하지 않는다.
        train_accuracy = accuracy.eval(session=sess,
                                       feed_dict={x: batch[0], y_: batch[1], keep_prob: 1.0})
        # %g : Same as "e" if exponent is greater than -4 or less than precision, "f" otherwise.
        print("[%d/%d], training accuracy %g" %
              (i, 1000, train_accuracy))
    sess.run(train_step, feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})

# 훈련 종료 후 실제 mnist 테스트 이미지로 인식하여 정확도 산출
print("test accuracy %g" % accuracy.eval(session=sess,
                                         feed_dict={x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))
sess.close()
