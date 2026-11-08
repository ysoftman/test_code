# grafana

- 테스트를 위한 grafana 입니다. chart 는 upstream [grafana-community/grafana](https://github.com/grafana-community/helm-charts/tree/main/charts/grafana) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `grafana.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- datasource 로 `prometheus` 앱(`prometheus-server.prometheus.svc.cluster.local`)을 기본 등록한다.
- admin 계정은 `admin` / `ysoftman` 으로 고정한다(테스트 클러스터라 git 에 둔다. 지정하지 않으면 chart 가 랜덤 값을 만들어 argocd 에서 OutOfSync 가 된다).
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
