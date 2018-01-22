# K-MOOC '인공지능 및 기계학습'

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
- 숫자 인식에서 각각의 8*8 특징들로 표현되는 픽셀마다 0 ~ 9(클래스) 에서의 사전확률(prior probability) 확률과 likelihood(우도)를 알고 있을때 모든(0 ~ 9) 클래스의 사후확률(posterior probability, Class Probability 라도 함)를 구할 수 있고 이중 가장 높은 값을 선택하여 클래스를 인식/분류(classification)한다.
  - likelihood(우도) : 각각의 class 가 주어졌을때 feature 값들이 나올 확률 값
    - 숫자 3의 경우 (0,0,1,1,1,0,0,0... )로 feature 가 있는데
    - 3에서 나올 확률을 높다 -> likelihood 가 높다.
    - 2에서 나올 확률은 낮다 -> likelihood 가 낮다
  - 64(8*8)개 -> 조건부 확률 테이블 CBT(Conditional Probability Table) -> likelihood
  - 맨처음에 사전확률은 모든(0~9) 클래스가 동등하게 0.1로 확률로 설정

```text
# 특징 F 0,0 ... n,n 주어졌을때 Y(0~9 각 클래스)의 사후확률은
# 사전확률P(Y) 와 likelihood ㅠP(Fi,j|Y)로 계산할 수 있다.ㅠ(파이, 수열곱)
P(Y|F ... Fn,n) = P(Y)ㅠP(Fi,j|Y)
```

- overfitting : trainning data 에 너무 fitting 되어 실제 데이터에서는 인식이 잘 안되는 것
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

다음 제약조건(contraint)를 이용해 최적화 문제를 편하게 풀 수 있다.(마진 구할때 분자로 사용하게됨)
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
- low dimension 에서 linear 하게 seperation 되지 않았는데, 차원이 infinite 까지 갈 수 있는 kernel trick 을 써서 nonlinearyity 를 얻을 수 있다.
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
  - H(S) = -(P1 Log2 P1) * -(P2 Log2 P2) , P1 or P2 : 전체 S 개중 class A or B 의 확률, An / S or Bn / S
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
  - bagging(bootstrap aggregating) tree : trainning data 에서 랜덤하게 k개를 랜덤하게 고른다. -> subset (training) data 로 ID3 등의 알고리즘으로 결정트리를 생성한다. 이과정을 B번 반복하여 B 개의 결정트리르 만든다. classification 시 B 개의 트리들 사용해서 majority vote(다수의 트리가 선택한쪽, 다수결)
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
  - activation function :  output 출력에 사용
  - h(x) = g(a(x)) = g(b + sum(i) WiXi)
- 활성화 함수(activation function)
  - linear : g(a) = a 로 입력에 따라 출력이 결정되는 형태로 거의 사용되지 않는다.
  - sigmoid(사전적의미:S자형의) : g(a) = sigm(a) = 1 / (1+exp(-a)) 로  0~1사의 값이 출력으로 가지면(항상 양수), S 자 모양의 그래프
  - tanh(hyperbolic tangent) : g(a) = tanh(a) = (exp(2a)-1 / exp(2a)+1) sigmoid 와 비슷하지만 -1~1 시아로 음수값도 가진다.
  - reclin(rectified(사전적의미:수정된,정류된) linear) : g(a) = recline(a) = max(0,a) 0보작 작을때 무조건 0, 0보다 크면 a 가 출력된다. sparse(뉴런 하나의 output 값이 0이 아닌 경우가 많이 생겨 부족하다. 부족하다는것은 뉴런 네트워크 전체를 계산하는데 훨씬 쉽고 간단해진다.)하여 가장 많이 쓰인다.
- sigmoid 활성화 함수를 통해 0~1사의 값을 주게 된다고 했을대, 이 값을 확률로 볼 수 x가 주었을때 y가 될 확률로 볼수 있고, 이것은 logistic regression(로지시틱 회귀: 사건의 발생 가능성을 예측하는 통계기법) classifier 랑 똑같이 되는것이다. binary classifier 로 활용된다.

### 다층 뉴럴 네트워크(Multilayer Neural Network)

- 다수의 뉴런을 연결하여 non-linear 문제를 해결해보자
- 여러개의 뉴런이 hidden layer 를 이루고, hidden layer neuron 들로부터 output neuron 이 만들어진다.
- output layer activation function 으로는 hidden layer activation function 과는 다른 softmax 등을 사용한다.
- hidden layer activation function h(x) = g(a(x)) 에서 activation function g(-) 은 sigmoid, tanh, recline 등이 될 수있다.
- single neuron 으로 표현이 힘든 xor(x1,x2) 를 표현할 수 있다.
- a(x) = b(1) + W(1)x  : W 는 여러기의 뉴런들을 matrix 로 표현
- softmax 는 output layer activation function 으로 사용한다. 확률값으로 모든 출력 노트의 출력값이 1로 했을때의 각 노의 확률값을 표현
  - softmax(a) = [ { exp(a1) / sum(c)exp(ac) } ... { exp(ac) / sum(c)exp(ac) }]
- 각 hidden layer 는 single layer neural network 처럼 pre-activation 과 activation function 이 있다.
- trainning data {(xi,yi)} 로 부터 neural network 의 weight matrix W 들을 학습해야 한다.
- 학습된 neural network 에서 test data x 를 input layer 에 넣고 output layer 의 값을 계산함으로써 y(hat) 을 추정할 수 있다.


### 경험적 위험 최소화(Empirical Risk Minimization)

- training data 를 가장 잘 설명할 수 있는 가장 적합한 parameter 를 찾는게 인공신경망 training 이고 이를 해결하기 위한 방법으로 risk minimization을 있다.
- empirical risk minimization 알고리즘(수식)은 다음과 같은 2부분이 더해져 나온다.
  - (1번째) 정답을 가장 잘 맞출 수 있는 parameter 를 구하는것 + (2번째)최대한 간단한 모델이 되도록 하는것
- 