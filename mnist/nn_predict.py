# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : neural nets 로 mnist(엠니스트, 숫자 데이터) 인식하기
'''
mnist 데이터 다운로드민 넘파이 배열러 리턴하는 소스를 사용
https://github.com/WegraLee/deep-learning-from-scratch/tree/master/ch03/sample_weight.pkl 가중치 값 저장
https://github.com/WegraLee/deep-learning-from-scratch/blob/master/dataset/mnist.py 내용을 mnist.py 로 저장
'''

import numpy as np
import pickle
from mnist import load_mnist
from PIL import Image
from activation_function import sigmoid, softmax


# mnist 데이터를 배열로 읽어온다
def get_mnist_data():
    # load_mnnist 를 한번 해두면 mnist.pkl 파일로 덤프해두어 이후 로딩시 빠르게 로딩된다.
    (train_img, train_label), (test_img, test_label) = load_mnist(
        flatten=True, normalize=False)
    return train_img, train_label, test_img, test_label


# mnist 이미지 하나 보기
def show_mnist_one():
    _, _, test_img, test_label = get_mnist_data()

    img = test_img[0]
    label = test_label[0]
    print (label)
    # 784 길이의 1차원 배열로 로딩되었다.
    print (img.shape)
    # 784 = 28*28 2차원 배열로 변경
    img = img.reshape(28, 28)
    print (img.shape)

    # PythonImageLibray 를 이용하이 이미지 보기
    pil_img = Image.fromarray(np.uint8(img))
    pil_img.show()


#
def init_network():
    with open("sample_weight.pkl", 'rb') as f:
        network = pickle.load(f)
    return network


# nn 구성하여 예측하기
def predict(network, x):
    W1, W2, W3 = network['W1'], network['W2'], network['W3']
    b1, b2, b3 = network['b1'], network['b2'], network['b3']

    # 2 층 레이어 구성
    # 각 레이어 에서는 행렬(데이터를 2차원 배열로 취급)의 내적곱 계산
    a1 = np.dot(x, W1) + b1
    # sigmoid 활성화 함수로 활성화 여부를 결정한다.
    z1 = sigmoid(a1)
    # 위 과정을 다음 레이어에서 반복
    a2 = np.dot(z1, W2) + b2
    z2 = sigmoid(a2)
    a3 = np.dot(z2, W3) + b3
    # 최종 결과시에는 softmax 로 각 노드(숫자0~9)를 1.0 기준 확률로 계산한다.
    # 실제 노트 값이 가장 큰값이 가장 높은 확률로 계산되고 계산 비용이 비싸서
    # softmax 는 실제 사용시에는 사용하지 않고, 훈련할때만 사용한다.
    y = softmax(a3)

    return y


if __name__ == "__main__":
    # mnist 이미지 하나 보기 테스트
    # show_mnist_one()

    # mnist 인식하기
    _, _, t_img, t_label = get_mnist_data()
    network = init_network()
    accuracy_cnt = 0
    for i in range(len(t_img)):
        y = predict(network, t_img[i])
        p = np.argmax(y)  # 확률이 가장 높은 노드의 출력값이 인식 결과다
        # 실제 레이블과 같음면 인식이 잘된 것이다
        if p == t_label[i]:
            accuracy_cnt += 1
    print("Accuracy:" + str(float(accuracy_cnt) / len(t_img)))
