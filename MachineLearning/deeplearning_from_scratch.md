# DeepLearning from Scratch 요약

## 개발 환경

- python 3.x
- numpy : 각종 수식을 쉽게 처리할 수 있는 다양한 기능 제공
- matplotlib : 데이터를 그래프로 표현

## 퍼셉트론(Perceptron)

- 다수의 신호를 입력으로 받아 하나의 신호를 출력하는 모델
  - DeepLearning(예전에는 NeuralNet이라고 불림) 의 기원이됨
- x1, x2 node(뉴런) 에서 각각 w1, w2 가중치가 곱해져 y 출력되는 형태
- 쉽게 활성화(출력이 1이되는)하기 위해 bias(편향) 을 추가
- 각 노드에는 가중치와 편향이라는 파라미터가 존재
- 한개의 단편적인 퍼셉트론은 선형 문제만 처리(인식,분류...등)하고 비선형 문제는 처리할 수 없어 여러 개의 퍼셉트론을 층으로 쌓아 multi-layer-perceptron(다층퍼셉트론) 를 구성하여 비선형 문제를 해결

## 신경망(NeuralNet)

- 처음 입력과 최종 출력 사이 많은 은닉 층이 존재
- 퍼셉트론과 달리 입력에 편향, 가중치 등이 곱해셔 합산하여 출력되기전 활성화 함수(activation function)을 통해 활성화(0:비활성, 1:활성)여부를 판단
  - 계단(step) 함수 : 어느 임계값 이상이면 활성화 시키는 함수, 계산이 간단하지만 그래프가 계단 모양처럼 가파르게 되어 노드들의 데이터를 제대로 출력층으로 반영하지 못함
  - 시그모이드(sigmoid) 함수 : 그래프가 s 를 닮음, 계산비용이 있지만 s 자 처럼 완만한 곡선으로 입력값들이 제대로 출력층에 반영됨
  - ReLu(Rectified Linear Unit) 함수 : 0 을 넙으려 입력값을 그대로 출력(활성), 계산 비용이 시그모이드보다 적고,의미 있는 입력 데이터도 출력층에 전달 할 수 있어 최근에 많이 쓰임
- 신경망의 입력, 출력을 계산할때는 행렬의 (내적)곱을 사용
  - numpy 의 dot() 사용
- 신경망의 최종 출력 노드들 중 가장 큰 값을 가진 노드를 결과 값이라 판단
- 소프트맥스(softmax) 함수는 최종 출력 노드들을 전체 합이 1인 확률을값을 표현하고, 이 값을 신경망의 입력으로 주어 학습하는데 사용
- 데이터 계산을 배치(batch, 묶음)단위로 처리하여 효율을 높인다
- 신경망을 입력에서 출력을 흘려서(전파해서) 결과(분류, 회귀)를 낸다는 의미로 순전파라고 한다
  - 분류(classification) : 물고기, 사람 등을 분류하는 문제
  - 회귀(regression) : 철수 사진을 보고 몸무게 예측하는 문제

## 신경망 학습(Learning)

- 신경망 학습으로 신경망에서 각 노드들의 최적의 파라미터(편향,가중치)를 찾는다.
- 학습(training, 훈련), 시험(test) 데이터로 나누어 실헐
- 신경망 학습이 잘되고 있는지 알기 위한 지표로 손실함수(loss function)을 사용
  - 정답데이터와, 출력데이터 간의 차이를 계산하여 하나의 확률료 나타낸다. 반복되는 학습을 통해 손실함수의 값이 가장 작은 출력데이터를 찾을 수 있다. 다음과 같은 방법이 있다.
    - 평균제곱오차(mean squared error, MSE)
    - 교차엔트로피(cross entropy error, CEE)
  - 손실함수의 값을 최대한 줄여주는 과정을 학습이라 볼 수 있다.
