# K-MOOC '인공지능 및 기계학습'

2018년 KAIST 오혜연 교수

## 1주차 - 확률론 및 나이브 베이즈(Probability and Naive Bayes)

### Bayes Rules

- 조건부 확률(Conditional Probability)
  - P(Y|X) : X가 조건으로 주어졌을때(given), Y 가 일어날 확률
- Bayes rules 이란

```text
P(Y|X) : x 가 조건으로 주어졌을때 y 의 확률
에 대해서 궁금한경우를 반대로
P(X|Y) : y 가 조건으로 주어졌을때 x 의 확률
로 바꿔서 사용할 수 있다.

# Y: 비가 올 활률, y: 비가 온다. 또는 비가 오지 않는다. Y 의 값
# X: 구름이 낄 확률, x: 구름이 낀다. 또는 구름이 끼지 않는다. X 의 값
# y' : y의 가능한 모든 값
P(Y=y|X=x) = P(Y=y)P(X=x|Y=y) / SUM(y') P(Y=y')P(X=x|Y=y')

# Quiz
확률 변수 X 는 오늘 구름이 끼었는지를 나타내고 (구름이 끼었으면 X=1, 구름이 끼지 않았으면 X=0),
확률 변수 Y 는 오늘 비가 올 것인지를 나타낸다 (비가 오면 Y=1, 오지 않으면 Y=0).
비가 온 날 구름이 끼었던 확률은 Pr(X=1|Y=1)=0.8,
비가 오지 않은 날 구름이 끼었던 확률은 Pr(X=1|Y=0)=0.1이고,
일반적으로 비가 올 확률 Pr(Y=1)=0.2 이다.
그렇다면 오늘 아침에 구름이 끼었을때, 비가 올 확률 Pr(Y=1|X=1) 은 몇인가 ?
분수 형태로 답하시오. 예시) 0.5 (X) , 1/2 (O)

추가로 추론할 수 있는 것, 일반적으로 비가 오지 않은 확률 Pr(Y=0) = 1 - 0.2 = 0.8

계산식은 파이썬 인터프리터로 바로 계산될 수 있도록 함

Pr(Y=1|X=1)
= P(Y=1)P(X=1|Y=1) / SUM(y') { P(Y=y')P(X) }
= P(Y=1)P(X=1|Y=1) / P(Y=1)P(X=1|Y=1) + P(Y=0)P(X=1|Y=0)
= 0.2*0.8 / (0.2*0.8 + 0.8*0.1)
= 0.16 / 0.24

# Quiz
유방암 검사 예제에서,
유방암에 걸렸을 때 (Y=Yes), 유방암 진단 (X=Positive)을 받을 확률 (Sensitivity of Mammogram) 은 Pr(X=Positive|Y=Yes)=0.9,
유방암에 걸리지 않았을 때 (Y=No), 유방암 진단 (X=Positive)을 받을 확률 (False Positive of Mammogram) 은 Pr(X=Positive|Y=No)=0.1,
아무런 조건 없이 유방암에 걸릴 확률 (Prior Probability) Pr(Y=Yes)=0.004 이다.

이 때, 유방암 진단을 받은 여성이 실제로 유방암에 걸렸을 확률 Pr(Y=Yes|X=Positive) 은 몇인가 ?
( 참고 : 반올림 가능 )

추가로 추론할 수 있는 것, 일반적으로 비가 오지 않은 확률 Pr(Y=No) = 1 - 0.004 = 0.996

Pr(Y=Yes|X=Positive)
= P(Y=Yes)P(X=Positive|Y=Yes) / SUM(y') { P(Y=y')P(X)) }
= P(Y=Yes)P(X=Positive|Y=Yes) / P(Y=Yes)P(X=Positive|Y=Yes) + P(Y=No)P(X=Positive|Y=NO)
= 0.004*0.9 / (0.004*0.9 + 0.996*0.1)
= 0.0036 / 0.1032
= 0.03488372093023256 = 0.035
```

- [사족] 확률 문제를 풀때 사용 방법
  - 표본공간이용-> 모든 조건이 같을때, 경우의 수가 많을때, ex) 주머니에 구슬 빨강공3,파란공7개가 있을때 5번째 사람이 빨간공을 뽑을 확률
  - 곱셈공식이용(조건부확률) : 조건이 다른 경우, 경우의 수가 적을때, ex) 제주도에 사는 남성의 비율

### 나이브 베이즈(Naive Bayes) classifier

- Query Y --> Observation X : query(알려고 하는것) Y 는 observation(관찰) X 에 확률적으로 영향을 준다.
- 숫자 인식에서 각각의 8\*8 특징들로 표현되는 픽셀마다 0 ~ 9(클래스) 에서의 사전확률(prior probability) 확률과 likelihood(우도)를 알고 있을때 모든(0 ~ 9) 클래스의 사후확률(posterior probability, Class Probability 라도 함)를 구할 수 있고 이중 가장 높은 값을 선택하여 클래스를 인식/분류(classification)한다.
  - likelihood(우도) : 각각의 class 가 주어졌을때 feature 값들이 나올 확률 값
    - 숫자 3의 경우 (0,0,1,1,1,0,0,0... )로 feature 가 있는데
    - 3에서 나올 확률을 높다 -> likelihood 가 높다.
    - 2에서 나올 확률은 낮다 -> likelihood 가 낮다
  - 64(8\*8)개 -> 조건부 확률 테이블 CBT(Conditional Probability Table) -> likelihood
  - 맨처음에 사전확률은 모든(0~9) 클래스가 동등하게 0.1로 확률로 설정

```text
# 특징 F 0,0 ... n,n 주어졌을때 Y(0~9 각 클래스)의 사후확률은
# 사전확률P(Y) 와 likelihood ㅠP(Fi,j|Y)로 계산할 수 있다.ㅠ(파이, 수열곱)
P(Y|F ... Fn,n) = P(Y)ㅠP(Fi,j|Y)
```

