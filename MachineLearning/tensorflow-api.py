#!/usr/bin/env python
# coding: utf-8
# ysoftman
# python version : 3.x

import numpy as np
import tensorflow as tf


# 텐서플로우를 실행하기 위한 세션 선언
sess = tf.Session()


#####
# 상수
# shape(차원)=2x2 상수 텐서, sess.run 중에 값이 변경되지 않음
# 내부적으로 사용하는 이름을 x 로 지정, 디폴트 이름 Const 가된다.
# x = tf.constant([[1.0, 2.0], [3.0, 4.0]], name="x")
x = tf.constant([[1.0, 2.0], [3.0, 4.0]])

# 내부적으로 add 라는 이름의 텐서가 생성된다.
x = x + 1

print(x)
# 텐서의 값을 출력하기위해서 텐서를 실행(흘려보낸다.)해준다.
print(sess.run(x))

# 아래 x 는 사실 내부적으로 Const_1 의 이름을 사용하게 된다.
# name 값을 주더라도 이미 사용중인 name이 있으면 name_1 이름으로 생성한다.
# x = tf.constant([[2, 3]], name="x")
x = tf.constant([[2, 3]])
print(x)
print(sess.run(x))


#####
# 변수
# 1x2 텐서 변수 생성, sess.run 중에 값이 변경될 수 있음
# 디폴트 이름 Variable 가된다.
y = tf.Variable([[5, 6]])
print(y)
# 변수는 실행전 반드시 초기화를 해줘야 한다.
sess.run(tf.global_variables_initializer())
print(sess.run(y))

# 위에 add 연산을 한번 했기 때문에 내부적으로 add_1 라는 이름의 텐서가 생성된다.
y = y + 1

print(y)
# 변수는 실행전 반드시 초기화를 해줘야 한다.
sess.run(tf.global_variables_initializer())
print(sess.run(y))


#####
# placeholder
# sess.run 할때 값을 명시하기 위한 자리만 마련해둔다.(feed 메커니즘)
z1 = tf.placeholder(tf.float32)
z2 = tf.placeholder(tf.float32)
z3 = z1 + z2
# sess.run 할때 feed_dict 으로 placeholder 노드에 실제 값을 명시(대입)한다.
print(sess.run([z3], feed_dict={z1: [5.], z2: [7.]}))

# 같은 shape 의 값만 명시해야 한다.
z3 = tf.placeholder(tf.float32, shape=[1, 2])  # 1x2 차원
z4 = tf.placeholder(tf.float32, shape=[1, 2])  # 1x2 차원
z5 = z3 + z4
print(sess.run([z5], feed_dict={z3: [[5., 6.]], z4: [[7., 8.]]}))


#####
# reduce_sum : 차원내 모든 요소들의 합
# reduce_mean : 차원내 모든 요소들의 평균
x = tf.constant([[1., 1.], [2., 2.]])
# (1+1+2+2)
print(sess.run(tf.reduce_sum(x)))
# 0번째 차원은 제외하고 더한다. [(1+2), (1+2)]
print(sess.run(tf.reduce_sum(x, axis=0)))
# 1번째 차원은 제외하고 더한다. [(1+1), (2+2)]
print(sess.run(tf.reduce_sum(x, axis=1)))
# (1+1+2+2)/4
print(sess.run(tf.reduce_mean(x)))
# 0번째 차원은 제외하고 평균을 구한다. [(1+2)/2, (1+2)/2]
print(sess.run(tf.reduce_mean(x, axis=0)))
# 1번째 차원은 제외하고 평균을 구한다. [(1+1)/2, (2+2)/2]
print(sess.run(tf.reduce_mean(x, axis=1)))
