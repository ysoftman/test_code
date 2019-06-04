# K-MOOC '인공지능의 기초'

2019년 서울대학교 김건희 교수

## 1주차 - 인공지능의 소개

- 인공지능의 정의
  - 정의가 쉽지 않다.
  - computaion model 로 구현하는 학문
  - 결국에서 사람이 잘하는 일을 컴퓨터가 할 수 있게 하는 학문
  - 지능적인 행동을 자동화 하는것

- 지능이란?
  - 정의가 쉽지 않다.
  - 지식이나 여러가지 기술을 습득하는 능력
  - holistic(전체적인) intelligence(지능)은 정의 하기 어렵지만, 지능을 갖추려면 어떤 요소가 필요한지 나열하기는 쉽다.(지능적인 행동의 정의 쉽다.)
  - 지능은 다양한 레벨로 정의 할 수 있다.

- AI 4가지 관점
  - think humanly : 사람처럼 생각
  - think rationaly : 이성적으로 생각
  - action humanly : 사람처럼 행동
  - action rationaly : 이성적으로 행동
  - 위 4가지 관점에서 인공지능을 바라볼 수 있다.

- 약인공지능(weak AI)
  - applied AI 또는 narrow AI 라고 불리며, 특정 도메인 또는 주어진 환경에만 적용 가능한 좁은 영역의 인공지능
- 강인공지능(string AI)
  - 사람을 모방하지지 않고, 자유의지, 자각을 가지고 스스로 행동하는 인공지능, SF 영화에서 등장하고 아직 현실세계에 없음.
  - 쉽게 도래하지 않을것 같음.

- 특이점(technological singularity)
  - 인공지능이 사람의 지능을 뛰어 넘는것
  - 알파고가 이세돌을 이긴 경우 바둑의 영역에서 약간의 특이점을 엿볼수 있다.
  - 특이점은 물리학 블랙홀에서 나온 용어로 사건의 지평선 내부는 빛조차도 빠져나올 수 없는 미지의 영역이라는 의미

- 인공지능의 발전의 역사
  - 1770년 mechanical turk (사람이 기계안에 들어가서 체스를 두는 장치)로 사기(fake)를 쳤다.
  - 1950년 imitation game 이름이 후에 turing test 바뀜
  - 1952년 audrey 전화를 통해 전화번호를 얘기할 전화번호를 자동인식하는 시스템
  - 1956년 dartmonth AI 학문의 처음으로 시작된 학회
  - 1959년 alpha-beta pruning 체스 알고리즘 개발
  - 1997년 IBM deepblue 체스 프로그램 개발
    - CMU 학생들이 depp thought 를 만들었고 졸업후 IBM 에서 deepblue 개발
  - 1966-1972년 shakey 최초의 인공지능 이동 로봇
  - 2004년 asimo 휴머노이드 개발
  - 2007년 DARPA urban challenge 도시에서 자율주행 자동차가 얼마나 잘 갈 수 있는지 경쟁
  - 2016년 deep mind alphago 가 이세돌 4:1로 이김
  - 2017년 deep mind alphago 갖 커제 3:0로 이김

## 2주차 - 문제 해결 및 탐색 전략

- romania(루마니아) 문제
  - arad(state,상태) 에서 시작해서 여러개의 action을 통해 도시를 옮겨 bucharest(state) 까지 갈때의 sequence 와 action 을 solution(해) 으로 정의할 수 있다.
  - 여러 해중 최단거리를 최고의 해라고 할 수 있다.
    1. initial state(초기상태)
    2. possible actions(상태를 이동하기 위한 행동)
    3. goal test(해를 찾았는지 파악하는 테스트)
    4. path cost(상태를 이동할때의 비용),step cost c(x,a,y) x 에서 y 로 갈때의 action 수행할때의 비용함수
  - 실세계는 매우 복잡하니 추상화시켜 간단하게 표현

