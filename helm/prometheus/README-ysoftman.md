# prometheus

- 테스트를 위한 prometheus 입니다. chart 는 upstream [prometheus-community/prometheus](https://github.com/prometheus-community/helm-charts/tree/main/charts/prometheus) 를 사용한다.
  (operator/CRD 가 필요한 kube-prometheus-stack 이 아니라 가벼운 단일 chart 를 선택했다.)
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `prometheus.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- alertmanager, pushgateway 는 끄고 server(+ node-exporter, kube-state-metrics)만 사용한다.
- 수동 배포시

```bash
helm upgrade --install prometheus prometheus \
--repo https://prometheus-community.github.io/helm-charts \
--version 29.45.1 \
--namespace prometheus \
--create-namespace \
--values values-ysoftman.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  prometheus.ysoftman
http://prometheus.ysoftman
```
