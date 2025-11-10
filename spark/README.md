# spark 사용하기

- 스칼라,스파크 참고 <https://wikidocs.net/book/2350>

## 설치(mac 환경)

```bash
# spark 는 자바 실행환경이 필요하다.
# /usr/libexec/java_home 로 자바 설치 경로를 파악 후 $JAVA_HOME 환경 변수 설정
export JAVA_HOME=$(/usr/libexec/java_home)

# scala 설치
brew install scala

# spark 설치
brew install apache-spark

# spark 실행 가능하도록 링크(필요시)
brew link --overwrite apache-spark
```

## 사용법

```bash
# scala 를 사용하는 경우, spark-shell 실행
# scala> scala 코드 입력
# 또는
# scala> :load 로 scala 파일 로드
# 해서 및 실행
spark-shell
scala> :load ./scala_sample.scala

# help
scala> :load

# 종료
scala> :quit
```

- spark-shell(scala) 외 spark-submit(scala jar), sparkR(R), pyspark(python) 를 이용할 수 있다.
- <http://127.0.0.1:4040> 를 제공한다.
