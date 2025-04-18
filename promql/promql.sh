#!/bin/bash
# [문제]
# grafana dashboard 에서 기간을 7일/30일등으로 길게 하면 시간이 오래 걸린다.(참고로 롱쿼리를 위해 prometheus liveness/readiness timeout 30초로 늘려놓음)
# Prometheus는 단일 바이너리 프로세스로 동작, 한 쿼리가 너무 오래 걸리면 전체 프로세스가 지연되고 /ready 응답도 늦어짐
# 문제가 되는 대시보드의 pane 들은 cpu, mem  등의 리소스 관련으로 시계열 데이터가 기간에 따라 증가하는 메트릭들을 조회한다
#
# [원인]
# 긴 쿼리 + 많은 시계열 = 리소스 폭발, 30일 범위의 쿼리는 수십~수백만 개의 데이터 포인트를 읽게 됨
# prometheus 부하는 크게 tsdb 로딩과 취합연산(sum,rate...)에서 발생
# prometheus /ready 는 단순한 살아있음 응답이 아니라 TSDB(Time Series Database) 상태, scrape 상태 등을 확인하기 때문에 느려질 수 있음
# 참고로 tsdb 는 보통 2시간까지는 메모리(head-series) 두고 2시간 이후는 disk 로 flush 해버린다
# --storage.tsdb.retention.time=30d  # 기간 제한
# --storage.tsdb.retention.size=10GB # disk 사용량 제한
# --storage.tsdb.min-block-duration=2h # tsdb 블록 사용 빈도(메모리 사용량에 영향)
# --storage.tsdb.max-block-duration=2h # tsdb 블록 사용 빈도(메모리 사용량에 영향)
# --storage.tsdb.head-series-limit=1000000 # 메모리 시계열 데이터 수 제한
# prometheus 캐싱이 없고 매 요청마다 tsdb 에서 찾는다
# 응답이 느린 슬로쿼리보다 응답이 빠른 쿼리를 동시에 여러개 부하를 주면 /ready 응답이 부하에 따라 10초이상 느려짐(아래 재현 스크립트로 테스트)
#
# [결론]
# 쿼리 기간을 너무 길게하지 말고 dashboard 하나에 다양한 pane(1개의 pand 에 n 개의 쿼리가 존재) 개수를 너무 많이 넣지 말고 요청을 여러번(refresh) 하지말자.

##### ready 지연 재현을 위한 테스트 #####
prometheus_host="ysoftman-prometheus.test.abc"
namespace="ysoftman-test"
cluster=""

# ready 응답 상태를 모니터링을 별도 터미널 창에서 띄워서 모니터링
# hwatch -n 1 "curl http://${prometheus_host}/-/ready"

queries=$(
    cat <<zzz
sum(rate(container_cpu_usage_seconds_total{namespace=~"$namespace", container!=""}[5m])) / sum(kube_pod_container_resource_limits{namespace=~"$namespace", resource="cpu"})
sum(container_memory_working_set_bytes{namespace=~"$namespace", container!=""}) / sum(kube_pod_container_resource_limits{namespace=~"$namespace", resource="memory"})
sum(container_memory_working_set_bytes{namespace=~"$namespace", container!=""}) by (pod)
sum(rate(container_cpu_usage_seconds_total{namespace=~"$namespace", container!=""}[5m])) / sum(kube_pod_container_resource_limits{namespace=~"$namespace", resource="cpu"})
sum(kube_pod_container_resource_requests{namespace=~"$namespace", resource="cpu"})
sum(kube_pod_container_resource_limits{namespace=~"$namespace", resource="cpu"})
sum(machine_cpu_cores{cluster="$cluster"})
sum(container_memory_working_set_bytes{namespace=~"$namespace", container!=""})
sum(kube_pod_container_resource_requests{namespace=~"$namespace", resource="memory"})
sum(kube_pod_container_resource_limits{namespace=~"$namespace", resource="memory"})
sum(machine_memory_bytes{cluster="$cluster"})
sum(kube_pod_status_phase{namespace=~"$namespace"}) by (phase)
label_replace((count(kube_service_info{namespace=~"$namespace", cluster=""}) or vector(0)), "kind", "Services", "", "")
label_replace((count(kube_ingress_info{namespace=~"$namespace", cluster="$cluster"}) or vector(0)), "kind", "Ingresses", "", "")
label_replace((count(kube_deployment_status_replicas{namespace=~"$namespace"}) or vector(0)), "kind", "Deployments", "", "")
label_replace((count(kube_statefulset_replicas{namespace=~"$namespace"}) or vector(0)), "kind", "Statefulsets", "", "")
label_replace((count(kube_daemonset_status_number_available{namespace=~"$namespace"}) or vector(0)), "kind", "Daemonsets", "", "")
label_replace((count(kube_configmap_info{namespace=~"$namespace", cluster="$cluster"}) or vector(0)), "kind", "Configmaps", "", "")
label_replace((count(kube_secret_info{namespace=~"$namespace", cluster="$cluster"}) or vector(0)), "kind", "Secrets", "", "")
label_replace((count(kube_hpa_labels{namespace=~"$namespace"}) or vector(0)), "kind", "Horizontal Pod Autoscalers", "", "")
label_replace((count(kube_networkpolicy_labels{namespace=~"$namespace", cluster="$cluster"}) or vector(0)), "kind", "Network Policies", "", "")
# 응답 30초가 넘어가는 slow query
# sum(kube_pod_status_reason{cluster="$cluster"}) by (reason)
zzz
)

# 응답 30초걸리는 느린 쿼리 여러번 요청을 날려도 응답은 느리지만 ready 응답은 1~2초내로 양호
# 응답 ~2초걸리는 빠른 쿼리 더라도 여러번 날리면 응답이 느려지면서 /ready 응답이 10~20초까지 느려진다.
IFS=$'\n'
for ((i = 0; i < 10; i++)); do
    for q in $queries; do
        # 주석 스킵
        [[ $q =~ ^# ]] && continue
        # 공백 제거
        # echo $q | sed "s/ //g"
        curl -g http://${prometheus_host}/api/v1/query_range?query="${q// /}&start=2025-04-01T00:00:00Z&end=2025-04-17T00:00:00Z&step=1h" >/dev/null &
    done
done