- 미니 배치 학습(mini batch) : 너무 많은 훈련 데이터는 시간이 너무 오래 걸려, 일부만(미니배치) 무작위로 골라 학습시킨다.
- 수치미분 : 아주 작은 차분(difference, 차이)로 미분하는 것을 수치미분(numerical differentiation)
- 편미분 : 변수가 여러개인 함수에세 구하고자 하는 변수값을 제외한 변수값들을 고정하여 계산(수치미분)하는것을 편미분(partial derivative)
- 기울기
  - 편미분들을 벡터 정리한것을 기울기(gradient)
  - 경사하강법(gradient descent method, 줄여서 경사법)
    - 기울기를 이용해서 함수의 최소값(오류를 최소화)을 찾도록 하는것
    - 경사(하강법) 수식에서 η(eta)는 갱신하는 양을 의미하며, 한번의 학습으로 얼마만큼 학습해아할지를 나타내는 학습률(learning rate)이 된다.
    - 학습률과 같이 (실험을 통해)사람이 직접 설정하는 매개변수를 하이퍼파라미터(hyper parameter)라고 한다.
- 학습 과정, 확률적 경사하강법(SGD, Stochastic Gradient Descent) 사용
  1. 훈련 데이터 중 일부를 랜덤으로 데이터를 고른다(미니배치)
  2. 미니배치의 손실함수 값을 작은 쪽으로 구하기 위해 각 가중치 매개변수에 대한 기울기를 구한다.(기울기는 손실함수 값을 작게하는 방향을 가르킨다.)
  3. 가중치 매개변수를 기울기 방향으로 아주 조금 갱신한다.
  4. 1~3과정을 반복한다.
     - 손실함수 값이 가장 작고 변화가 거의 없다는것을 그래프를 그려 본다.
     - 시험데이터에 대해 테스트하여 가장 좋은 매개변수 학습된것을 찾는다.

## 오차역전파법(backpropagation)

- 가중치 매개변수 값을 효율적으로 계산하기 위한 방법(수치미분은 단순하지만 계산시간이 오래 걸린다.)
  - 그래프에서 왼쪽에서 오른쪽으로 흐르는 순전파(forward propagation)
  - 순전파와 반대로 오른쪽에서 왼쪽으로 흐르는 역전파(backward propagation)
- 계산 그래프는 노드는 연산(+,-등), 엣지는 이전 노드의 출력값으로 구성된다.
- 국소적 계산(각 노드는 자신과 관련된것만 계산만)하고 그 결과를 전달하여 전체 복잡한 문제를 해결한다.
  - 여기서의 계산은 편미분(∂,round)을 뜻한다.
  - y = f(x)의 경우, ∂y/∂x x에 대한 y의 미분
- 역전파 구조
  - z = x+y, ∂z/∂x=1, ∂z/∂y=1, 덧셈노드는 입력을 그대로 흘려보낸다.
  - z = xy, ∂z/∂x=y, ∂z/∂y=x, 곱셈노드는 서로 바꾼 입력값을 흘려보낸다.
- 활성화함수(Sigmoid, ReLu), affine, softmax 등 역전파에서의 맞게 계산(미분)하여 사용해야 한다.
  - 순전파에서 행렬의 내적곱을 계산하는 계층(신경망을 구성하는 층)을 affine 계층이라고 한다.

## 학습 관련 기술들

- 확률적 경사 하강법(SGD)
  - 매개변수의 기울기를 구해 기울어진 방향으로 매개변수 값을 계속 갱신
  - 타원형 모양의 그래프에서는 최소값을 찾을때까지 지그재그로 이동하여 비효율적인 단점이 있다.
- SGD 단점을 극복하기 위한 매개변수 갱신 방법들
- 모멘텀(Momentum, 운동량) : 지그재그 정도가 덜(부드럽게) 하다.
- AdaGrad(AdaptiveGradient) : 각각의 매개변수에 맞게(적응하여 adaptive) 조정하여 학습률을 조정하여 효율적으로 최소값을 찾는다.
- Adam(Momentum + AdaGrad 융합) : 부드럽게 효율적으로 최소값을 찾아 간다.
- 가중치 초기값에 따른 신경망 학습 영향
  - 초기값이 0 이라면 모든 가중치의 값이 똑같이 갱신되어 올바른 학습이 이뤄지지 않는다.
  - 가중치 표준편차 초기값에 따라 은닉층에서의 활성화값 분포이 한쪽으로 치우지게 된다.
  - Xavier(사비에르) 초기값 : 앞 게층의 노드 n개라면 표준편차는 1/sqrt(n) 로 초기값 사용
    - 딥러닝 프래임워크에서 표준으로 많이 사용된다.
    - 앞 층의 노드 n 외 뒤 노드 수도 고려하여 설정하는 사비에르의 논문도 있다.
