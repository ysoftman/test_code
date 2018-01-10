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
- 커널 종류 : Gaussian Kernel, Radial Basis Function, Polynomial 등
