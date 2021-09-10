# k8s test

kubernetes(k8s) 관련 테스트

```bash
kubectl delete -f ysoftman-pod-test.yaml; kubectl apply -f ysoftman-pod-test.yaml
kubectl apply -f ysoftman-cronjob-test.yaml
```

k8s pod/container 별 디스크 사용량 파악 스크립트

```bash
bash ./get_container_disk_usage.sh
```