- 배치 정규화(BatchNorm)
  - 입력 데이터 {x1, .. xn} 을 평균0, 분산 1로 고르게 분포된는 역할
  - 활성화 함수 앞 또는 뒤에 위치하며 데이터 분포를 덜 치우치게 한다.
  - 장점
    - 학습을 시간을 단축한다.
    - 초기값에 크게 의존하지 않는다.
    - 오버피팅을 억제한다.
- 오버피팅(훈련 데이터셋에 지나치게 적응되어 실제 데이터에는 정확도가 떨어지는것)
  - 훈련 데이터가 적거나 매개변수의 값이 커서 발생할 수 있다.
- 오버피팅 해결하기
  - 가중치감소(weight decay)
    - 학습과정에서 큰 가중치가 발현되면 큰 패널티를 부여하여 오프피팅을 방지하는 방법
  - 드롭아웃(drop out)
    - 훈련시 은닉층의 뉴런을 무작위로 골라 삭제하여 신호가 전달되지 못하게 하는 방법
    - 테스트시는 뉴런을 삭제하지 않고 모든 뉴런이 신호가 전달되게 하고 출력결과에 (1.0 - 훈련시 삭제한 뉴런의 비율) 값을 곱해서 출력한다.
- 하이퍼파라미터 찾기
  - 뉴런수, 배치크기, 매개변수 갱신시 학습률, 가중치 감소등 사람이 설정하는 값
  - 검증데이터(validation data)로 하이퍼파라미터 성능 평가
  - 하이퍼파라미터 최적 값 찾기(직과적인 방법)
    1. 하이퍼파라미터 범위 지정
    2. 지정된 범위에서 무작위로 1개 추출
    3. 무작위 추출된 값으로 하이퍼파라미터 성능 평가
    4. 위 단계 약 100회 반복하며 정확도로 하이퍼파라미터의 범위를 좁혀나간다.
    5. 좁혀진 범위내에서 하나의 하이퍼파라미터 선택
  - 좀더 수학적인 베이즈최적화(bayesian optimization)를 이용한 하이퍼파라미터 최적값 찾기도 있다.

## 합성곱 신경망(Convolutional Neural Network, CNN)

- 이미지, 음성 인식에 주로 사용
- CNN 합성곱계층(convolutional layer, conv)와, 풀링계층(pooling layer, pooling)을 사용하여 다음과 같이 구성(pooling 은 생략 가능)
  - conv -> ReLu -> pooling --> conv -> ReLu -> pooling --> ...
- 앞장에서 설명한 신경망들은 인접한 모든 뉴런과 완전연결(fully-connected)된 Affine 계층을 사용하여 다음과 같이 구성
  - affine -> ReLu --> affine -> ReLu --> ...
- 합성곱 계층(conv)
  - 완전연결 계층은 이미지(가로,세로,색상) 과 같은 3차원 데이터를 1차원으로 시리얼하게 처리하여 데이터 원래 형상이 무시되는 단점이 있다.
  - CNN 은 각 계층에서 데이터를 입/출력 특징맵(feature map)으로 부르기도 한다.
  - 각 계층에서 합성곱이 수행되며, 이는 이미지 처리에서의 사용되는 필터(커널) 연산으로 윈도우가 슬라이딩 되면서 매칭되는 원소끼로 곱하여 합한다.
  - 필터의 매개변수가 가중치에 해당하고, 합성곱 결과의 각 원소에 편향값을 더하게 출력 데이터를 만든다.
  - 합성곱 연산 전에 출력 크기 조정을 위해 입력 데이터 가장자라에 0으로 붙여 맵을 확장하는 패딩(padding) 작업을 수행한다.
  - 합성곱 연산시 필터 윈도우가 슬라이딩 될때 1칸,2칸...n칸을 이동시키는 것을 스트라이드(stride)로 부른다.
  - 스트라이드를 키우면 출력크기가 작아지고, 패딩을 크게하면 출력크기가 커진다.
  - 채널(이미지의 색상정보 같은)마다 필터와 합성곱 연산하고 이를 더해서 하나의 결과 데이터를 출력하도록 한다.
  - n개의 출력 데이터를 만들기 위해서 n개의 필터를 사용하고, 여기에 n개의 편향값을 더해 n개의 출력데이터를 만든다.
