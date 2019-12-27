# curl http3 지원 빌드 테스트

- 빌드

```bash
# 스크립트 실행 후 curl 이 ./quiche/target/release/libquiche.dylib 라이브러리를 참조한다.
bash ./make_curl_supports_https.sh
```

- 테스트
  - http3 테스트 서버 : <https://bagder.github.io/HTTP3-test/>

```bash
./curl-http3-mac --http3 -I https://cloudflare-quic.com
HTTP/3 200
date: Fri, 27 Dec 2019 10:09:55 GMT
content-type: text/html
content-length: 106072
set-cookie: __cfduid=d8aeca1c4948f646dcb9c1c1bf23caa6c1577441395; expires=Sun, 26-Jan-20 10:09:55 GMT; path=/; domain=.cloudflare-quic.com; HttpOnly; SameSite=Lax; Secure
expect-ct: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
alt-svc: h3-24=":443"; ma=86400, h3-23=":443"; ma=86400
server: cloudflare
cf-ray: 54ba80725bb53a40-ICN

./curl-http3-mac --http3 -I https://quic.aiortc.org
HTTP/3 200
server: aioquic/0.8.4
date: Fri, 27 Dec 2019 10:12:13 GMT
content-length: 1068
content-type: text/html; charset=utf-8
```