- overfitting : training data 에 너무 fitting 되어 실제 데이터에서는 인식이 잘 안되는 것

  - likelihood 가 확률적으로 (극단적인경우)0 나오면 안되기 때문에 lapalce smoothing 기법(실제 관찰값보다 +1)으로 해결
  - P라플라스(x) = c(x) + 1 / sum(x) { c(x) + 1} = c(x) + 1 / N + |X|

  ```text
  Pml(X) -> ml(maximum likelihood) 0.001 일때 Plap(X) -> lap(laplace smoothing) 을 통해 전체적으로 1 더해준다.
  ```

## 2주차 - SVM(Support Vector Machines)

### 기본개념

- svm 은 linear classifier 방법으로 특정 데이터를 기반으로 클래스를 구분하고 마진을 최대로 하는 구분선(hyperplane)을 찾는 알고리즘이다.
  - margin : 데이터를 구분할 수 있는 라인(hyperplane)이 한개가 있을때 라인과 가장 가까운 데이터 포인터와 라인과의 거리
    - 최대 마진(거리)을 결정하는 데이터 벡터들을 support vector 라고 부른다.
  - dichotomy(이분법) : a,b,c 3개의 클래스가 있을때 2개의 집합으로 나눠주는것
    - {0} {a,b,c} or {a} {b,c} or {a,b} {c} ... 최대 8개
  - shattering(산산히부수는) : classifier 가 dichotomy 모든 경우(위 예에서 8개)를 표현할 수 있는가를 의미
  - VC(Vapnik–Chervonenkis) dimension : shattering 할 수 있는 max num of data points, classifier 가 얼마나 복잡한 데이터를 구분할 수 있는지를 나타내는 수치
    - 2D(2차원)에서는 linear classifier VC dimension = 2 + 1 = 3 이된다, n차원에서 linear classifier 의 vc dimension 은 n + 1 이 된다.
    - vc dimension 이 높으면 (전체 에러가 높아) 안좋다.
  - svm maximize margin 을 높이는것 => shattering dataset 낮추는것 => vc dimension 를 낮추는것 => 에러를 줄이는것

### 최대 마진 분류기(maximum margin classifier)

- hyperplane 과 마진

```text
# w 가 hyperplane(초평면, n차원에서 n-1 로 표현되는 subspace) 을 정한다.
# w : weight parameter vector(matrx)
# x : input vector(matrix), 공간상에 표현되는 데이터들
# b : 상수
hyperplane 정의 -> w(transpose) 내적곱 x + b = 0 으로 표현되는 선 또는 평면
transpose(전치행렬, 열과행을 바꿔준다)하는 이유는 w,x 는 다음과같이 세로로된 1열 형렬로 표현되고
w = {1,   x = {1,
     2}        2
행렬을 곱하기 위해 w transpose 한다
w = {1,2}   x = {1,
                 2

2차원 벡터(그래프)에서 x1 = 1, x2 = 2 일때 x1 - x2 + 1 = 0 가 되고
hyperplane 정의를 이용하면 w1*(x1=1) + w2*(x2=2) + b = 0
w1 = 1, w2 = -1, b = 1
w1 = 2, w2 = -2, b = 2 ... 등이 될 수 있다.

다음 제약조건(constraint)를 이용해 최적화 문제를 편하게 풀 수 있다.(마진 구할때 분자로 사용하게됨)
| w(transpose) * Xn + b | = 1
```

- 마진 최대화

```text
 x1-x2 벡터는 w vector 와 직교(orthogonal)이고  1 / ||w|| (normed space, 길이 일반화) 로 hyperplane 과의 거리가 마진이 된다.
# ||w|| 예제
w=(3,4) 일때 ||w|| = root(3**2 + 4**2) = 5.0 가 된다.
# python
import math
math.sqrt(3**2 + 4**2)

# 최대 마진 찾기
# 제약조건 : ||w||(거리)는 데이터 벡터들 중 hyperplane 과 가장 가까운 거리를 찾는다.
||w|| ====> min(i=1,2,..n) | w(transpose) Xi + b | = 1
# 마진 계산
max( 1 / ||w|| )
# 1 = > | w(transpose) * Xn + b | 로 표현되고
# 마진 최대화
max (| w(transpose) * Xn + b | / || w ||)

# Quiz
w=[1,−2,3,−1]⊤, b=2라 할 때 초평면 w⊤x+b=0과 x1=[3,1,2,4]⊤ 사이의 거리를 구하면?
( 소수점 둘째 자리 이상 계산하시오 )
거리 d = |w1*x1+w2*x2 .. +wn*xn + b| / root(w1^2+w2^2+...+wn^2)
math.fabs((1*3)+(-2*1)+(3*2)+(-1*4) + 2) / math.sqrt((1**2)+((-2)**2)+(3**2)+((-1)**2)) = 1.2909944487358056 = 1.290
```

### 듀얼 문제와 서포트벡터(Larange Dual and Support Vector)

- Larange(라그랑주, L) : 제약이 있는 최적화 문제 --> 최적화하려 하는 값에 형식적인 라그랑주 승수항을 더해 --> 제약이 없는 문제로 변경
- svm 의 최적회 식이 여러개가(수식은 별도 참고) 있고 이중 듀얼 문제(형식)으로 풀면 느슨한(slack) 변수는 사라지는 효과가 있다.
- svm 최적화의 듀얼 문제를 풀었을때 AlphaN >= 0 이고, 대부분 0의 값을 가진다.
- slack 값 yn(w(transpose)Xn + b) - 1 = 0 이 되는점 Xn 들을 support vector 라 부른다.
- 학습된 svm 이용해 새로운 점 x 에 대한 예측을 수행할때, support vector 가 아닌 점들은 계산에서 제외된다.(slack)
- svm 에서는 전체 데이터를 다 보지 않고 support vector 만 보고 이들의 내적곱으로 y(답)을 구할 수 있다.

