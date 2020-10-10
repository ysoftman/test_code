# tomcat test

## tomcat 설치 및 실행

```bash
# install tomcat
wget 'http://mirror.navercorp.com/apache/tomcat/tomcat-9/v9.0.31/bin/apache-tomcat-9.0.31.tar.gz'
tar zxvf apache-tomcat-9.0.31.tar.gz

# 설정 파일 변경 후 tomcat 실행 중지 및 실행
cp -fv server.xml ./apache-tomcat-9.0.31/conf/; \
cp -fv tomcat-users.xml ./apache-tomcat-9.0.31/conf; \
./apache-tomcat-9.0.31/bin/catalina.sh stop; \
./apache-tomcat-9.0.31/bin/catalina.sh start;

# 동작 확인
http://localhost:8080
http://localhost:8080/manager  # id:tomcat  pw:admin
```

## war 빌드 및 실행

```bash
# install jdk 12
# ubuntu 19
# sudo apt-get install openjdk-12-jdk
# mac
brew tap AdoptOpenJDK/openjdk
brew cask install adoptopenjdk12

# JVM 12.0.1 (AdoptOpenJDK 12.0.1+12) 환경에 동작하는 gradle 설치
wget https://services.gradle.org/distributions/gradle-6.2.2-bin.zip
unzip gradle-6.2.2-bin.zip
# JVM 확인
./gradle-6.2.2/bin/gradle --version

# sprint boot 기본 생성 참고
https://start.spring.io/

# gradle init(최초1회)
./gradle-6.2.2/ init

# gradle 로 빌드 -> .war 복사 후 tomcat 재시작
./gradle-6.2.2/bin/gradle clean build -b build.gradle --warning-mode all; \
cp -fv ./build/libs/tomcat_springboot.war ./apache-tomcat-9.0.31/webapps/; \
./apache-tomcat-9.0.31/bin/catalina.sh stop; \
./apache-tomcat-9.0.31/bin/catalina.sh run

# 동작 확인
http://localhost:8080/tomcat_springboot/hello

# war 에 문제가 있는지 체크할때
./gradle-6.2.2/bin/gradle clean build -b build.gradle --warning-mode all; \
java -jar ./build/libs/tomcat_springboot.war

# 동작확인
http://localhost:8080/hello
```
