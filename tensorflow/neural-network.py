# python version : 3.x
import numpy as np
import matplotlib as plt
import pandas as pd
import seaborn as sb
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

# mkdir MNIST_DATA
# cd MNIST_DATA
# wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
# wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
# wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
# wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
# read_data_sets 에서 mnist data 를 자동으로 다운로드된다.
mnist = input_data.read_data_sets("./MNIST_DATA", one_hot=True)

tf.convert_to_tensor(mnist.train.images).get_shape()

W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))

x = tf.placeholder("float", [None, 784])
y = tf.nn.softmax(tf.matmul(x, W) + b)

y_ = tf.placeholder("float", [None, 10])
cross_entropy = -tf.reduce_sum(y_ * tf.log(y))
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)


sess = tf.Session()
sess.run(tf.initialize_all_variables())

for i in range(1000):
    batch_xs, batch_ys = mnist.train.next_batch(100)
    sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
    if i % 100 == 0:
        print(sess.run(accuracy, feed_dict={
              x: mnist.test.images, y_: mnist.test.labels}))
