# vector

- chart 원본 파일(Chart.yaml, templates/, values.yaml 등 tgz 압축 해제 결과물)은
  `.gitignore` 로 커밋 대상에서 제외되어 있다.
  git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `vector.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- 수동 배포할 때는 chart 원본이 없으므로 아래 절차로 받아서 압축을 풀어야 한다.
- vector 차트 새로 받을때(버전 업데이트시)

```bash
helm repo add vector https://helm.vector.dev
helm repo update
helm pull vector/vector
tar zxvf vector-{최신버전}.tgz -C ../
```

- 수동 배포시

```bash
helm upgrade --install vector . \
--namespace vector \
--create-namespace \
--values values-ysoftman.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  vector.ysoftman
http://vector.ysoftman
```

- vector 처리 확인

```bash
kubectl exec -it $(kubectl get pod --no-headers -n vector | awk '{print $1}' | head -1) -n vector -- vector top
```

## vector > prometheus > grafana 파이프라인

```text
vector (kubernetes_logs -> log_to_metric, internal_metrics)
  -> prometheus_exporter :9598/metrics
  -> prometheus (pod annotation prometheus.io/scrape 으로 scrape)
  -> grafana (Vector Pipeline 대시보드)

vector (kubernetes_logs 원본)
  -> loki sink (http://loki.loki.svc.cluster.local:3100)
  -> grafana (Explore, 대시보드의 로그 패널)
```

- 로그 한 줄마다 `ysoftman_log_lines_total{namespace,pod,level}` counter 를 올린다.
  vector 자체 메트릭(`vector_component_received_events_total` 등)도 같이 노출한다.
- 컨테이너 로그 원본은 `loki_sink` 로 loki 에 보낸다. label 은 `namespace`/`pod`/`container` 만 쓴다(카디널리티 억제).
  grafana 에서 `{namespace="argocd"}` 같은 LogQL 로 조회한다.
- prometheus 는 `values-ysoftman.yaml` 의 `podAnnotations` 를 보고 scrape 한다(별도 scrape 설정 없음).
- grafana 의 `Vector Pipeline` 대시보드는 `helm/grafana/values-ysoftman.yaml` 의 `dashboards` 로 provisioning 한다.
- `customConfig` 는 chart 가 helm `tpl` 로 한 번 더 렌더링하므로, vector 템플릿 `{{ field }}` 는
  `'{{ "{{ field }}" }}'` 로 이스케이프해야 한다(안 하면 `function "field" not defined` 로 helm 렌더링 실패).
- 확인

```bash
# vector 가 노출하는 메트릭
kubectl --context colima -n vector port-forward ds/vector 9598:9598
curl -s localhost:9598/metrics | rg "ysoftman_log_lines_total|vector_component_received_events_total" | head
# prometheus 쿼리
curl -s -H "Host: prometheus.ysoftman" "http://127.0.0.1/api/v1/query?query=sum(rate(ysoftman_log_lines_total[5m]))"
# loki 에 로그가 들어오는지
kubectl --context colima -n loki port-forward svc/loki 3100:3100
curl -s localhost:3100/loki/api/v1/labels
curl -s --get localhost:3100/loki/api/v1/query_range --data-urlencode 'query={namespace="argocd"}' --data-urlencode 'limit=3'
```