### 커널 서포트 벡터 머신(Kernel SVM)

- svm 은 linear classifier 로 많이 쓰지만 linear 하지 않는 데이터들에 대해서도 커널(kernel : 현재 차원에서 linear 하게 구별할 수 없는 경우 차원을 높여 높은 차원에서 hpyerplane 을 만들어 구별)이라는 것을 사용해 잘 분류 할 수 있다.
- 차원을 너무 높이면 컴퓨팅 코스트가 너무 많이 들어 불가능할 수 있다.
- 아주 큰 차원이라고 할지라도 실제 support vector 의 개수는 차원에 비해 훨씬 적을 수 있다.
- kernel trick : original low dimension space 에서 어렵지 않게 구할 수 있다. 실제 높은 차원에서 컴퓨팅을 해야한다고 하지만 실제 그렇게 높지 않는 차원에서 컴퓨팅하면 된다.
- low dimension 에서 linear 하게 separation 되지 않았는데, 차원이 infinite 까지 갈 수 있는 kernel trick 을 써서 nonlinearyity 를 얻을 수 있다.
- 커널 종류 : Gaussian Kernel, RBF(Radial Basis Function) Kernel, Polynomial Kernel 등

## 3주차 - 결정 트리(Decision Trees)

### 결정 트리 개념

- 결정 트리는
  - 데이터들이 linear 하게 분류 할수 없는 경우에 여러개의 룰을 가진 classifier, tree 형식으로 조건에 해당하는 leaf 노드를 선택해 나간다.
  - linear serparation 보다 복잡한 function 으로 데이터를 분류하고 싶을때 많이 사용
  - 커널 방법이 좋지 않은 경우 결정트리를 이용할 수 있다.
  - 사람이 이해하기 편한다.
  - 앙상블 러닝(ensemble learning, 여러개의 결정트리를 조합) - random forest 가 대표적
- 예) 구매자가 n 번째까지 구매한 케이스 데이터를 학습하여 결정트리로 만들고 n+1 번째의 구매를 어디서 해야하는지 판단
- leaf node 들이 pure(더이상 나눌 수 없는 상태)가 되어야 한다.
- 실제 데이터에서는 pure node 를 만들기 위해 아주 많은 질문을 던져 overfitting 될 수 있다.

### ID3 알고리즘(Iterative Dichotomiser 3 Algorithm)

- 결정트리를 만드는 ID3 알고리즘 과정
  - 현재 노드를 나눌 수 있는 A: 최적의 속성(Best Attribute)을 찾는다.
  - A 를 현재 노드의 decision attribute 로 적용한다.
  - A 의 가능한 값들에 대해 현재 노드의 child 노드들을 각각 하나씩 만든다.
  - 현 노드에 들어 있는 training example 들을 A 값에 따라 child node 에 넣는다.
  - 모든 child node 에 대해, 그 노드가 "pure" 하면 멈추고, 그렇지 않으면 그 child node 에 대해 처음부터 다시 반복한다.
- entropy(복잡도) : 좋은 attribute 를 정하기 위해 계산
  - H(S) = -(P1 Log2 P1) \* -(P2 Log2 P2) , P1 or P2 : 전체 S 개중 class A or B 의 확률, An / S or Bn / S
    ```text
    # 노드에 대한 entropy 구하는 예시
    전체 데이터 (9, 5) - class a 에 속하는 경우 9개, class b 에 속하는 겨웅 5개, 전체 15개
    -(9/14 * log2 9/14) - (5/14 * log2 * 5/14)
    # python
    import math
    -(9.0/14.0 * math.log(9.0/14.0, 2)) -(5.0/14.0 * math.log(5.0/14.0, 2)) = 0.9402859586706309
    H = 0.94
    ```
  - 노드 마다 entropy 를 구할 수 있다. pure 노드는 H(entpropy) = 0
  - best attribute 를 구한다고했을때, decision 노드들에 대해서, attribute를 정하면 엔트로피가 감소하고, 엔트로피를 가장 많이 감소하게 할 수 있을 꺼라는 것을 염두해 두고 고르면 best attribute 가 나온다.(entropy 를 감소하는 쪽으로 가는 attribute 가 best 이다.)
- information gain(정보획득) : entropy 를 감소하기 위해 계산
  - Gain(S,A) = A 로 나눔으로써 얻게되는 entropy 감소, S 는 전체 데이터 사이즈
  - Gain(S,A) = H(S) - Sum(v){ |Sv| / |S| } Entropy(Sv)

```text
# Quiz
아래와 같이 Attribute A를 이용해 데이터를 Child node로 쪼갤 때 Information Gain을 계산하면?
괄호 안의 숫자 (a,b)는 각각 (class 1에 속하는 데이터의 수, class 2에 속하는 데이터의 수)를 뜻한다.
힌트) 소수점 아래 셋째 자리 이상 계산하시오.
전체데이터(10,20)
Attribute A 로 구분하였을때
Attribute A(3,14) , Attribute B(7,6)

풀이)
전체데이터 엔트로피 = -(10.0/30.0 * math.log(10.0/30.0, 2)) -(20.0/30.0 * math.log(20.0/30.0, 2)) = 0.9182958340544896
Attribute A 엔트로피 = -(3.0/17.0 * math.log(3.0/17.0, 2)) -(14.0/17.0 * math.log(14.0/17.0, 2)) = 0.672294817075638
Attribute B 엔트로피 = -(7.0/13.0 * math.log(7.0/13.0, 2)) -(6.0/13.0 * math.log(6.0/13.0, 2)) = 0.9957274520849256
Information Gain = 0.9182958340544896 - ( (17.0/30.0)*0.672294817075638 + (13.0/30.0)*0.9957274520849256) = 0.1058468751414936
```

### 랜덤 포레스트(Random Forest)