- 풀링 계층(pooling)
  - 입력 데이터(맵)의 가로,세로 크기를 줄인 출력데이터(맵)를 만든다. 예) 입력 4x4 -> 출력 2x2
    - 최대풀링(max pooling) : 입력데이터 2x2 대상영역에서 가장 큰 값을 선택해 출력값 원소 1개를 만든다.
    - 평균풀링(average pooling) : 대상영역내의 원소들의 평균 값을 출력값 원소1개가 된다.
  - 최대값이나 평균값을 계산하는 명확한 처리로 학습이 필요없고 채널마다 독립적으로 풀링 연산을 수행한다.
  - 입력 데이터에 약간의 변화는 (최대치나 평균값을 취하기 때문에) 풀링결과에 많은 변화를 주진 못한다.
- 합성곱/폴링 계층 구현
  - CNN 은 예(가로 28, 세로 28, 채널 1, 이미지 데이터가 10개)와 같이 4차와 데이터를 처리해야 한다.
    1. 겹겹의 for(성능저하) 를 사용하지 않기 위해 im2col 함수로 이미지1개->가로방향 1차원배열로 변환, 이미지n개->1차원배열xn개가 있는 2차원 행렬로 표현할 수 있다.
    2. 필터 데이터도 im2col 를 사용해서 2차원배열화 시킨다.(단 입력데이터와 행렬의 내적곱하기위새 이미지1개->세로방향으로 1차원배열)
    3. 입력2차원배열 과 필터2차원배열 를 행렬의 내적곱 연산을 수행한다.
    4. 3에서 출력된 2차원을 원래의 4차원데이터로 reshape 한다.
- CNN 시각화하기
  - 채널1개짜리인 필터들은 회식(0~255)값으로 표현할 수 있다.
  - 학습을 하면서 각각의 필터들은 특정 특징(가로에지, 세로에지...)에 반응하며 규칙성을 갖게된다.
  - 필터를 이미지로 시각화해보면 규칙성을 확일할 수 있다.
- CNN 합성곱 계층이 여러겹 쌓이면서 복잡하고 추상화된 정보가 추출된다.
- 대표적인 CNN 들
  - LeNet : 1998년에 제안된 손글씨 인식 CNN으로 단순히 합성곱계층과 풀링 계층을 반복하고 마지막에 완전연결 계층 적용하는 방식
  - AlexNet : 2012년에 발표된 CNN으로 LeNet 과 같은 구성이지만 활성화 함수로 ReLU 사용, LRN(Local Response Normalization) 이라는 국소적 정규화 계층을 이용, 드롭아웃을 적용하였다.

## 딥러닝(Deep Learning)

- mnist(Modified National Institute of Standards and Technology, 손글씨 인식을 위한 표준 숫자 데이터 샘풀) 숫자 데이터를 인식할때 99.38% 정확하고 나머지 0.62% 는 인간도 잘 구분할 수 없는 숫자 이미지 샘풀이다.
- 정확도를 높이기
  - 훈련 데이터(이미지)가 적은경우 인위적으로 이미지를 일부잘라냄(crop), 회전(rotate), 좌우반전(flip), 크기변경(scale) 등으로 데이터를 확장(늘린다.)
  - 최근의 딥러닝은 층을 깊게하여 정확도를 높인다.
    - 층을 깊게하여 매개변수의 수가 줄어(CNN에의 필터링 합성곱을 계속 할 수록)든다. 결국 학습할 데이터를 양이 줄어 학습효율을 높일 수 있다.
    - 각 층이 학습해야할 단순한 문제로 분해되어 효율적이다.
