# DeepLearning 요약 정리
## 개발 환경
- python 3.x
- numpy : 각종 수식을 쉽게 처리할 수 있는 다양한 기능 제공
- matplotlib : 데이터를 그래프로 표시

## 퍼셉트론(Perceptron)
- 다수의 신호를 입력으로 받아 하나의 신호촐 출력하는 모델
  - DeepLearning(예전에는 NeuralNet이라고 불림) 의 기원이됨
- x1, x2 node(뉴런) 에서 각가 w1, w2 가중치가 곱해져 y 출력되는 형태
- 쉽게 활성화(출력이 1이되는)하기 위해 bias(편향) 을 추가
- 각 노드에는 가중치와 편향이라는 파라미터가 존재
- 한개의 단편적인 퍼셉트론은 선형 문제만 처리(인식,분류...등)하고 비선형 문제는 처리할 수 없어 여러 개의 퍼셉트론을 층으로 쌓아 multi-layer-perceptron(다층퍼셉트론) 를 구성하여 비선형 문제를 해결

## 신경망(NeuralNet)
- 처음 입력과 최종 출력 사이 많은 은닉 층이 존재
- 퍼셉트론과 달리 입력에 편형, 가중치 등이 곱해셔 합산하여 출력되기전 활성화함수(activation function)을 통해 활성화(1)여부를 판단
  - 계단(step) 함수 : 어느 임계값 이상이면 활성화 시키는 함수, 계산이 간단하지만 그래프가 계단 모양처럼 가파르게 되어 노드들의 데이터를 제대로 출력층으로 반영하지 못함
  - 시그모이드(sigmoid) 함수 : 그래프가 s 를 닮음, 계산비용이 있지만 s 자 처럼 완만한 곡선으로 입력값들이 제대로 출력층에 반영됨
  - ReLu(Rectified Linear Unit) 함수 : 0 을 넙으려 입력값을 그대로 출력(활성), 계산 비용이 시그모이드보다 적고,의미 있는 입력 데이터도 출력층에 전달 할 수 있어 최근에 많이 쓰임
- 신경망의 입력, 출력을 계산할때는 행렬의 (내적)곱을 사용
  - numpy 의 dot() 사용
- 신경망의 최종 출력 노드들 중 가장 큰 값을 가진 노드를 결과 값이라 판단
- 소프트맥스(softmax) 함수는 최종 출력 노드들 전체 합이 1인 확률을값을 표현하고, 이 값으로 신경망의 입력으로 주어 학습하는데 사용
- 데이터 계산을 배치(batch, 묶음)단위로 처리하여 효율을 높인다
- 신경망을 입력에서 출력을 흘려서(전파해서) 결과(분류, 회귀)를 낸다는 의미로 순전파라고 한다
  - 분류(classification) : 물고기, 사람 등을 분류하는 문제
  - 회귀(regression) : 철수 사진을 보고 몸무게 예측하는 문제

## 신경망 학습(Learning)
- 신경망 학습으로 신경망에서 각 노드들의 최적의 파라미터(편향,가중치)를 찾는다.
- 학습(trainning, 훈련), 시험(test) 데이터로 나누어 실헐
- 신경망 학습이 잘되고 있는지 알기 위한 지표로 손실함수(loss function)을 사용
  - 정답데이터와, 출력데이터 간의 차이를 계산하여 하나의 확률료 나타낸다. 반복되는 학습을 통해 손실함수의 값이 가장 작은 출력데이터를 찾을 수 있다. 다음과 같은 방법이 있다.
    - 평균제곱오차(mean squared error, MSE)
    - 교차엔트로피(cross entropy error, CEE)
  - 손실함수의 값을 최대한 줄여주는 과정을 학습이라 볼 수 있다.
- 미니 배치 학습(mini batch)
  - 너무 많은 훈련 데이터는 시간이 너무 오래 걸려, 일부만(미니배치) 무작위로 골라 학습시킨다.
- 수치미분, 편미분, 기울기
  - 아주 작은 차분(difference, 차이)로 미분하는 것을 수치미분(numerical differentiation)
  - 변수가 여러개인 함수에세 구하고자 하는 변수값을 제외한 변수값들을 고정하여 계산(수치미분)하는것을 편미분(partial derivative)
  - 편미분들을 벡터 정리한것을 기울기(gradient)
  - 기울기를 이용해서 함수의 최초값을 찾도록 하는것을 경사하강겂(gradient descent method)
- 학습 과정, 확률적 경사하강법(SGD, Stochastic Gradient Descent) 사용
  1. 훈련 데이터 중 일부를 랜덤으로 데이터를 골른다(미니배치)
  2. 미니배치의 손실함수 값을 작은 쪽으로 구하기 위해 각 가중치 매개변수에 대한 기울기를 구한다.(기울기는 손실함수 값을 작게하는 방향을 가르킨다.)
  3. 가중치 매개변수를 기울기 방향으로 아주 조금 갱신한다.
  4. 1~3과정을 반복한다.
      - 손실함수 값이 가장 작고 변화가 거의 없다는것을 그래프를 그려 본다.
      - 시험데이터에 대해 테스트하여 가장 좋은 매개변수 학습된것을 찾는다.

## 오차역전파법(backpropagation)
 - 가중치 매개변수 값을 효율적으로 계산하기 위한 방법(수치미분은 단순하지만 계산시간이 오래 걸린다.)
   - 그래프에서 왼쪽에서 오른쪽으로 흐르는 순전파(forward propagation)
   - 순전파와 반대로 오른쪽에서 왼쪽으로 흐르는 역전파(bakward propagation)
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
  - 모멘텀(Momentum, 운동량이라는 의미) : 지그재그 정도가 덜(부드럽게) 하다.
  - AdaGrad(AdaptiveGradient) : 각각의 매개변수에 맞게(적응하여 adaptive) 조정하여 학습률을 조정하 효율적으로 최소값을 찾는다.
  - Adam(Momentum + AdaGrad 융합) : 부드럽게 효율적으로 최소값을 찾아 간다.
 - 가중치 초기값에 따른 신경망 학습 영향
   - 초기값이 0 이라면 모든 가중치의 값이 똑같이 갱시되어 올바른 학습이 이뤄지지 않는다.
   - 가중치 표준편차 초기값에 따라 은닉층에서의 활성화값 분포이 한쪽으로 치우지게 된다.
   - Xavier(사비에르) 초기값 : 앞 게층의 노드 n개라면 표준편차는 1/sqrt(n) 로 초기값 사용
     - 딥러닝 프래임워크에서 표준으로 많이 사용된다.
     - 앞 층의 노드 n 외 뒤 노드 수도 고려하여 설정하는 사비에르의 논문도 있다.
 - 배치 정규화
   
