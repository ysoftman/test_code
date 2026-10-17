# nginx

- 테스트를 위한 nginx 입니다. chart 는 upstream [bitnami/nginx](https://github.com/bitnami/charts/tree/main/bitnami/nginx) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `nginx.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- 수동 배포시

```bash
helm upgrade --install nginx oci://registry-1.docker.io/bitnamicharts/nginx \
--namespace nginx \
--create-namespace \
--values values-ysoftman.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  nginx.ysoftman
http://nginx.ysoftman
```
