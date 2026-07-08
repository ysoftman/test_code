# helm test

- minikube 환경 사용시

```bash
# 기존 minikube 삭제 후 새로 시작
minikube delete
minikube start
# ingress-nginx 활성화
minikube addons enable ingress
minikube addons enable ingress-dns
# minikube 선택
kubectx minikube
```

- colima k8s(k3s) 환경 사용시

```bash
# colima + k8s 시작
colima start --cpu 4 --memory 4 --kubernetes
# k8s 설정 리셋(필요시)
colima k8s reset
# colima 선택(colima 시작하면 자동 선택)
kubectx colima
```

- colima k8s 는 k3s 기반으로 traefik ingress controller 가 기본 내장되어 있어
  별도의 ingress controller 설치가 필요 없다.
  각 chart 의 values-ysoftman.yaml 에서 `ingressClassName: traefik` 을 사용한다.

```bash
# traefik 동작 확인 (kube-system 네임스페이스)
kubectl get pods -n kube-system -l app.kubernetes.io/name=traefik
kubectl get ingressclass
```

- ./argo-cd : argocd-cd 설치
- ./argocd-apps : argocd applications(app)들을 관리하는 app
- ./harbor : harbor app
- ./nginx : nginx app
