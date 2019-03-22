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
