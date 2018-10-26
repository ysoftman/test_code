# coding: utf-8
# ysoftman
# python version : 3.x

import numpy as np
import tensorflow as tf

# tensorflow 는 graph 를 구성하고 이를 실행(session)하는 구조다.
# graph 의 node 는 tensor(다차원 배열)을 가지고 연산(operation)을 하는 곳이다.
# tensorflow : tenosr 들이 정의된 노드들로 구성된 그래프에서 흘러간다는 의미

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


##########

# 그래프를 한번 작용 시킨 후 전역 변수들을 초기화해 한다.
initglobalvariable = tf.global_variables_initializer()

# 위 과정을 다음과 같이 할 수 있다.
# with 가 끝나면 sess.close() 가 자동 호출된다.
with tf.Session() as sess:
    # (이전 세션의 흔적을 없애기 위해서)전역 변수 초기화
    sess.run(initglobalvariable)
    with tf.device("cpu:0"):
        matrix1 = tf.constant([[1, 2]])
        matrix2 = tf.constant([[1], [2]])
        matproduction = tf.matmul(matrix1, matrix2)
        result = sess.run(matproduction)
        print(result)


##########

# ipython 과 같은 인터렉티브 환경에서 실행하기 위한 세션 생성
sess = tf.InteractiveSession()

# 변수 값을 가지는 노드 생성
var1 = tf.Variable([1.0, 2.0])
# var1 변수를 초기화
var1.initializer.run()

const1 = tf.constant([3.0, 3.0])

# var1 변수노드에서 const 값을 빼는 노드 생성
sub = tf.subtract(var1, const1)

# 그래프를 한번 작용 시킨 후 전역 변수들을 초기화해 한다.
initglobalvariable = tf.global_variables_initializer()


# (이전 세션의 흔적을 없애기 위해서)전역 변수 초기화
sess.run(initglobalvariable)

# result = sess.run(sub)
# print(result)
# sess.run(수행할노드) 대신 수행할노드.eval() 으로 간단하게 쓸 수 있다.
print(sub.eval())

sess.close()


##########


# 스칼라로 0 값을 가지는 변수 노드 생성
var1 = tf.Variable(0, name="counter")
const1 = tf.constant(1)
# var1 에 const1 값을 더하는 작업을 하는 노드 생성
addresult = tf.add(var1, const1)
# 더한결과를 var1 에 할당하는 작업을 하는 노드 생성
update = tf.assign(var1, addresult)


# 그래프를 한번 작용 시킨 후 전역 변수들을 초기화해 한다.
# (var1, const1 노드를 만들것을 전역 변수로 셋팅하는 과정)
initglobalvariable = tf.global_variables_initializer()


with tf.Session() as sess:
    # (이전 세션의 흔적을 없애기 위해서)전역 변수 초기화
    sess.run(initglobalvariable)
    # 더하기를 수행하기전의 초기 var1 값 출력
    print(sess.run(var1))
    # var1 에 1을 더하는 위 그래프를 10번 반복 수행하면
    for _ in range(10):
        sess.run(update)
        # 그래프가 실행된 후 var1 이 바뀐것을 알 수 있다.
        # print(sess.run(var1))
        print(var1.eval())


##########

var1 = tf.constant([3.0])
var2 = tf.constant([2.0])
var3 = tf.constant([5.0])
intermediate = tf.add(var2, var3)
mulresult = tf.multiply(var1, intermediate)

initglobalvariable = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(initglobalvariable)
    # 그래피 실행
    print(mulresult.eval())
    # 2개 이상의 노드를 실행하여 각 노드의 결과(tensor)을 파악할 수 있다.
    print(sess.run([mulresult, intermediate]))


##########

# 노드는 const, variable 로 값을 직점 명시하는 대신 placehold 로 표할 수 있다.(feed 메커니즘)
var1 = tf.placeholder(tf.float32)
var2 = tf.placeholder(tf.float32)
# var3 = tf.multipy(var1, var2)
# 사칙연산은 다음과 사용할 수 도 있다.
var3 = var1 * var2
# var3 = var1 / var2
# var3 = var1 + var2
# var3 = var1 - var2

initglobalvariable = tf.global_variables_initializer()
with tf.Session() as sess:
    sess.run(initglobalvariable)
    # 그래프 실행시 위 placeholder 에 들어갈 값을 명시한다.
    print(sess.run([var3], feed_dict={var1: [7.], var2: [2.]}))
