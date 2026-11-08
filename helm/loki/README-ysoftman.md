# loki

- 테스트를 위한 loki 입니다. chart 는 upstream [grafana-community/loki](https://github.com/grafana-community/helm-charts/tree/main/charts/loki) 를 사용한다.
  (`grafana/loki` chart 는 `grafana-community` 로 이전되었다.)
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `loki.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- 단일 인스턴스(`deploymentMode: Monolithic`) + filesystem 저장소(PVC 2Gi)로 구성한다.
  `write`/`read`/`backend` replicas 를 0 으로 내리지 않으면 chart 검증에서 실패한다.
- cache(chunks/results), gateway, canary, test 는 테스트용이라 끈다.
  gateway 가 없으므로 접속 주소는 `http://loki.loki.svc.cluster.local:3100` 이다(멀티테넌시 꺼짐).
- 수동 배포시

```bash
helm upgrade --install loki loki \
--repo https://grafana-community.github.io/helm-charts \
--version 21.0.0 \
--namespace loki \
--create-namespace \
--values values-ysoftman.yaml
```

- 동작 확인

```bash
kubectl --context colima -n loki port-forward svc/loki 3100:3100
curl -s localhost:3100/ready
curl -s localhost:3100/loki/api/v1/labels
```
