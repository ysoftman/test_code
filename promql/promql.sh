#!/bin/bash
# grafana dashboard 에서 기간을 7일/30일등으로  길게 하면 시간이 오래 걸린다.(참고로 롱쿼리를 위해 prometheus liveness/readiness timeout 30초로 늘려놓음)
# 긴 쿼리 + 많은 시계열 = 리소스 폭발, 30일 범위의 쿼리는 수십~수백만 개의 데이터 포인트를 읽게 됨
# prometheus /ready 단순한 살아있음 응답이 아니라 TSDB 상태, scrape 상태 등을 확인하기 때문에 느려질 수 있음
# Prometheus는 단일 바이너리 프로세스로 동작, 한 쿼리가 너무 오래 걸리면 전체 프로세스가 지연되고 /ready 응답도 늦어짐
# 쿼리 기간을 너무 길게하지 말고 dashboard 하나에 다양한 pane(요청) 개수를 너무 많이 넣지 말자

##### ready 지연 재현을 위한 테스트 #####
prometheus_host="ysoftman-prometheus.test.abc"
namespace="ysoftman-test"
cluster=""

# ready 응답 상태를 모니터링을 별도 터미널 창에서 띄워서 모니터링
# hwatch -n 1 "curl http://${prometheus_host}/-/ready"

# 요청 처리가 30초걸리는 것 여러번 요청을 날려도 응답은 느리지만 ready 응답은 1~2초내로 양호
# for ((i = 0; i < 40; i++)); do
#     # -g, --globoff 를 사용하면 {}[] 문자 인코딩 문제를 해결할 수 있다
#     curl -g "http://${prometheus_host}/api/v1/query_range?query=kube_pod_status_reason&start=2025-04-01T00:00:00Z&end=2025-04-17T00:00:00Z&step=1h" >/dev/null &
# done

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
# 30초가 넘어가는 slow query
# sum(kube_pod_status_reason{cluster="$cluster"}) by (reason)
zzz
)

# 다양한 빠른 요청을 여러번 날리면 ready 응답이 10~20초까지 느려진다.
IFS=$'\n'
for ((i = 0; i < 3; i++)); do
    for q in $queries; do
        # 주석 스킵
        [[ $q =~ ^# ]] && continue
        # 공백 제거
        # echo $q | sed "s/ //g"
        curl -g http://${prometheus_host}/api/v1/query_range?query="${q// /}&start=2025-04-01T00:00:00Z&end=2025-04-17T00:00:00Z&step=1h" >/dev/null &
    done
done
