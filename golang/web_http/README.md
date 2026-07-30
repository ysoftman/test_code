# web_http

golang web http test

## 인증서 생성 (crt, key 파일 생성)

```bash
# openssl 사용시
openssl req -newkey rsa:2048 -nodes -keyout cert/server.key -x509 -days 365 -out cert/server.crt

# mkcert 툴 사용시
brew install mkcert
mkcert -key-file cert/server.key -cert-file cert/server.crt localhost 127.0.0.1 ::1 ysoftman.local
```

## build and run

```bash
go build && ./web_http
```

## test

```bash
# http 요청
curl 'http://localhost/main'

# 기본 https + http2
curl -Iv -k 'https://localhost/main'

# https + http1.1 로 요청시
curl -Iv -k 'https://localhost/main' --http1.1
```
