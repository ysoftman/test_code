# K-MOOC '텍스트 마이닝 실전 및 분석'

## 실습 환경

- java sdk 1.8.0 이상 http://www.oracle.com/technetwork/java/javase/downloads/index.html
- yTextMiner 설치 http://informatics.yonsei.ac.kr:8080/yTextMiner/home.html

### eclipse 사용시

- eclipse 설치 https://www.eclipse.org/downloads/ 
- eclipse -> file -> open projects from file system -> import source -> yTextMiner 경로 추가
- src -> edu.yonsei.lexical_analysis -> SimpleTokenizer.java -> (pop-up menu) run as -> java application
- JRE 빌드 환경에 에러 발생시
  - properties(alt+enter) -> java build path -> jre system library -> 현재 설치된 jre 버전에 맞게 변경

### command-line 사용시

```bash
cd yTextMiner1.0
javac -Xlint -classpath lib\* src\edu\yonsei\lexical_analysis\SimpleTokenizer.java
java -classpath lib\*;. edu.yonsei.lexical_analysis.SimpleTokenizer
```

## TextMining 구성 요소

- 기술적(Descriptive) 분석 : 대량의 데이터를 유용한 정보로 요약함, 서술적
- 예측적(Predictive) 분석 : 현재까지의 현상을 가지고 미래를 예측함, 통계, 모델링, 데이터 마이닝, 머신러닝 등을 사용, 예)감성분석 -> 긍정인지 부정인지 분석
- 지시적(Prescriptive) 분석 : 예측적 모델을 넘어 각 결정의 예상 결과을 모두 알고 추천해준다.

## 텍스트 요소 단위별 분석

### 텍스트의 표현단위

- 어휘(lexical) 표현
  - 문자, 단어, 구, 품사 로 표현
- 구분(syntatic) 표현
  - 벡터-공간모델(vector-space model) : 비정형텍스트 -> 벡터 공간모델(검색, 추천등에 사용)
  - 언어 모델(language models) : 통계적인 기법으로 분포 파악
  - 전체 구문 분석(full-parsing) : 트리구조로 나누고 각각의 관계를 분석
- 의미론적(semantic) 표현 : 템플릿이나 온톨로지는 주제전문가의 수작업(의견)이 필요하다.
  - collaborative tagging / web2.0 : 일반 대중들의 집합적인 지능에 의미르 부여
  - templates /frames  : 어떤 동사어 어떤 단어와 같이 올 수 있는지 틀을 정해 놓는다.
  - ontologies /first order theories : 단어의 상위,하위, 반대의 개념등을 온톨로지로 구축

### 문자 단위 분석

- 문자 철자 오류를 찾기 위해 많이 사용
- 글자와 구분기호(,:? space등등)로 나우어진다.
- 문자 언어 모델(확률 분포를 통해)을 구축해 사용.
- 서픽스 배열(suffix array, 일련의 문자열의 접미사를 사전식 순서대로 나열해 찾는 방식)은 색인 작업에 많이 사용

### 단어 단위 분석

- 단어의 특징
  - homonymy : 말(언어), 말(동물) -> 같은 형식 + 다른 의미
  - polysemy : 다리(책상), 다리(지게) -> 같은 형식 + 관련 의미
  - synonmy : 가수, 보컬 -> 다른 형식 + 동일의미
  - hyponymy : 식사, 아침식사 -> 상하관계
- 품사 태킹, 개체명 인식, 철자 교정을 할때 사용
- 서양언어는 단어 분석하기에 적합하지만 한국어는 의미 단위로 다른 개념을 가져 서양 언어보다 어렵다.
- tokenization : 무자열에 주어졌을때 token 들로 문자열을 조각내는 작업
  - 구두점등 불필요한 글자 제외
  - 영어는 조사가 붙지 한글보다 tokenization 이 용이
- 불용어 : 정보를 전달하지 않는 단어로, 좋은 결과를 위해서 삭제한다. ex) 있, 않, the
  - 도메인에 따라 불용어 리스트가 달라질 수 있다.
