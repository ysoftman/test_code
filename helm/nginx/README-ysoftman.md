# nginx

- 테스트를 위한 nginx 입니다. chart 는 upstream [CloudPirates nginx](https://github.com/CloudPirates-io/helm-charts/tree/main/charts/nginx) 를 사용한다.
  공식 `docker.io/nginx` 이미지를 tag+digest 로 고정해서 쓴다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `nginx.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다(nginx 버전은 chart 의 appVersion 을 따른다).

## bitnami 에서 CloudPirates 로 바꾼 이유 (2026-11-25)

- bitnami 무료 이미지는 `latest` 태그만 제공한다.
  chart 가 `bitnami/nginx:latest` + `imagePullPolicy: IfNotPresent` 라 노드에 예전 `latest`(1.31.7)가 남아,
  NGINX2Shell(CVE-2026-123007, CVE-2026-123633, 1.31.8 이하 취약) 패치가 반영되지 않았다.
- bitnami chart 는 `/opt/bitnami/nginx/conf` 를 emptyDir 로 덮고 entrypoint 가 `cp -n` 으로 채운다.
  VM 이 비정상 종료되면 0 byte conf 가 emptyDir 에 남아 pod 를 지울 때까지 CrashLoopBackOff 가 된다.
  CloudPirates chart 는 conf 를 덮지 않아 이 문제가 없다.
- 전환할 때 bitnami 가 만든 NetworkPolicy, PDB 는 nginx 앱이 prune 을 하지 않아 남는다.
  NetworkPolicy 는 8080/8443 만 허용해서 새 pod(80)로 가는 트래픽을 막으므로 직접 지웠다.

```bash
kubectl --context colima -n nginx delete networkpolicy nginx
kubectl --context colima -n nginx delete pdb nginx
```

## 수동 배포시

```bash
helm upgrade --install nginx oci://registry-1.docker.io/cloudpirates/nginx \
--version 0.16.18 \
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
