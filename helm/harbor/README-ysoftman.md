# harbor

- chart 원본 파일(Chart.yaml, templates/, values.yaml 등 tgz 압축 해제 결과물)은
  `.gitignore` 로 커밋 대상에서 제외되어 있다.
  git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `harbor.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- chart 는 1.18.1(harbor 2.14.1)에 고정한다. harbor 이미지는 amd64 전용이라 colima(arm64, rosetta 끔)에서 qemu 7.0 으로 에뮬레이션되는데,
  1.19.x(harbor 2.15, go1.26 빌드)는 jobservice 가 기동 중 runtime 교착이나 `fatal error: found bad pointer in Go heap` 으로 계속 죽는다.
  go1.24 빌드인 2.14.1 은 정상이다(2026-11-25 확인).
- chart 1.19.x 는 harbor-db 를 PostgreSQL 15 → 18 로 시작 시 `pg_upgrade` 하고 기존 pg15 데이터 디렉토리를 지워서 되돌릴 수 없다.
  올리기 전에 백업하고, 되돌릴 때는 `database-data-harbor-database-0`, `data-harbor-redis-0`(valkey 9 rdb) PVC 를 지워 새로 초기화한 뒤 백업을 복원한다.

```bash
kubectl -n harbor exec harbor-database-0 -c database -- pg_dumpall -U postgres > harbor-pg15-dumpall.sql
```

- 수동 배포할 때는 chart 원본이 없으므로 아래 절차로 받아서 압축을 풀어야 한다.
- harbor 차트 새로 받을때(버전 업데이트시)

```bash
helm repo add harbor https://helm.goharbor.io
helm repo update
helm pull harbor/harbor
tar zxvf harbor-{최신버전}.tgz -C ../
```

- chart 가 랜덤 생성하는 secret 값은 git 에 두지 않으므로, argocd sync(또는 수동 배포) 전에 클러스터에 한 번 만들어 둔다.
  (`values-ysoftman.yaml` 의 `existingSecret`, `existingXsrfSecret`, `secretName` 이 `harbor-secrets` 를 참조한다.)

```bash
openssl genrsa -out token.key 2048
openssl rsa -in token.key -traditional -out token.key
openssl req -x509 -new -key token.key -out token.crt -days 3650 -subj "/CN=harbor-token-ca"
REGISTRY_PASSWD=$(openssl rand -hex 16)
kubectl create namespace harbor
kubectl create secret generic harbor-secrets -n harbor \
--from-literal=secret="$(openssl rand -hex 8)" \
--from-literal=CSRF_KEY="$(openssl rand -hex 16)" \
--from-literal=JOBSERVICE_SECRET="$(openssl rand -hex 8)" \
--from-literal=REGISTRY_HTTP_SECRET="$(openssl rand -hex 8)" \
--from-literal=REGISTRY_PASSWD="$REGISTRY_PASSWD" \
--from-literal=REGISTRY_HTPASSWD="$(htpasswd -nbBC 10 harbor_registry_user "$REGISTRY_PASSWD" | tr -d '\n' | sed 's/\$2y/$2a/')" \
--from-file=tls.key=token.key \
--from-file=tls.crt=token.crt
rm token.key token.crt
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