- 결정트리의 가장 큰 단점 중 하나는 overfitting 이다.
- 실제 데이터를 ID3 로 pure 노드까지 가게할 경우 node 개수가 많아 지면서 overfitting 이 발생할 수 있다.
- overfitting 을 막는 방법

  - 통계적으로 무의미한 노드들은 나누지(split) 않는다. ex) 1000 데이터 대해서 95 : 5 정도로 나누는 경우
  - 결정트리가 만들어진 상태에서 Validation Data 의 정확도(accuracy) 를 기준으로 sub-tree 를 제거(prune)한다. prune 의미는 child-node 는 제거하고 parent node 는 pure 하지 않더라도 그대로 놔둔다.

- random forest

  - 결정트리 하나만 쓰면 prediction accuracy 가 좋기지 않기 때문에, bagging 과 attribute 둘다 random 하게 두는 random forest 방법을 사용한다.
  - bagging(bootstrap aggregating) tree : training data 에서 랜덤하게 k개를 랜덤하게 고른다. -> subset (training) data 로 ID3 등의 알고리즘으로 결정트리를 생성한다. 이과정을 B번 반복하여 B 개의 결정트리르 만든다. classification 시 B 개의 트리들 사용해서 majority vote(다수의 트리가 선택한쪽, 다수결)
    - decreases variance while bias stays same : overfitting(bias 의미) 이 늘어나지 않으면서 variance 를 줄이는 것
  - attribute 무작위 선택 : bagging 과정의 subset data 에 대해 모든 attriibute 를 사용해서 tree 를 만들경우, 특정 attribute 가 압도적으로 많이 나와(항상 결정트리에 포함되) 모든 결정트리에 영향을 주는 것을 막기위해 랜덤하게 하게 attribute 를 선택한다.

- 결정트리와 random foreset 정리
  - 결정트리는 svm, nerual network 등의 다른 기계학습과 달리 사람이 이해하기 쉬운 classifier 다.
  - 결정트리는 svm 과 같이 linear 가 아닌 non-linear 바운더리 형태로 나타낼 수 있다.
  - O(height of tree) 의 시간복잡도로 비교적 빠른 prediction 이 가능하다.
  - random forest 등을 사용할 경우 prediction accuracy 을 높일 수 있다.

## 4주차 - 신경망 모델(Neural Networks)

### 인공뉴런(Artificial Neuron)

- 인공 신경망은 60년대부터 인공지능 분야에서 많이 연구었고, 최근 DeepLearning 의 기반기술로 주목 받고 있다.
- 안공 신경망에서 하나의 작은 단위가 인공뉴런이다.(인간 뇌의 뉴런을 모델로 한것)
- 인공 뉴런은 x(x1..n 벡터, input)을 입력과 b(bias) 를 입력으로 받아 g(activation function)를 거쳐 활성화 여부를 출력한다.
  - inptut activation 또는 pre-activation : input x와 b를 합하였을때까지의 상태로 activation function 계산하기전을 말한다.
  - activation function : output 출력에 사용
  - h(x) = g(a(x)) = g(b + sum(i) WiXi)
- 활성화 함수(activation function)
  - linear : g(a) = a 로 입력에 따라 출력이 결정되는 형태로 거의 사용되지 않는다.
  - sigmoid(사전적의미:S자형의) : g(a) = sigm(a) = 1 / (1+exp(-a)) 로 0~1사의 값이 출력으로 가지면(항상 양수), S 자 모양의 그래프
  - tanh(hyperbolic tangent) : g(a) = tanh(a) = (exp(2a)-1 / exp(2a)+1) sigmoid 와 비슷하지만 -1~1 시아로 음수값도 가진다.
  - reclin(rectified(사전적의미:수정된,정류된) linear) : g(a) = recline(a) = max(0,a) 0보작 작을때 무조건 0, 0보다 크면 a 가 출력된다. sparse(뉴런 하나의 output 값이 0이 아닌 경우가 많이 생겨 부족하다. 부족하다는것은 뉴런 네트워크 전체를 계산하는데 훨씬 쉽고 간단해진다.)하여 가장 많이 쓰인다.
- sigmoid 활성화 함수를 통해 0~1사의 값을 주게 된다고 했을대, 이 값을 확률로 볼 수 x가 주었을때 y가 될 확률로 볼수 있고, 이것은 logistic regression(로지시틱 회귀: 사건의 발생 가능성을 예측하는 통계기법) classifier 랑 똑같이 되는것이다. binary classifier 로 활용된다.

### 다층 뉴럴 네트워크(Multilayer Neural Network)

- 다수의 뉴런을 연결하여 non-linear 문제를 해결해보자
- 여러개의 뉴런이 hidden layer 를 이루고, hidden layer neuron 들로부터 output neuron 이 만들어진다.
- output layer activation function 으로는 hidden layer activation function 과는 다른 softmax 등을 사용한다.
- hidden layer activation function h(x) = g(a(x)) 에서 activation function g(-) 은 sigmoid, tanh, recline 등이 될 수있다.
- single neuron 으로 표현이 힘든 xor(x1,x2) 를 표현할 수 있다.
- a(x) = b(1) + W(1)x : W 는 여러기의 뉴런들을 matrix 로 표현
- softmax 는 output layer activation function 으로 사용한다. 확률값으로 모든 출력 노트의 출력값이 1로 했을때의 각 노의 확률값을 표현
  - softmax(a) = [ { exp(a1) / sum(c)exp(ac) } ... { exp(ac) / sum(c)exp(ac) }]
- 각 hidden layer 는 single layer neural network 처럼 pre-activation 과 activation function 이 있다.
- training data {(xi,yi)} 로 부터 neural network 의 weight matrix W 들을 학습해야 한다.
- 학습된 neural network 에서 test data x 를 input layer 에 넣고 output layer 의 값을 계산함으로써 y(hat) 을 추정할 수 있다.

### 경험적 위험 최소화(Empirical Risk Minimization)

