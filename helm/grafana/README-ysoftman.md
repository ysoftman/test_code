# grafana

- 테스트를 위한 grafana 입니다. chart 는 upstream [grafana-community/grafana](https://github.com/grafana-community/helm-charts/tree/main/charts/grafana) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `grafana.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- datasource 로 `prometheus` 앱(`prometheus-server.prometheus.svc.cluster.local`)을 기본 등록한다.
- admin 계정은 git 밖에서 수동으로 만든 `grafana-admin` secret 을 참조한다(없으면 파드가 기동하지 않는다).

```bash
kubectl --context colima create namespace grafana
kubectl --context colima -n grafana create secret generic grafana-admin \
  --from-literal=admin-user=admin \
  --from-literal=admin-password="$(openssl rand -hex 12)"
# 비밀번호 확인
kubectl --context colima -n grafana get secret grafana-admin -o jsonpath='{.data.admin-password}' | base64 -d
```

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
