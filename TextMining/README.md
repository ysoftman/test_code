# K-MOOC '텍스트 마이닝 실전 및 분석'

## 실습 환경

```bash
# eclipse, yTextMiner 다운로드
https://www.eclipse.org/downloads/
http://informatics.yonsei.ac.kr:8080/yTextMiner/home.html

# 빌드
eclipse -> file -> open projects from file system -> import source -> yTextMiner 경로 추가
src -> edu.yonsei.lexical_analysis -> SimpleTokenizer.java -> (pop-up menu) run as -> java application

# JRE 빌드 환경에 에러 발생시
properties(alt+enter) -> java build path -> jre system library -> 현재 설치된 jre 버전에 맞게 변경
```

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
  - "the boy's car are different colrs" -> the boy car be different color
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