- training data 를 가장 잘 설명할 수 있는 가장 적합한 parameter 를 찾는게 인공신경망 training 이고 이를 해결하기 위한 대표적인 방법으로 risk minimization을 사용한다.
- empirical risk minimization 알고리즘(수식)은
  - 수식에서 1번 부분(l 부분) : loss function
    - l(loss function)은 f(모든 nerual network 의 모든 계산을 거처 나온 최종 output)과 정답과의 차이 구하는 함수
    - 주어진 training data 에서 정답을 가장 잘 맞출 수 있는 parameter 를 구하는것
    - 학습데이터와 다른 그 차이에 대한 패널티을 주는 부분
    - 우리가 최적화(optimization) 하고자 하는 실제 목적(objective)을 나타내는 부분이다.
  - 수식에서 2번 부분(omega 부분) : regularizer(overfitting 을 막기위해 패널티 주는것)
    - 최대한 간단한 모델이 되도록 하는 파라미터를 찾는 역할
    - 모델의 복잡도가 올라가면 overfitting 되어 이에 대한 패널티를 주는 부분
  - loss function 과 regularizer 의 합을 최소화 하는 최적화(optimization) 문제로 나타낼 수 있다.
- classification error optimization 을 위해서 -> gradient 계산하고 -> gradient 계산을 위해선 smooth 한 loss function 에러를 대체한다.
- stochastic gradient descent(SGD, 확률적 경사 하강법) : 뉴럴넷에서 가장 많이 쓰이는 최적화 방법
  - 초기 파라미터는 랜덤밸류로 시작
  - 조금씩 object function(loss function + regularization)을 최적화하는 방향으로 조금씩 업데이트
    - 편미분(partial derivative)을 구해서 반대 방향으로, 그 방향에서 alpha(learning rate)를 곱해서 그 만큼 이동한다.
    - 모든 training data 에 대해서 하나하나 계산
    - 이 과정을 n 번을 반복, n 도 실험적으로 해보면서 정한다.
- Gradient Descent 알고리즘을 사용할 경우, 미분 가능한 함수를 선호한다.

### 손실 함수(Loss Function)

- 정답을 알고 뉴럴넷이 출결과와 얼마나 일치하는가를 확률적으로 나타내는 것 손실함수의 기능이다.
- 입력값에 대해서 특정 class(c)에 대한 확률 추정값 f(x)c = p(y=c|x) 로 계산한다.
- 입력값 x의 true class가 y일 때, f(x)y를 최대화 하는 방향으로 학습이 되어야 하고, 이는 negative log likelihood −log⁡f(x)y를 최소화 함으로써 달성할 수 있다.
- 입력값 x에 대한 추정값 f(x)과 입력값의 true class y 사이의 손실 함수는 흔히 l(f(x),y)=−∑c1(y=c)log⁡f(x)c 로 정의된다.

### 은닉층 그래디언트(Hidden Layer Gradient)

- Loss function의 Hidden layer에 대한 gradient를 바로 계산하기는 복잡하므로 Chain rule을 이용해 단계적으로 계산한다.
  - Chain rule : qi 의 여러개를 더하거나 곱하면 p 를 구성하는 intermediate step 들에 대해 partial derivative 를 하고, 모든 qi 에 대해 summation 을 하면 구할 수 있다.
- Back propagation을 하기 위해서는 Forward propagation 계산이 선행되어야 한다.
- Back propagation 알고리즘을 이용해 파라미터에 대한 Loss function의 Gradient를 효율적으로 계산할 수 있고, 이를 이용해 Loss function을 줄이는 방향으로 파라미터를 최적화 시켜나가게 된다.

## 5주차 - 딥 러닝과 그 응용(Deep Learning & Application)

### 딥 러닝 소개(Introduction to Deep Learnging)

- 딥러닝의 역사
  - NN 의 20년간 암흑기가 있었는데, 캐나다 토론토 대학의 Geoff Hinton 교수가 2006년 reducing the dimensionality of data with nerual networks 라는 논문을 사인언스에 내게 된다. restricted boltzmann machines (RBM) 을 이용해 학습한다. 현재는 RBM 보다 좋은 알고리즘들을 사용한다.
  - 2009년 훨씬 큰 데이터와, 현실적인 데이터를 가지고 convolutional rbm 을 만들어서 한번더 관심을 받게 된다.
  - 2012년 ICML(머신러닝에서 가장 큰 학회) 에서 Google 과 스탠포드 Andrew Ng 가 논문을 발표하게 된다. 천만개의 이미지와 16천개의 코어와 3일동안 트레이닝을 하는등 엄청 큰 스케일의 데이터와 하드웨어로 사용하였다. 딥러닝의 잠재력은 높다.
- 여러개의 Levels of Abstraction 을 가진다. (Ex. Pixel - 직선 - 눈코입 - 얼굴 (in Face Recognition Example))
- 딥러닝은 feature extraction 하지 않고 딥 뉴럴 네트워크로 여러 레벨의 abstraction 을 뽑아주는게 가장 큰 힘이라고 할 수 있다.
  - Feature Extraction 에 대한 사전지식 없이, Deep Neural Network 이 자동으로 Levels of Abstraction 을 찾아주는 Representation Learning 이 가능하다.
- 딥러닝은 supervised learning, unsupervised learning 둘 다 할 수 있다.
- 딥러닝이 근본적으로 하는 것은 representation learning 이다.
  - represenetation learning : 이미지 데이터에서 픽셀 부터 사물 전체 레벨까지 여러개의 레벨이 될 수 있는 representation 들이 무엇이 있는지 그것을 자동으로 학습한다.
- Deep Learning 에서 쓰이는 모델로는 Restricted Boltzmann Machine (RBM), Autoencoder, Convolutional Neural Network (CNN), Recurrent Neural Network (RNN) 등이 있다.
  - 더 잘할 수 없을 정도로 좋은쪽 : 이미지인식, 음성인식
  - 아직 좀 미흡한 쪽: 자연어 처리, 기계번역

