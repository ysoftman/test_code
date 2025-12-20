# harbor

- harbor 차트 새로 받을때(버전 업데이트시)

```bash
helm repo add harbor https://helm.goharbor.io
helm repo update
helm pull harbor/harbor
tar zxvf harbor-1.18.1.tgz -C ../
```

- 수동 배포시

```bash
helm upgrade --install harbor . \
--namespace harbor \
--create-namespace \
--values values.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  harbor.ysoftman
http://harbor.ysoftman
```
