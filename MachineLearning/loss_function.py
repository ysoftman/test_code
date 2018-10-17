# -*- coding: utf-8 -*-
'''
author: ysoftman
python version : 3.x
desc : 손실(오차) 함수 
'''
# pip3 install numpy matplotlib
import numpy as np
from mnist import load_mnist


# 평균 제곱 오차(MSE)
# y(신경망 출력, 추정치) 과 t(정답) 과의 차이를 구한다.
def mean_squared_error(y, t):
    return 0.5 * np.sum((y - t)**2)


# 교차 엔트로피 오차(CE)
# y(신경망 출력, 추정치) 과 t(정답) 과의 차이를 구한다.
def cross_entropy_error(y, t):
    #  log (0) = -inf 마이너스 무한대로 계산이 불가능하여 아자 작은 값 delta 를 더한다.
    delta = 1e-7
    return -np.sum(t * np.log(y + delta))


# 교차 엔트로피 오차(배치 처리)
# y(신경망 출력, 추정치) 과 t(정답) 과의 차이를 구한다.
def cross_entropy_error_batch(y, t):
    delta = 1e-7
    print("y.ndim:", y.ndim)
    print("y:", y.size)
    print("t:", t.size)
    if y.ndim == 1:
        t = t.reshape(1, t.size)
        y = y.reshape(1, y.size)

    # 훈련데이터(y)가 one-hot-label 이면 레이블의 인덱스로 변환
    if t.size == y.size:
        t = t.argmax(axis=1)
    batch_size = y.shape[0]
    return -np.sum(np.log(y[np.arange(batch_size), t] + delta)) / batch_size

# 입력 x 값들에 대해서 활성화(출력 0이상)화 판단
if __name__ == "__main__":
    """
    어떤 손실 함수를 사용하더라도 신경망 결과1에 정답과의 오차가 적기 때문에 두번째 신경망 보다 더 정확한 파라미터를 가진것이다.
    """
    t = np.array([0, 0, 1, 0, 0, 0, 0, 0, 0, 0])
    # 신경망 결과1 (softmax 로 전체 1기준의 확률 값)
    y = np.array([0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0])
    # 0.0975
    print(mean_squared_error(y, t))
    # 0.510825457099
    print(cross_entropy_error(y, t))
    # 신경망 결과2 (softmax 로 전체 1기준의 확률 값)
    y = np.array([0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.6, 0.0, 0.0, 0.0])
    # 0.597
    print(mean_squared_error(y, t))
    # 2.30258409299
    print(cross_entropy_error(y, t))

    """
    mnist 데이터로 테스트
    one_hot_label 옵션으로 정답값을 1 나머지는 0으로 만든값을 취한다.(오차 계산을 위해선 1, 0으로 된 정답 배열과의 차이 계산이 필요하기 때문)
    """
    (train_img, train_label), (_, _) = load_mnist(
        flatten=True, normalize=True, one_hot_label=True)
    # 미니배치 학습(배치크기 : 10)
    # 훈련 데이터를 모두(60000개) 사용하면 계산 시간이 너무 크기 때무에 훈련 데이터중 10개만 무작위로 뽑아 사용한다.
    print(train_img.shape[0])
    random_index = np.random.choice(train_img.shape[0], 10)
    print("random_index :", random_index)
    img_batch = train_img[random_index]
    label_batch = train_label[random_index]
    # img_batch = img_batch.astype(int)
    label_batch = label_batch.astype(int)
    print(img_batch)
    print(label_batch)
    print(cross_entropy_error_batch(img_batch, label_batch))
