# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : neural nets 로 mnist(엠니스트, 숫자 데이터) 인식하기
'''
mnist 데이터 다운로드민 넘파이 배열러 리턴하는 소스를 사용
https://github.com/WegraLee/deep-learning-from-scratch/blob/master/dataset/mnist.py 내용을 mnist.py 로 저장
'''

import numpy as np
from mnist import load_mnist
from PIL import Image


# mnist 데이터를 배열로 읽어온다
(train_img, train_label), (test_img, test_label) = load_mnist(
    flatten=True, normalize=False)
img = train_img[0]
label = train_label[0]
print (label)
# 784 길이의 1차원 배열로 로딩되었다.
print (img.shape)
# 784 = 28*28 2차원 배열로 변경
img = img.reshape(28, 28)
print (img.shape)

# PythonImageLibray 를 이용하이 이미지 보기
pil_img = Image.fromarray(np.uint8(img))
pil_img.show()
