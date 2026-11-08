# grafana

- 테스트를 위한 grafana 입니다. chart 는 upstream [grafana-community/grafana](https://github.com/grafana-community/helm-charts/tree/main/charts/grafana) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `dashboard-*.yaml`, `README-ysoftman.md`, `.gitignore` 이다.
- 대시보드는 파일별로 분리한다. 각 `dashboard-*.yaml` 은 `dashboards.default.<name>.json` 키만 가지며,
  argocd-apps 의 `grafana.valueFiles` 로 `values-ysoftman.yaml` 과 함께 전달되어 helm 이 deep-merge 한다.
  (chart 가 원격이라 `.Files` 로 JSON 파일을 읽을 수 없어 values 파일로 나눈다.)
  - `dashboard-vector-pipeline.yaml`: vector 처리량과 로그 줄 수(prometheus datasource)
  - `dashboard-loki-logs.yaml`: 컨테이너 로그, 에러 로그, 레벨별 그래프(loki datasource)
  - 대시보드를 추가하려면 새 `dashboard-<name>.yaml` 을 만들고 argocd-apps 의 `grafana.valueFiles` 에 한 줄 추가한다.
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
--values values-ysoftman.yaml \
--values dashboard-vector-pipeline.yaml \
--values dashboard-loki-logs.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  grafana.ysoftman
http://grafana.ysoftman
```
