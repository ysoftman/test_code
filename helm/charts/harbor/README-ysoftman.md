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
