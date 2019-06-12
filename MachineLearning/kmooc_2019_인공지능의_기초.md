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
  - contorl : reward 를 최대화 할 수 있는 policy 를 찾는 과정(optimal policy를 구하는 과정)
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
  - policy 는 stationary(고정), 시간에 따라 변화되지 않는다.
- value function
  - policy 에 의존적이며, 아래 첨자로 pi(policy) 가 추가되었다.
  - 또다른 형태의 value fuction Qpi(s,a) 가 추가되었다.
    - Vpi(S) 는 state value function 이라 부르고
    - Qpi(s,a) 는 state action value function 이라고 부른다.
- Bellman Equation(MDP 에서 가장 중요한 식)
  - Bellman Optimality Equation(이 강의에서 제외)
  - Bellman Expectation Equation : 현재 state 의 value function 과 다음 state 의 value function 의 상관관계를 정의
    - state 에서 actcion 을 취해 다른 state 로 가는 과정을 V, Q 의 2 step으로 구분
    - V value function : state 에서 취할 모든 action 에 대해서 확률분포(weighted sum) 에 Q 를 곱한것
    - Q value function : state(S)에서 action(A)를 취했을때 reward + gamma(discount) * (Pss'(action 에서 여러개의 state 로 갈 수 있는, state 확률분포)의 weighted sum 에) = expectation(기대값)
    - V 는 Q 로 정의가 되고, Q는 다음 step 의 state 의 V 값으로 정의 된다.
    - state 마다 value 가 주어지지 않았을때
      - n 개의 state, V = Nx1, P = nxn matrix 로 표현할 수 있다.
      - 구하는 방법1: MDP 에선 P, R 이 주어지고 random initialization 한 V 로 새로운 V 를 구하고, V 를 matrix 식에 맞게 계속 반복해 나가는 방법을 수렴된 V 를 구한다.
      - 구하는 방법2: indentity matrix(단위행렬) matrix 식을 역행렬고 변환해서 구한다.(nxn 역행렬의 복작도는 n^3 으로 추천하는 방법은 아니다.)
      - 구하는 방법3: 위 두 방법보다 효율적인 dynamic programming 로 구한다.
- optimal value functions
  - 주어진 문제에선 모든 policy 를 다 고려했을대 가장 최대가 되는 value function
  - MDP 에선 optimal policy 는 항상 존재한다.
  - optimal policy 를 따랐을때 value function = optimal value function
    - optimal value function 을 찾고 그에 대한 optimal policy 를 구해도 되고
    - optimal policy 를 찾고 그에 대한 value function 을 구해도 된다.
  - optimal policy 를 찾는 과정 => optimal value 를 찾으면 된다.

- dynamic programming(DP) 을 통한 MDP
  - 주어진 문제를 sub-problem 날 수 있고, sub-problem 을 구하면 전에 문제를 풀수 있을대 dynamic programming 을 사용한다.
  - MDP 가 이와 같은 조건을 만족하기 때문에 DP 로 Bellman Expectation Equation  을 풀 수 있다.
  - prediction : policy 가 주어졌을때 value function 를 구하는 과정
    - MDP 의 S, A, P, R, r 과 policy pi 가 주어졌을때 알 수 있다.
  - control : optimal policy를 구하는것 (=optimal value function 구하면 쉽게 알 수 있다.)
    - MDP 의 S, A, P, R, r 이 주어졌을때 알 수 있다.
  - iterative policy evaluation
    - policy 가 주어졌을대 이걸 evaluation 하는것(V pi 를 구하는 과정이다.)
    - v 초기화후 matrix muliplication 으로 주어진 수식대로 반복하면 V 가 수렴한다. 수렴된 결과가 policy 에 대한 evaluation 이 끝났것
    - 예제 4x4 grid world
      - 조건1 MDP r = 1
      - 조건2 terminal state(종료 state) : 맨왼쪽 맨위, 맨오른쪽 맨아래 2개가 있음
      - 조건3 girid 끝을 벗어나라는 action 있다면 그자리에 머무른다.
      - 조건4 reward 는 move 할때마다 -1
      - 조건5 random policy(현재 상태에서 취할 수 있는 액션을 같게)로 동,서,남,북 가는 확률을 0.25로 동일하게 했다.
      - next step value function = reward + gamma + state transition probability P + V
        - 처음에는 iteration 0 에서는 V k(policy) 를 모두 0 으로 초기화
        - 다음 stop value function(V) = R + (P * gamma * V)
        - K(policy) = 1,2,... 까지 위 과정을 반복 => greedy policy 를 구하는것
        - 계속 V 를 구해가면서 각 state 에서 value function 이 최대가 되는 방향으로 화살표(이동방향)을 표시하면, greedy policy 를 구할 수 있다.
        - greedy policy 경우 step 3정도까지만 V 를 구해가면 optimal policy 에 수렴된 greepy policy 를 구할 수 있다.
        - policy 만 구하는 경우 적은 iteration  으로 구할 수 있다.
        - evaluation 을 한다면 충붛나 iteration 으로 V 가 바뀌지 않을때 까지 수행해야 한다.
        - policy improvement : pi(policy) 가 주어졌을대, V pi 를 가지고 policy 를 improve 하는것
          - 않좋은 policy -> 좋은 policy 를 구하는 힌트
          - 특별한 아이디어 없다면 random policy(보통 0으로)로 시작
          - 현재 policy 에 대한 value function을 구한다음 greedy(각 state 의 action 에서 value function 이 최대가 되는것을 취하는것)으로 policy 로 바꾼다.
    - prediction 문제 푸는 방법
      - bellman expectation equation 과 iterative policy evaluation(algorithm)을 사용
    - control 문제 푸는 방법
      - bellman expectation equation + greedy policy improvement) 와 policy iteration(algorithm = iterative policy evaluation 과 greedy policy improvement를 반복하는 과정)
      - V 에 대헛 설명했지만 Q 에 대해서도 적용할 수 있다.
        - V (action=m x state=n 의 제곱 복잡도)를 주로 다루는 이유는 복잡도가 Q (m제곱 x n제곱)보다 적다.

