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