- tree search algorithm
  - 위와 같은 문제는 tree search 알고리즘을 사용
  - 모든 가능한 상태를 펼쳐놓은 트리구조로 되어 있고, 상태(노드)를 이동(탐색) 하는 edge는 액션
  - 탐색시 다음 4가지 정보를 제외하고 정보가 없는것을 uninformed search 전략이라고 한다.
    - completeness : 완전성, 해를 찾을 수 있느냐
    - time complexity : 시간 복잡도
    - space complexity : 공백 복잡도
    - optimality : 최적의 솔루션을 찾을 수 있느냐

- uninformed search 전략
  - breadth first state(BFS, 너비우선탐색)
    - FIFO(first in first out) queue 에 탐색 중인 노드를 기록하면서 탐색
    - fringe(주변,가장자리): FIFO queue, 아직 펼쳐지지 않은 노드
    - completeness : yes(해를 찾을 수 있다.)
    - time complexity : O(b^d+1)
      - b:한노드에서 펼쳐질 수 있는 노드의 개수
      - d:goal이 있는 depth
    - space complexity : O(b^d+1)
    - optimality : yes
    - DFS 에 비해 답을 찾는것을 보장하지만 시간,메모리를 많이 차지 한다.
  - depth first state(DFS, 깊이우선탐색)
    - LIFO(last in first out) queue 에 탐색 중인 노드를 기록하면서 탐색
    - completeness : no(깊이 탐색중 무한 루프에 빠져서 해를 찾을 수 없는 경우도 있다.)
    - time complexity : O(b^m)
      - m:탐색할 깊이
    - space complexity : O(bm)
    - optimality : no

- Quiz

```text
다음 설명이 가리키고 있는 것이 무엇인지 고르시오.
- 1950년데 만들어진 기계가 인간과 얼마나 비슷하게 대화할 수 있는지를 기준으로 기계에 지능이 있는지를 판별하고자 하는 테스트이다.
- Imitation game 으로도 불린다.
정답 : Turing test

다음 graph의 노드 A에서 Breadth-First Search를 실행하였을 때 탐색 과정에서 방문하는 노드를 순서대로 기입하시오.
a
- b
  - e
    - g
    - h
      - f
- c
- d
  - i
정답 : abcdeighf

다음 graph 노드 A에서 Depth-First Search를 실행하였을 때 탐색 과정에서 방문하는 노드를 순서대로 기입하시오.
(위와 같은 graph)
정답 : abeghfcdi

다음 graph의 노드 A에서 Breadth-First Search를 실행하였을 때 탐색 과정에서 방문하는 노드를 순서대로 기입하시오.
a
- b
  - d
    - h
  - e
    - h
- c
  - f
    - h
  - g
    - h
정답 : abcedfgh

다음 graph 노드 A에서 Depth-First Search를 실행하였을 때 탐색 과정에서 방문하는 노드를 순서대로 기입하시오.
(위와 같은 graph)
정답 : abdhecfg
```

## 3주차 - 휴리스틱(heuristic) 탐색

- uninformed 반대로 추가적인 정보가 있을 경우를 휴리스틱이라고 한다.
- 탐색시 노느를 평가하는 함수를 만들어 문제를 푸는데 있어 적합한 노드인지 판단한다.
- greey best-first search
  - 휴리스틱함수:휴리스틱한정보(bucharest까지 가는 직선거리를 알고 있는 경우)를 보고 평가하는 함수
- A*(star) search
  - f(n) = g(n) + h(n)
  - f(n) : 평가함수
  - g(n) : 노드n까지 오는데 걸린 비용
  - h(n) : 현재노드n -> 목적노드까지의 비용
  - 아이디어 : 현재노드들중 goal까지 도달하는데 가장 빠른 노드를 펼치(탐색)는 동시에 그 노드까지 가는데 있어 이미 비싼 비용을 치렀다고 하면 그 노드는 더이상 탐색하지 않는다. 즉 (어떤 노드까지 올린 cost + 그 노드 부터 goal 까지 가는데 예측된 비용)을 활용한다.
  - 탐색 중인 노드의 평가함수보다 큰 노드들 탐색에서 제외한다.
  - greedy best-first search 보다 최적의 솔루션을 찾을 수 있다.

