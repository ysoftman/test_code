# caddy 테스트

## 설치

```bash
# linux 설치
mkdir caddy && cd caddy
curl -L -O https://github.com/mholt/caddy/releases/download/v0.11.5/caddy_v0.11.5_linux_amd64.tar.gz
tar zxvf caddy_v0.11.5_linux_amd64.tar.gz

# mac 설치
brew install caddy
```

## 실행

```bash
caddy -conf ./caddyfile
```

## 빌드 및 플러그인 개발

- 참고
  - <https://github.com/mholt/caddy/wiki/Extending-Caddy>
  - <https://www.calhoun.io/building-caddy-server-from-source>

- 빌드

```bash
cd $GOPATH/src
go get -u github.com/mholt/caddy
go get -u github.com/caddyserver/builds
cd $GOPATH/src/github.com/mholt/caddy/caddy
#  build.go 를 실행함녀 caddy 실행파일이 생성된다.
# linux
go run build.go -goos=linux -goarch=amd64
# mac
go run build.go -goos=darwin
```

- 플러그인 빌드

```bash
# ysoftmanhellocaddy.go 파일 위치하기
mkdir -p $GOPATH/src/github.com/ysoftman/ysoftmanhellocaddy
cp -fv ./ysoftmanhellocaddy.go $GOPATH/src/github.com/ysoftman/ysoftmanhellocaddy

# run.go 에 ysoftmanhellocaddy 패키지 (init 수행되도록) _ 로 import
vi $GOPATH/src/github.com/mholt/caddy/caddy/caddymain/run.go
_ "github.com/ysoftman/ysoftmanhellocaddy"

# 플러그인 이름을 directive 로 추가한다.
vi $GOPATH/src/github.com/mholt/caddy/caddyhttp/httpserver/plugin.go
# var directives = []string { 부분에 추가
"ysoftman",

# mac 에서 빌드 및 실행
cd $GOPATH/src/github.com/mholt/caddy/caddy/build.go
go run build.go -goos=darwin

# 플러그인 리스트 확인
./caddy -plugins

# 플러그인 지시자 포함 설정 파일 생성
echo '# port
:8080
# 플러그인 지시자 사용
ysoftman hello_Caddy
' | tee $GOPATH/src/github.com/mholt/caddy/caddy/caddyfile

# 실행
./caddy -conf ./caddyfile
```