### 제한적 볼츠만 기계(Restricted Boltzmann Machine, RBM)

- RBM 은 unsupervised learning 을 할 수 있는 모델로 데이터의거 아주 커지는 상황에서 일일히 레이블링하여 정답셋을 만들 수 없기 때문에 unsupervised learning 이 중요해 졌다.
- 차원 감소, 분류, 선형 회구 분석, 특징값 학습등에 사용 가능한 알고리즘으로 Geoff Hinton 교수가 제안
- RBM 자체적으로 사용할 수 있지만 다른 디러닝 신경망의 학습을 돕기 위해서 쓰이기도 한다.
- RBM 은 입력층(visible layer) + 은닉층(hidden layer) 의 2 layers 로 구성된다.
  - 입력층노드와 은닉층 노드들은 모두 풀 연결되어 있지만 layer 안에서의 노드들끼는 연결되어 있지 않다. -> 확률적인 관계가 없다. -> 독립적이다.
    - 같은 layer 에서는 연결이 없어 '제한된' 볼츠만 머신 이름이 붙여짐
    - 입력 데이터를 은닉층으로 전달할지(1) 말지(0)를 확률적 결정(stochastic decision)
    - MNIST 필기인식의 경우 784개의 픽셀이 입력노드의 입력값이 된다.
  - Hidden Layer 와 Visible Layer 사이에 방향성이 없는 (Undirected) 관계를 가지는 Graphical Model 이다.
  - Contrastive Divergence 알고리즘 등으로 RBM 의 Inference 가 가능하고, Deep Neural Network 의 Weight Initialize 를 위한 Pre-Training(전처리, 선행학습) 에 쓰일 수 있다.
  - inference : 확률값을 높이는 파라미터를 알아보는것
- 2006년 hinton 교수의 논문 에 소갠된 Contrastive Divergence(CD) (대조 분기?)는
  - RBM 을 하나의 유닛을 가지고 있는 딥러닝응 쉽게 할 수 있는 알고리즘이다.
  - RBM 에서 Stochastic Gradient Descent 알고리즘 대신 사용
  - CD 로 굉장히 쉽고 빠르게 inference 할 수 있다.
- Contrastive Divergence(CD) 의 아이디어
  - 하나의 포인트 X estimate 를 expectation 으로 보자.
  - gibbs sample (chain 으로 볼수 있다.) 을 k 개의 적은 숫자로 iteration 한다.
    - gibbs sample: 두개 이상의 확률 변수의 결합 확률 분포로부터 일련의 표본을 생성하는 확률적 알고리즘으로, 결합 확률 분포나 그에 관련된 확률 계산을 근사하기 위해 사용
    - gibbs sample 을 쓴다는 것은 sample iteration 하나를 거칠때 마다 parameter 를 업데이틑 해준다는것, parameter 는 connection weight W, Bias Vectors bj,ck 들을 업데이트 해간다.
  - chain 시작시 랜덤하지 하지 않고 input data 에서 그냥 하나를 뽑아 시작한다.
  - k=1 일때어 어느정도 좋은 결과를 보인다.
- RBM 예시
  - MINIST 필기 숫자데이터 -> RBM 으로 pretraining filter 적용한듯(특징이 있어야 하는 곳은 밝게, 없어야 할곳은 어둡게 표현)

### 오토인코더(Autoencoder)

- 오토인코더는 RBM 과 같은 unsupervised learning 모델이고, pretraing 을 하는 단계에서 많이 쓰임
- input layer -> hidden layer -> output layer(input layer 의 노드 개수와 같다.) 형태로 input 값을 output 에서 reconstrunction 하는 것이 목적이다.
  - input -> hidden layer : encoder 라 부르고 sigmoid 를 사용
  - hidden layer -> output layer : decoder 라 부르고 sigmoid 를 사용
  - under complete representation(compression) : hidden layer node(dimension) 개수가 input node(dimension) 보다 작은 경우
    - dimension reducntion 목적으로도 쓰임 PCA(Principle Component Analysis) 에 대응
    - training data 와 많이 다른 데이터가 들어왔을경우 compression 이 전혀 역할을 하지 않는 제한이 있다.
  - overcomplete : hidden layer node 개수가 input node 보다 큰 경우
    - hidden layer 의미있는 structure 를 발견하지 못할 수도 있는 제한이 있어 좋은 모델이 아니다.
    - overcomplete 를 개선하기 위해 노이즈가 추가된 데이터를 노이즈가 없는 원래 데이터로 복원할 수 있는 유의미한 Feature들을 찾아내는 denoising autoencoder 를 사용, 음성인식, 이미지인식등 노이즈가 많은 input 데이터 대해서 pre-training 으로서 사용한다.

### 딥 뉴럴 네트워크 정규화(Deep Neural Network Regularization)

- 딥러닝 = representation learning = distributed(첫번재 hidden layer 픽셀 특징, 두번재 hidden layer 눈,코입....특징, 등 layer 를 쌓아 올려) representation
- multi layer feed forward nerual net 이 표현할 수 있는 function 은 complexity 가 높은 function 이다.
- 2가지 문제점
  - underfitting : parameter optimization 잘 못한다. 최적화 의미는 backpropagation 에서 layer 마다 gradient 를 구하고 그 뒤로 가는것, stochastic gradidnet descent 를 통한 최적화. hyperbolic tangent, sigmoid 등에서 0에 가까울때는 slope(경사, gradient)가 있지만 0에서 멀어질수록 slope 가 거의 0에 가까워진다. gradient이 거의 0이 되면 다음 iteration 에서 parameter update 할때 잘 되지 않는다. iteration 마다 처음 시작했던 weight 보다 좋은쪽으로 움직여야 하는데 움직이지 못한다는것으로 이를 vanishing gradient problem 이라고 한다.
  - overfitting : training data 에 너무 fitting 되서 실제 데이터에 prediction 할수있는 generalization power 가 떨어진다. 학습할 수 있는 함수의 범위가 매우 크기 때문에 overfitting 이 잘 일어난다.
