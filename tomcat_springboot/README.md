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
# install jdk gradle
sudo apt-get install openjdk-11-jdk

# download gradle
https://services.gradle.org/distributions/gradle-6.1.1-bin.zip
unzip gradle-6.1.1-bin.zip

# sprint boot 기본 생성 참고
https://start.spring.io/

# gradle init(최초1회)
gradle init

# gradle 로 빌드 -> .war 복사 후 tomcat 재시작
./gradle-6.1.1/bin/gradle clean build -b build.gradle --warning-mode all; \
cp -fv lib/build/tomcat_springboot.war ./apache-tomcat-9.0.31/webapp; \
./apache-tomcat-9.0.31/bin/catalina.sh start; \
./apache-tomcat-9.0.31/bin/catalina.sh run

# 동작 확인
http://localhost:8080/tomcat_springboot
```
