# harbor

- chart 원본 파일(Chart.yaml, templates/, values.yaml 등 tgz 압축 해제 결과물)은
  `.gitignore` 로 커밋 대상에서 제외되어 있다.
  git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- 클론 직후에는 chart 원본이 없으므로 아래 절차로 받아서 압축을 풀어야 한다.
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
--values values-ysoftman.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  harbor.ysoftman
http://harbor.ysoftman
```