- overfitting 방지를 위해서 parameter 들의 값에 패너티를 주면서 에방하는 regularization 을 사용한다.
- 정규화(regularization, 딥넷의 overfitting 을 줄이기 위한것) 2 가지 방법
  - unsupervised pre-training : 다음과 과정을 거치면서 feature 조합을 잘 찾아낸다. combination of combination of ...
    - first layer : training data input 에서만 잘 나오는 hidden unit 용 feature 를 찾는다.
    - second layer : first layer output 을 입력으로 받아 hidden unit 들의 combination 을 찾는다.
    - third layer : second layer output 을 입력을 받아 또 hidden unit 들의 feature 를 또 combination 한다.
    - Unsupervised pre-training을 할 때, 첫 번째 Layer의 학습이 끝나면 첫 번째 Layer의 weight 값을 고정시킨 채 두 번째 Layer의 학습을 진행하며, 같은 방식으로 여러 층에 걸쳐 학습된 Weight를 Supervised learning의 파라미터 초기값으로 사용하면 Over-fitting이 방지되는 효과가 있다.
    - 마지막 output layer 를 하다 더 얹는데 이는 정답을 가지고 있는 supervised learning 이 된다.
    - 그리고 backpropagation 을 통해 hidden layer 의 weight 들을 업데이트를 한하는데 이를 find tuning 한다고 얘기한다.
  - dropout : hidden layer 의 hidden unit 을 0.5의 확률로 0으로 한다.
    - 모든 hidden unit layer 가 출력되면 비슷한 효과를 내는 feature 들을 표현하지 않고 다른것을 해버리는 net weight 들의 co-adaptation(동조화 현상)이 발생하는데 몇몇 hidden unit 을 없앰(drop)으로써 hidden unit 이 좀더 자기가 표현할 수 있도록 한다.

## 6주차 - 강좌 종합 정리

### 콘볼루션 신경망(Convolutional Neural Network)

- 컴퓨터비전 분야에서 딥러닝을 사용하는데
  - object regcogintion(사물인식)에 많이 사용한다. caltech 101 dataset(101개의 사물 분류) 데이터를 많이 사용한다.
  - 이미지의 경우 dimension(MxN 픽셀, 픽셀당 RGB 컬러 정보)이 크다.
  - 이미지의 경우 togoploy(위상, 지형) 패턴을 가지고 있다. 예를 들어 edge 등의 특성, 꽃의 경우 비슷한 색깔이 많이 분포된다.
  - rotation, illumination, scaling 등의 invariance(불변) 를 지켜줘야 한다.
  - 이런 문제 특성을 해결하기 위해 CNN(Convolutional Neural Network) 방법을 인식하며, 다음 3가지 아이디어에서 내포되어 있다.
    - local connectivity : fully connected hidden layer 는 관리되지 않는 너무 많은 파라미터를 가지고 있고 복잡하기 때문에 local connected hidden layer 를 보도록 한다. parameter 의 수를 줄여준다.
      - feature-map 이 가지고 있는 필터 효과를 이용해 이미지에 대해서 계산하여 어떤 패턴을 찾아 내는 방법을 convoluvtion 이라고 하는데, discrete(분리된) convolution (사실signal processing 에서 하나의 input signal 있을때 패턴을 감지하기 위해 사용)는 이미지 데이터에서 kernel(이미지 필터 값은 녀석)이 가지고 있는 패턴을 input data 에서 찾아보기 위해 input 의 필터크리만큰 shift 하면서 곱해주는 것을 말한다. 이미지의 크기가 5x5이고 커널의 크기가 3x3이라면 콘볼루션 결과는 3x3 행렬이 된다.
      - convolution 후에 non-linear 한 sigmoid function, hyperbolic tangent 등을 계산하여 찾고자 하는 패턴와의 차이을 수치상을 확인할 수 있다. convolution 결과값이 크다는 것은, 입력 이미지의 해당 위치가 커널과 비슷한 패턴을 가지고 있음을 뜻한다.
      - 이미지의 바깥쪽에 있는 곳을 0으로 채워주는 zero padding 을 통해 바깥쪽의 패턴도 잡을 수 있도록 한다.
    - parameter sharing : N 개의 feaature-map 이 있고 feature-Map(w1, w2,,,. wn)일때, 각 feature-map 의 w1 은 이미지의 한 부분에 특징 값을 가진다. local connectivity 로 파라미터를 줄여줬지만 parameter sharing 을 통해 feature-map 의 숫자만큼 parameter 수를 줄여준다. 그리고 receptive-filed(수용영역, 외부자극이 있을때 전체에 영향을 주는것이 아니라 특정영역에만 영향은 준다는 의미로 이미지에서 특정 필셀은 인접한 일부 픽셀들하고만 밀접하게 연과되어 있고 거리가 멀수록 영향은 감소된다) 이미지의 모든 position 에 대해서 똑같은 feature 들을 extraction 하고 있다.
    - pooling / subsample hidden unit : convolution 결과에서 3x3, 4x4 크기의 patch(neighborhood 라고도 함, 일종의 필터)들을 적용하여 max 값만 취한다. 3x3 의 경우 max 1개만 취하고 나머지 8개는 버린다.(max-pooling).
      - input data 이미지가 클때, hidden layer 가 클때 pooling 을 통해 이미지 사이즈를 줄이거나 hidden unit 개수를 줄이다.
      - local translation : max-pooling 을 통해 특정부분(local)값이 다른쪽을 이동(번역translation)되는 현상, Pooling을 통해 Local translation에 대한 Invariance를 가질 수 있다.
  - CNN 흐름 : input -> layer1 (convolution) -> max-pooling -> layer2(convolution) -> max-pooling .... -> max-pooling -> output
  - max-pooling gradient : 0 except for delta xij+p`,k+q` l = delta yijk l
  - average-pooling gradient : { umsample(delta y l) } / m\*m
  - jarret 2009년 논문에 rectification(개정, 수정) 를 사용 : 모든 layer 에 대해서 값이 다 나오는데 그값에 대해서 absolute value 를 쓰운다. convolution의 특징은 잡는단 것은 결국 edge 를 찾는것으로 흰색에서 검은색으로, 검은색에서 흰색으로 변하는 구간인데, rectification 을 적용하여 흰색->검은색으로 가던 검은색->흰색으로 가던 구분없이 모두 edge 로 하겠다는 의미다.
    - contrast nomalization : 비슷한 neighbor local한 부분에 대해서 contrast 에 대한 평균값을 빼고 standard deviation 으로 나눈다. 모든 layer 에서 contrast-normalization 을 하여 비슷한 부분은 무시되고 정말 다른 부분만 잡아내겠다는 의미
    - input image -> convolution -> rectification -> contrast normalization -> pooling/subsample ...
    - rectification, contrast normalization 등을 적용하니 인식률이 좋아지고, 2번 적용하니 더 좋아지더라.
    - 그리고 random filters(kernel)를 적용하더라도 어느정도 패턴을 잡아내기는 한다.