- 품사태깅 (POS tagging) : 각 문장에서 각 단어가 가지는 품사로 태깅하는 작업, 문장의 형태소들의 품사를 파악하고 구조도 파악할 수 있다.

### zipf's (집스의) 법칙

- 단어 레벨에서 발결할 수 있는 법칙으로 '말뭉치(corpus)에 나타나는 단어들에 대해서 사용빈도가 높은 순서대로 나열했을때 모든 단어의 사용빈도는 해당 단어의 순위에 반비례 한다.'
- 브라운 대학교 말뭉치의 경우 다음과 같이 사용 빈도 순위에 반비례 한다.
  - 가장 사용 빈도가 높은 단어 'the' 인데, 말뭉치 전체의 7%(전체 1000000개 단어 중 69971회 쓰임),
  - 두번째 사용 빈도가 높은 단어 'of' 인데, 말뭉치 전체의 3.5%(전체 1000000개 단어 중 36411회 쓰임)

### 구 단위 분석

- 텍스트 단위화(text chunking) : 텍스트를 관련 있는 단어들로 나눈다.
  - 명사구, 동사구단위 인식(shallow parsing)
  - 품사태깅 후 단어간의 연관성을 따져 구를 파악

## 영어 전처리

### preprocessing 과정

- normalization : 텍스트와 쿼리를 동일한 형식으로 정규화, 용어의 동치관계(equivalence class)를 정의
  - windows, window -> window 로 통일
  - windows, Windows -> windows 소문자로 통일
- tokenization : 토큰으로 나누는 단계
  - 공백으로 끊지만, 이름과 같은 고유명사등에 있는 공백으로 끊으면 안된다.
  - that's 와 같은 축약은 that is 등올 바꿔주는 룰을 만들어야 한다.
- lemmatization : 원형 복원, 한단어가 여러가지 형식으로 표현되는 것을 하나의 단일 형식으로 묶어 주는 기법
  - 자연어 처리의 근간이 되는 형태소 분석으로 통해서 처리
  - 굴절형태론(inflectional morphology) : cutting -> cut
  - 파생형태론(derivational morphology) : destruction(명상), destructive(형용사) -> destroy
  - am, are, is -> be 동사 원형으로
  - car, cars, car's, cars' -> car 원형으로 복원
  - "the boy's cars are different colors" -> the boy car be different color
- stemming : 어간 추출, 어근만을 남겨두고 제거하는 것
  - automate, automatic, automation -> automat
  - 영어에서는 포터 어간 추출 알고리즘이 많이 쓰임
    ```bash
    ATION -> ATE   ex) relational -> relate
    TIONAL -> TION ex) conditional -> condition
    ```
- stopword removal : 불용어 삭제
  - the, a, of, in, to 등의 전치사 삭제
  - 불용어 리스트를 참고해서 삭제

## 한글 형태소 분석 기법 1

### 한글 형태소 분석기 소개

- 형태소(morpheme) : 의미 최소단위, 더ㅣ상 분석 불가능한 가장 작은 의미 요소
- 체언 : 명사, 대명사, 수사
- 용언 : 형용사, 동사
- 독립언 : 부사, 관형사, 감탄사
- 기능어 : 조사, 어미, 선어말어미, 접사
- 단순어의 어근(원형), 어미, 조사 접두사, 접미사
- 한글형태소 분석기 절차
  1. 분석 대상 문헌집단 선정
  2. 전처리 : 문장 추출, 어절분리, 부호/숫자/특수문자 처리
  3. 분석후보생성 : 원형복원 규칙 적용
  4. 결합제약검사 : 분석 후보들정 잘못된 분석 조정(결합제약 규칙 적용)
  5. 분석후보선택 : 어휘 사전을 활용하여 최종 결과 도출
  6. 후처리 : 중의성 해소, 미등록어 처리등
