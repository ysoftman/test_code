# vector

- vector 차트 새로 받을때(버전 업데이트시)

```bash
helm repo add vector https://helm.vector.dev
helm repo update
helm pull vector/vector
tar zxvf vector-0.48.0.tgz -C ../
```

- 수동 배포시

```bash
helm upgrade --install vector . \
--namespace vector \
--create-namespace \
--values values.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# sudo vim /etc/hosts 수정
# 127.0.0.1  ysoftman.vector
http://ysoftman.vector
```

- vector 처리 확인

```bash
kubectl exec -it $(kubectl get pod --no-headers -n vector | awk '{print $1}') -- vector top
```