### 신경망 언어 모델(Neural Network Language Model)

- 자연어 처리(Natural Language Processing, NLP)는 책, 신문기사 등의 문서 데이터에서 의미를 추출하기 위한 분석을 하는 학문으로 에도 머신 러닝을 이용할 수 있다.
- word(단어) 단위로 분석하며 다음의 2과정을 거친다.
  - tokenization : 단어 추출하는 과정
  - lemmatization(혹은 normalization) : 대문자를 소문자로 만드다던지, 7 같은 숫자 자체는 number 로 고친다던지등의 표준형태로 만드는 과정
- corpus(문서의집합)에서 단어들을 모두 추출할 수 있고 이것을 vocabulary 만든다고 한다. vocabulary 를 만들때 크게 의미 없는 단어(예를 들어 the) 너무 많이 나오는 단어(예를 들어 the)는 빼는 등의 작업을 하고 각각에 단어에 unique 한 id를 부여한다. oov(out of vocabulary) vocabbulary 에 없는 경우도 구분
  - one-hot encoding : vocabulary dimension 크기의 벡터를 만들고 모두 0 으로 하고 vocabulary 의 특정 단어가가 가진 위치(position)에 대해서만 1로 한다. 많이 쓰이지만 dimension 의 크기가 너무 커진다는 단점이 있다.
  - continuous word representation : one-hot encoding 이 단점을 보완하기 위해 나온 방법, 모든 dimension 에대해서 0 아닌 value 를 가질 수 있도록 한다. vector(dimension) 값들이 서로 비슷한 단어들은 서로 비슷하다고 할 수 있도록 하는것이 continuous word representation가 추구하는 목표이다.
- Language Model : 문서에서 단어들 (Sequence of Words)이 나타날 분포에 대한 확률적 모델이다. 영어, 한국어등 하나의 언어에 쓰이는 단어들의 distribution 을 표현한것으로 많은 텍스트가 주어졌을때 텍스트에서 단어들이 어떤 순서로 나오는지를 보고 모델링하면 영어에서는 어떤 단어들이 어떤 단어들 다음에 나온다는것을 확률적으로 표현 할 수 있다.
  - n-gram model : 지금까지 가장 많이 쓰이는 language model. n-gram 모델에서는 (n-1) 개의 순차적인 단어들 후에 나올 n 번째 단어에 대한 확률을 나타내는 모델이다. n=1 이면 unigram, n=2 이면 bigram, n=3 이면 trigram(음성인식, 자동기계번역에서 많이 쓰임)
    - 학습 과정에서 한 번도 보지 못했던 n-gram 은 확률 모델이 잘 설명할 수 없기 때문에 Data Sparsity(희박함) 문제가 있다. trigram 에 없는 모델은 bigram 과 unigram 을 조합해서 Data Sparsity 문제를 부분적으로 해결할 수 있지만 근본적으로 해결할 수 없어 Nerual Network 를 활용하기 시작했다.
  - Neural Network Language Model : continuous Word Representation 을 input 으로 하고 output 은 전체 문장의 확률 혹은 전체문장에 context 가 주어졌을때 그 단어 하나가 나올 조거부확률(conditional probability)이 된다.
    - continuous Word Representation 을 Input 으로 하고, 각각의 단어가 나올 확률을 Output 으로 하는 Neural Network 구조로 표현할 수 있다.
    - "cat" 과 "dog" 라는 단어를 continuous Word Representation 으로 표현했을 때, 비슷한 Vector 값을 가지도록 Neural Network 를 학습함으로서 Data Sparsity 문제를 다룰 수 있다.
    - 학습된 Language Model 로부터 학습되지 않은 새로운 문장에 대한 확률 값을 기준으로 Language Model 의 성능을 측정할 수 있다. (ex. Perplexity(곤혹,혼론,당혹) : 학습한 language 모델에서 확률듈을 계산했을때 새로운 문장에 대해서 얼마나 높게 주는가는 확률이고 이 확율을 반대 개념을 Perplexity 라고 하고 perplexity 는 낮을 수록 좋다.)

### 강좌 종합 정리(Course Summary)

- 딥러닝 도입 사례
  - netflix 개인별 추천에 머신러닝을 도입하고 있다. personalized rating prediction(내가 좋아하는 영화 별주기) -> personalized ranking(영화들 랭킹) -> personalized page generation(나에 맞는 첫화면 생성)
  - ibm watson service 로 health care 분야에 활용하고 있다. 환자의 피부 사진을 보고 skin cancer(피부암)인지를 detection 을 이미지 딥러닝을 활용한다.