- admissible(허용될 수 있는) heuristic
  - h(n) <= h*(n) 일때 admissble heuristic 이라고 한다.
  - h(n) : 우리가 사용하는 휴리스틱
  - h*(n) : 실제 골까지의 비용
  - 휴리스틱 함수가 admissible 하면 A* 알고리즘으로 최적의 솔루션을 찾을 수 있다.

- local search(지역 검색) algorithms
  - 최단경로 찾기의 경우의 global seach
  - 목적(goal)까지의 path 는 중요하지 않고 목정을 달성하는것만 중요한 경우에 사용
  - 매 상태 에서 좀더 나은 상태로만 가보자. 시간, 메모리 절약
  - hill-climbing(언덕 오르기) search 방법
    - 예) 에베레스트 산을 올라 가는데 주변에 안개가 있어 시야확보가 되지 않는다, 기억상실에걸려있다.
    - steepest(가파른) ascent(오르기) : 주변 상태중에 가장 경사가 급한 곳(목적함수가 가장 높은) 곳으로 가는 방법
    - greedy local search : 지금 내가 취할 수 있는 행동줄 가장 좋은 행동을 취하는 방법
    - initial point 을 어디로 잡느냐에 따라 결과가 매우 달라진다.
    - shoulder : 경사가 없는 평평한 영역이지만 이웃하는 곳에 더 높은 곳으로 갈 수 있다.
    - flat : 경사가 없는 평평한 영역이지만 이웃하는 곳에 더 높은 곳으로 갈 수 없다.
    - local maximum,optimum 에 빠지는 문제가 생길 수 있다.
    - 8-queens 문제, 체크 퀸이 서로 공격하지 않는 위치로 만들기
  - simluated annealing(쇠담금질) search 방법
    - hill-climinb 의 문제를 해결하기 위해 고안한 방법
    - 중간중간 현상태보다 안좋은 상태 이동을 허용(임의의, 처음엔 크게, 점점 작게만 허용)한다.
    - 처음에는 온도가 높았을때는 randomness 크고, 점점 온도가 낮아지면서 randomness 가 작아진다.

## 4주차 - 강화학습(reinforcement learning, RL)

- RL이란? AI agent 에 잘했으면 reward(보상), 못했으면 punishment(벌)을 줘서 학습시키는 방법
- reward funcion : 보상을 주는 함수
- fills in the details : AI(agent) 가 스스로 채워(배워)야 한다.
- 기본 RL model
  - agent 가 최대의 보상을 받을 수 잇는 제어 정책을 찾는것
  - reward 를 어떻게 정의하느갸 중요
  - agent 3가지 요소
    - policy : agent 행동을 정의
      - deterministic policy : 어떤 state 에서 어떤 action 을 할지 하나하나 정해놓은것
      - stochastic policy : 어떤 state 에서 어떤 action 을 할지 확률분포로 정해놓은것
    - value function : agent 가 state -> state 이동할때 얼마나 좋은지를 나타내는 함수
      - 미래에 보상에 대한 예측
      - v : state 에 대한 함수
      - q : state, action 에 대한 함수
    - model : agent 환경을 표현한것
      - p : state transition
      - r : reward 에 확률분포
- Maze(미로) exmaple : 미로 빠져나가기
  - reward : 한번 움직일때마다 -1, 쓸데없이 움직이면 벌을 받게 된다.
  - action : N,E,S,W 방향으로 움직일 수 있다.
  - states : agent 의 현재 위치
  - policy : 각 상태마다 가야 할 방향이 있다.
  - value function : 각 상태가 얼마나 값을 가지고 있는지 나타낸다.