## 6주차 - 게임이론(game theory)

- game theory 가정
  - player 들은 모두 이성적이다. 각자의 utility(효용함수)을 극대화하기를 원한다.
  - 각 플레이어들은 utility 를 최대화하 하기 위한 목적으로 선택한다.
  - 모든 player 은 다른 player 들이 rational(이성적)이라는것을 모두 알고 있다.
  - 예) 체스, 부르마블, 나라들끼리 경재하는 모습(정치학, 경제학에서도 활용), 투표
- 죄수의 딜레마(prisoner's dilemma)
  - 2명의 죄수가 있고, 각각 조사를 받는다.
  - 조용이 있거간 상대방을 밀고(implicate)하거나 조용히 있거나(silent) 액션을 취할 수 있다.
  - -1 : 1년 징역,... -n : n년 징역
                                죄수2
                      silent         implicate
    죄수1  silent       -1, -1          -5, 0
          implicate     0, -5          -3, -3
    게임 전체에서 보면 (silent, silent) 액션이 합리적
    각각의 player 에서 보면(dominant 한 policy 또는 strategy) 서로 밀고(implicate,  implicate)를 선택한다.
    - 또다른 죄수의 딜레마
      - nuclear arms race(핵무기 경쟁)
      - climate change(기후협약 탈퇴), 지구 전체를 위해선 협약을 지켜야 되지만 개인의 이득을 위해선 탈퇴하는게 좋을 수 있다.
- 게임을 정규 형태로 표현을 위한 3가지 component
  - N : 참여자(player) 개수, indexed by i
  - A : A1... An 로 action 집합
  - U : utility function(효용함수), ui(a) : player i 가 action a 를 취했을대의 효용성
  - 죄수의 딜레마에 적용해보면
    - N : 2
    - A : {Silent, Implicate} x {Silent, Implicate}
    - U u(a) 는 다음과 같은 경우가 된다. 2x1 벡터이다.

      ```text
      = [-1
         -1] if = (S,S)
      = [-5
          0] if = (S,I)
      = [0
        -5] if = (I,S)
      = [-3
        -3] if = (I,I)
      ```

- 제로썸게임(zero sum)
  - 부가 새로 생기지도 않고 사라지지 않는다. 누가가가 1을 얻으면 누군가는 1을 잃는다.
  - 둘을 합치면 0(효용의 합은 0이다.)
  - player2 utility 를 최대하는것은 player1 utility 를 최소하는것과 같다.
  - 예) 가위바위보
