# thrift go 사용하기

## thrift 설치

- 참고: <https://thrift.apache.org/docs/install/>

### prerequisite

```bash
#centos
sudo yum -y groupinstall "Development Tools"

# debian/ubuntu
sudo apt-get install automake bison flex g++ git libboost-all-dev libevent-dev libssl-dev libtool make pkg-config
```

### 소스 빌드 및 설치

```bash
wget http://apache.tt.co.kr/thrift/0.11.0/thrift-0.11.0.tar.gz
tar zxvf thrift-0.11.0.tar.gz
cd thrift-0.11.0
./bootstrap.sh
./configure
make
sudo make install

# mac 은 brew 로 설치끝
brew install thrift
```

### thrift 코드 생성

- 참고: <https://thrift.apache.org/tutorial/go>

```bash
# golang 에서 사용한 데이터 구조 생성(gen-go/)
cd tutorial
thrift -r --gen go tutorial.thrift

# tutorial 소스코드
cd thrift-0.11.0

# go thrift 패키지 다운로드
go get "git.apache.org/thrift.git/lib/go/thrift"

# 예제 코드
/tutorial/go.src/client.go
/tutorial/go.src/server.go
```
