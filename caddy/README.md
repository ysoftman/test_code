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

- webdav 기능 추가해서 설치(빌드)하는 경우

```bash
# xcaddy(Custom Caddy Builder) 설치
go install github.com/caddyserver/xcaddy/cmd/xcaddy@latest

# caddy 클론
git clone https://github.com/caddyserver/caddy
cd caddy

# xcaddy 로 webdav 모듈 추가해서 빌드
xcaddy build master --with github.com/mholt/caddy-webdav
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
# run.go 에 ysoftmandirective 패키지 (init 수행되도록) _ 로 import
vi $GOPATH/src/github.com/mholt/caddy/caddy/caddymain/run.go
_ "github.com/ysoftman/ysoftmandirective"

# 플러그인 이름을 directive 로 추가한다.
vi $GOPATH/src/github.com/mholt/caddy/caddyhttp/httpserver/plugin.go
# var directives = []string { 부분에 추가
"ysoftmandirective",

# ysoftmandirective.go 파일 위치하기
mkdir -p $GOPATH/src/github.com/ysoftman/ysoftmandirective && cp -fv ./ysoftmandirective.go $GOPATH/src/github.com/ysoftman/ysoftmandirective

# mac 에서 빌드 및 실행
cd $GOPATH/src/github.com/mholt/caddy/caddy && go run build.go -goos=darwin && cd -

# 플러그인 리스트 확인
$GOPATH/src/github.com/mholt/caddy/caddy/caddy -plugins

# 플러그인 지시자 포함 설정 파일 생성
echo '# port
:8080
# 플러그인 지시자 사용
ysoftmandirective hello_Caddy
' | tee $GOPATH/src/github.com/mholt/caddy/caddy/caddyfile

# 실행
$GOPATH/src/github.com/mholt/caddy/caddy/caddy -conf $GOPATH/src/github.com/mholt/caddy/caddy/caddyfile
```