- pure and mixed strategies
  - palyer i 의 strategy(전략)  si : ai(action 에 대한 확률분포) 로 표현
    - 각각의 액션에 대한 전략의 값의 항상 0보다 크거나 같다
    - action 집합에 대한 확률 분표
    - support : 확률분포가 있을때 확률의 값이 0보다 큰영역
      - 전략에 적용해보면 action 들 중에 그 확률이 0이 아닌 action 들을 support 한다라고 말한다.
    - pure strategy : 모든 player 에서 si((어떤 action 을 취하는 확률분포상)가 시간에 따라 변하지 않고 고정
    - mixed strategy : si(어떤 action 을 취하는 확률분포상)에서 randomness 를 추가적으로 넣는 경우
      - 어떤 player 가 선택을 할때 si 를 따라가지 않고 가끔 그걸 벗어나는 무작위성을 가지고 있다.
- nash equilibrium(내시 평형)
  - best response : 나를 제외한 모든 플레이어들의 전략이 주어졌을때 내가 취할 수 있는 최선의 전략
  - profile(strategy) S 가 nash equilibrium 에 있다.
    - 자신(player)을 제외한 모든 player 들의 전략이 주어졌을때 최선의 전략이라는 뜻
  - nash equilibrium : player1 ... playerN 다 best response 로만 이루어진 전략 profile 을 의미
    - 나도, 남도 모두 최선을 다해서 평형 상태를 이루고 있어 내가 전략을 조금만 수정하더라도 나는 더이상 얻는게 없고 잃게 되는 경우
- player가 2명인 제로썸 게임 가위바위보 예제

  ```text
        R(rock)  P(paper)   (scissors)
     R      0,0      -1,1      1,-1
     P      1,-1      0,0      -1,1
     S     -1,1       1,-1      0,0

     첫번째 숫자만 취해서 일반적인 행렬을 만들 수 있다.
     player2 입장에선 값(utility)에 만 곱하면 된다.
           0,     -1,      1
           1,      0,     -1
          -1,      1,      0
  ```

  - pure maxmin(minmax) strategies
    - 상대방은 자신에게 가장 유리한 action 을 취할것이다. 이걸 모든 플레이어가 알고 있다.
    - player1 입장에선 매트릭트에서의 각 행(액션)의 최솟(min)값들 선택하고 그 중에 최대(max)가 되는것을 택하는것을 maxmin 전략이라고 한다.(이것이 player1 의 utility 를 최선으로 하는 방법이다)
    - player2 는 player1 의 값에 -값을 곱하고, 각 열의 최대(max)값들 선택하고 그중 최솟(min)값이 되는것을 택하는것 minmax 전략이라고 한다.
    - player 입장에 따라 maxmin, minmax 가 된다.
    - player1 과 player2 가 maxmin 전략을 통해 얻을 수 있는 것을 이 게임의 가치(value)라고 정의 한다.
    - player1 의 액션과 player2 의 액션을 모아서 maxmin solution 또는 minmax solution 이라고 한다.
    - saddle(안장) point : 안장모양으로 어떤 방향으로는 minimum 이 되고 어떤 방향으로는 maximum 이 되는 포인트(2 그래프가 만나는 점)
      - maxmin solution 의 경우 row의 minimum 이고 column 의 maximum 이기 때문에 saddle point 라고 얘기한다.
    - two  player zero-sum game 에선 maxmin solution 을 구하게 되면 이건 항상 nash equilibrium 이 된다.
    - iff(if and only if, 필요 충분 조건) = equivalent(동치)
      - 만약 a,b 가 zero-sum game 의 solution 이면 a,b 는 nash equilibrium 만족
      - 만약 a,b 가 nash equilibrium 이면 a,b 는 zero-sum game 의 solution 만족
    - player1,2 모두 이성적 선택을 한경우 nash equilibrium 이 된다.
  - multi player 가 되면 갑자기 어려워져서 이번 강의에선 다루진 않습니다.
    - N 명의 player 에 있어서의 명확한 이론은 아직 개발 되지 못했다.
  - non-zero-sum game 의 경우
    - 특정 게임에서 nash equilibrium(ne) 을 찾을 수 있지만 모든 non-zero-sum 통일해서 ne 를 찾는건 어렵다.
    - stag hunt(수사슴 사냥) 게임
      - 2명의 사냥꾼은 사슴을 잡던지, 산토끼를 잡는 선택한다.
      - 사슴은 항상 2명의 사냥꾼이 있어야 잡는다.
      - 산토끼는 1명의 사냥꾼이 잡을 수 있다. 하지만 사슴보다 utility 보다 훨씬 낮다.
      - (stag,stag) (hare,hare) 의 경우가 nash equilibrium 이다.

      ```text
                        Stag(수사슴)    Hare(산토끼)
        Stag(수사슴)         2,2           0,1
        Hare(산토끼)         1,0           1,1
      ```

    - battle of the sexes(성대결) 게임
      - 남편은 풋볼을 보러 가는걸 원한다.
      - 부인의 경우 발레를 보러 가는걸 원한다.
      - 부부가 서로 얘기하지 않는 상황

      ```text
                                Ballet(발레)    Football(풋볼)  wife
        husband  Ballet(발레)         2,3           0,0
                Football(풋볼)        1,1           3,2
      ```

    - game of chicken(치킨게임)
      - 갈등이 증폭되는 과정을 표현하는 모델로 많이 사용된다.
      - 사거리에서 두마의 (닭)사람이 있는 경우 둘다 직진하면 서로 나고, 둘다 양보하면 둘다 못가지만 사고는 막을 수 있다.

      ```text
                                straight    chicken
        straight                 -10,-10       1,-1
        chicken(겁쟁이,양보)        -1,1         0,0
      ```

- Quiz

```text
아래 graph가 random policy를 만족하며 𝛾=1일 때, 붉은 색 노드의 𝑉_𝜋(𝑠)를 구하시오. (𝜋(𝑎|𝑠)=0.5)
value function(V) = R + (P * gamma * V)
R(reward=3)
P(state transition probability=0.5)
gamma(𝛾=1)
V(state value function)
붉은색 노드에서 갈 수 있는 상태는 2개로 각각 0.5 확률로 7 또는 3 의 reward 를 받는다.
7 reward 의 경우 진행할 action 없어 끝
3 reward 의 경우 0.3 의 확률로 4.1 노드로 간다.(이전 3으로 왔을떄의 0.5 확률을 곱해해야 한다.)
3 reward 의 경우 0.4 의 확률로 -2.1 노드로 간다.(이전 3으로 왔을떄의 0.5 확률을 곱해해야 한다.)
3 reward 의 경우 0.3 의 확률로 3.1 노드로 간다.(이전 3으로 왔을떄의 0.5 확률을 곱해해야 한다.)
정답 : (7*0.5)+(3*0.5)+((0.5*0.3*4.1)+(0.5*0.4*-2.1)+(0.5*0.3*3.2)) = 5.675


Zero-sum game을 아래와 같이 matrix로 나타내었을 때, Pure Maxmin Strategy를 사용하여 solution을 구하시오.
      b1    b2    b3
a1    -1     1     2
a1     2    -3     4
a1     2     3     5
player1 입장에선 각행(a-action)의 utility 값중 최소값을 찾고(-1, -3, 2) 이중 가장 큰 값(3)이 있는 a3 액션을 선택 (maxmin 전략)
player2 입장에선 각열(b-action)의 utility 값중 최대값을 찾고(2, 3, 5) 이중 최소값(2)이 있는 b1 액션을 선택 (minmax 전략)
정답 : (a3, b1)


다음 Stag Hunt 중, Nash Equilibrium을 모두 고르시오.
a) (Stag, Stag) b) (Stag, Hare) c) (Hare, Stag) d) (Hare, Hare)
                Stag(수사슴)    Hare(산토끼)
Stag(수사슴)         3,3           0,2
Hare(산토끼)         2,0           1,1
두명의 플레이어가 서로 평행을 이루는 경우를 선택하면 된다.
정답 : a, d


다음 중 옳지 않은 것을 고르시오.
iteration 해도 변화가 없으면 멈춰야 된다.
정답 : Iterative policy evaluation은 value function이 diverge할 때까지 계속한다.


다음 게임이론에 대한 설명으로 옳지 않은 것을 고르시오.
게임이론에서는 플레이어들은 이성적으로 행동한다고 가정한다.
정답 : 플레이어는 이성적으로 행동하지 않고, 임의의 행동을 반복한다.
```
