# grafana

- 테스트를 위한 grafana 입니다. chart 는 upstream [grafana-community/grafana](https://github.com/grafana-community/helm-charts/tree/main/charts/grafana) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `grafana.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- datasource 로 `prometheus` 앱(`prometheus-server.prometheus.svc.cluster.local`)을 기본 등록한다.
- admin 계정은 `admin` / `ysoftman` 으로 고정한다(테스트 클러스터라 git 에 둔다. 지정하지 않으면 chart 가 랜덤 값을 만들어 argocd 에서 OutOfSync 가 된다).
- (선택) 비밀번호를 git 에 두고 싶지 않으면 secret 을 수동으로 만들어 참조할 수 있다.
  `values-ysoftman.yaml` 의 `adminUser`/`adminPassword` 를 지우고 아래 `admin.existingSecret` 설정으로 바꾼다.
  secret 이 없으면 파드가 `CreateContainerConfigError` 로 기동하지 않는다.

```yaml
admin:
  existingSecret: grafana-admin
  userKey: admin-user
  passwordKey: admin-password
```

```bash
kubectl --context colima create namespace grafana
NEW_PASSWORD='원하는비밀번호'
kubectl --context colima -n grafana create secret generic grafana-admin \
  --from-literal=admin-user=admin \
  --from-literal=admin-password="$NEW_PASSWORD"
```

- 비밀번호를 바꿀 때는 secret 을 지우고 같은 명령으로 다시 만든 뒤 grafana 파드를 재시작한다.
  (grafana 는 DB(sqlite)에 저장된 admin 비밀번호를 우선하므로, persistence 를 켠 상태라면 UI 나 `grafana cli admin reset-admin-password` 로 바꿔야 한다.)

- 수동 배포시

```bash
helm upgrade --install grafana grafana \
--repo https://grafana-community.github.io/helm-charts \
--version 14.4.0 \
--namespace grafana \
--create-namespace \
--values values-ysoftman.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  grafana.ysoftman
http://grafana.ysoftman
```