- exploration(탐험) and exploitation(개척,활용,이용)
  - exploration 예: 가보지 않는 식당을 시도해본다.
  - exploitation 예: 이미 알고 있는 좋은 식당에 간다.
- prediction(예측) and control(제어)
  - prediction : policy 가 주어졌을때 value function 를 구하는 과정
  - contorl : reward 를 최대화 할 수 있는 policy 를 찾는 과정
  - V* : optimal value function
  - pi* : optimal policy(수많은 policy 중 reward 를 maximizing)

- markove decision process(MDP,마르코프 과정)
  - S : state 집합
  - P : transition function 상태 전이 확률, NxN 행렬로 표현, 확률 분포의 합은 1이다
  - episode(에피소드) : 초기 state 주어진 transition function 을 이용해 하나의 경험를 샘플링해보는 것(하나의 경우를 따져보는것)

- markov reward processes(MRP,마르코프 과정)
  - MDP에서 한단계 더 나간 모델
  - MDP 외 추가적으로 다음이 주어진다.
    - reward function : state 에 reward 를 매핑해주는 함수
    - discount factor : 하나의 스케일 값 (0~1.0)
    - R : 각 state 마다 reward 할당
    - gamma : discount factor
      - 0 값을 주면 근시안적인 모델(지금 당장의 reward 만 따라가도록)
      - 1 값을 주면 아주 멀리보는 모델(지금 당장의 rewad 와 먼 미래의 reward랑 똑같이 고려하겠다.)
  - discount factor(gamma) 왜 필요한가?
    - 수학적으로 안정화된다.(무한대 방지)
      - gamma 가 없으면 계속 자신의 상태로 움직이는 무한 루프에 빠질 수 있다.
    - agent 가 다음 상태에서 살아 남을 확률을 높여준다.
    - 당장의 reward 는 먼 미래의 reward 보다 가치있게 평가 받아야 한다.
- Quiz

```text
RL agent의 구성 요소로 옳지 않은 것을 고르시오.
정답 : state  (구성요소는 policy, model. value function)

다음 graph의 노드 A에서 노드 J로 가는 최단 경로를 찾는 경우, A* Search를 실행하였을 때 도출되는 최단 경로를 순서대로 기입한 것을 고르시오.
(그래프 생략)
정답 : afgij  (A 근접 노드 중 가장 비용이 적는 노드를 선택해간다.)

Markov Reward Process의 discount factor에 대해 옳게 서술한 것을 고르시오.
[예시] Discounter factor가 사용되는 이유는 ...
정답 : Discount factor는 loop 등과 같은 graph에서 value가 무한하게 커지는 것을 방지하기 위한 value function의 장치이다.


다음 중 A* 알고리즘이 OPTIMAL한 경우를 고르시오.
정답 : Heuristic function h(n)이 admissible할 경우

다음 중 옳은 것을 고르시오.
정답 : Simulated Annealing serach는 항상 임의의 경로를 선택하여 이동한다.
```

## 5주차 - 마르코프 결정 과정(markov decision process, MDP)

- MRP 에서 A(action 집합)요소가 추가됨
- policy : 어떤 state 에서 어떤 action 을 취할 확률 분포 로 정의 가능
  - 현재 state 에만 의존
  - policy 는 stataionary(고정), 시간에 따라 변화되지 않는다.
- value function
  - policy 에 의존적이며, 아래 첨자로 pi(policy) 가 추가되었다.
  - 또다른 형태의 value fuction Qpi(s,a) 가 추가되었다.
    - V 는 state value function 이라 부르고
    - Q 는 state action value function 이라고 부른다.
- Bellman Equation
  - Bellman Expecation Equation : 현재 state 의 value function 과 다음 state 의 value function 의 상관관계를 정의
  - Bellman Optimality Equation(이 강의에서 제외)