- 딥러닝 역사
  - 2012년 ILSVRC(Imagenet Large Scale Visual Recognition Challenge)대회에서 AlexNet이 그동안의 이미지 인식에 대한 접근을 뿌리째 흔든 딥러닝을 시작으로 주목을 받게 된다.
  - 이미지넷(ImageNet)은 100만장이 넘는 이미지 데이터로 ILSVRC 등에서 사용한다.
  - VGG : 3x3 작은 필터를 사용하는 계층을 연속적으로 사용
  - GoogLeNet : 앞 계층에 1x1, 3x3, 5x5 필터와 3x3 풀링 결과를 결합
  - ResNet : 스킵연결(Skip Connection) 입력데이터를 합성곱 계층윽 거치지 않고 바로 출력에 더하는 구조로 층을 깊게하며 발생될 수 있는 소실문제(오인식)을 방지
- 딥러닝은 곱셉,나누기등의 단순한 연산을 빠르게 처리해야 하기 때문에 많은 단순 코어로 병렬 처리에 좋은 GPU를 사용해야 학습 시간을 절약한다.(CPU 40일 vs GPU 6일, nvidia 의 CUDA 개발환경을 많이 사용)
- 더욱더 빠르게 처리하기 위해 분산환경에서 많은 GPU 사용한다.(GPU 1개 7일 vs GPU 100개 3시간, 56배 빨라짐)
  - 구글 tensorflow, 마이크로스포트 CNTK(Computational Network Toolkit) 등은 분산환경에 역점
- 고속화 처리를 위해 데이터 처리량을 비트 수를 줄인다.
  - 딥러닝 실수 표현시 16비트 반정밀도(half precision) 사용해도 문제가 없다고 한다.
- 딥러닝 활용분야
  - 사물검출, 분할
  - 사진 캡션 생성
    - 사진을 보고 이해해서 사진을 설명하는 문장을 생성한다.
    - NIC(Neural Image Caption) 모델로 CNN과 RNN(Recurrent Neural Network)이라는 자연어처리에 많이 사용되는 순환신경망을 사용한다.
    - RNN : 신경망이 순환구조로 되어 있어 이전의 생성된 정보를 기억하여 영향을 준다.
      - '나' 생성 '잤다' 생성, 이전 나라는 정보를 기억하여 '나'에 '는'을 붙여 '나는 잤다'를 만든다.
  - 이미지 화풍 흉내 : 반고흐 이미지 + 실세사진 => 반고흐와 같은 사진 생성
  - 이미지 생성
    - 대량의 침실이미지를 학습시켜, 존재하는 않은 침실 이미지를 생성한다.
    - DCGAN(Deep Convolutional Generative Adversarial Network) 기법 사용
      - GAN 은 가짜 이미지를 생성하는 생성자(Generator)와 이를 가짜인지 식별하는 식별자(Discriminator) 가 서로 경쟁하여 결과를 산출, 존재하진 않지만 정말 진짜 같은 이미지를 만든다.
  - 자율 주행 : CNN 기반의 SegNet 신경망이 있다
  - DQN(Deep Q-Network)
    - 강화학습(reinforcement learning) 기반
      - 에이전트라는 것이 주어진 환경에 맞게 행동하고, 행동에 의해 환경이 변한다.
      - 환경이 변하면 보상이 주어지며, 에이전트는 더 나은 보상을 받기위해 스스로 학습한다.
    - Q학습 이라는 강화학습 사용
      - 최적 행동 가치 함수라는 것으로 최적의 행동을 정한다.
    - 사람의 조작 수준을 뛰어 넘는 비디오 게임 사례
    - DQN 은 강화학습이 적용된 알파고(AlphaGo)를 만든 구글의 딥마인드(DeepMind)가 진행한 연구