- 언어적 차이
 - 한글은 교착어(고립어와 굴절어의 중간적 성격을 띠는 것으로 어근과 접사에 의해 단어의 기능이 결정되는 언어의 형태)의 일종
 - 한글은 어간과 기능어를 활용하여 어절 생성
 - 영어는 어간의 변화 또는 연관 기능 형태소 결합으로 성,수, 시제를 표현
- 어휘 분석 기법
  - Lex(구문분석 프로그램) 사용
- 형태소 분석의 난제
  - 형태소 분석의 모호성
    - 한글) 감기는 -> 질병 감기? 줄을 감다? 머리를 감다?
    - 영어) cold -> 감기? 춥다?
  - 표준화 필요 : 한글 형태소 분석기의 분석 결과가 차이가 있다.
  - 띄어쓰기 문제, 신조어 맞춤법 오류로 이한 미등록 어휘 문제,복합명사 처리 문제
  - 한글의 가능한 음절 조합 수 : 11.172음절

### 한글 품사
- 규칙 기반 접근 방법
 - 긍정/부정 정보 활요해 점수 부여
 - 정밀하게 고안된 규칙은 정확성이 높지만 새로운 용어나 규칙의 변화로 인해 규칙 구축이 어려움
- 통계적 접근 방법 
  - 충분한 태그가 젱공되는 말뭉치로 부터 통계 정보 추출해 사용
  - HMM(hidden markov model) 과 같은 기계학습 사용
- 복합적 접근 방법 : 규칙기반 후 해소안된 부분에는 통게적 접근 적용

### 한글 형태소 분석기 종류
- UTagger(울산과기대) : HMM 기반 / c 언어
- 꼬꼬마(서울대) : HMM + 휴리스틱
- MACH(성신여대), KLT(국민대)
- 한나눔(카이스트) : 각 단계를 모듈로 분할 workflow
- Arirang(Lucene) : 루씬 검색엔진에서 한글 형태소 분석을 위해 사용
- Kormoran(shinware) : 오픈소스, 여러어절을 하나의 품사로 분석 가능, 사용자가 사전에 새로운 단어들을 추가 가능
- twitter-korean-text : scala 언어, 짧은 트윗이나 비정형 소셜 미디어에 특화

## 한글 형태소 분석 기법 2

### 구문분석

- 구문분석의 흐름도 : token stream -> 전처리(파서...) -> syntaxtree
- 파서(분석기)
  - 토근들을 보다 넓은 범위(exppression, statement, condition branch, loop)로 단위뢰 통합 하는 일
  - 규칙을 담고 있는 specifications 참고하여 파서 생성기에 의해서 만들어진다.
  - 문맥 자유 문법 : 4-tuple G(grammar) = (V,T,S,P)
    - V : nonterminal 집합, 언어에 존재하는 구성 요소들로 NP, VP, NN, TO 등
    - T : terminal 집합, 트리 구조에서 맨 아래쪽 텍스트들
    - S : 시작 심볼(Start symbol), 틀리의 맨위(뿌리)
    - P : 규칙(Rules)
  - 모든 단어는 노드로 표현하고 노드 사이의에는 의존적 관계가 있다.

### 한글 구문 분석 

- 구문 표지와 트리 태깅
  - 명사구(NP) 는 명사(N)와 격조사(이,가,을,를)와 접속사(와,과) 또는 특수조사(도,만), 주제격조사(은,는)로 형성될 수 있다.
  - 후치사구(PP) 는 명사구 외에 구문내에서 독립적으로 나타날 수 있는 성분들이다.
  - 관형사구(AP, Adnominal Phrase) 는 독립적으로 사용될 수 없는 범주로 반드시 뒤에 N이 포함된 명사구, 후치사구, 용언구가 나타나야 한다.
  - 용언구(VP) 는 동사와 형용사를 모두 포함하며 다른 범주와 달리 연달아 나타날 수 있고 또한 다른 범주와 관계하여 복잡하게 나타날 수 있기 때문에 어휘 범주인 V를 도입한다.
