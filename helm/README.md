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

- colima k8s 환경 사용시

```bash
# colima + k8s 시작
colima start --cpu 4 --memory 4 --kubernetes
# k8s 설정 리셋(필요시)
colima k8s reset
# ingress nginx controller 설치
kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/main/deploy/static/provider/cloud/deploy.yaml
# colima 선택(colima 시작하면 자동 선택)
kubectx colima
```

- ./argo-cd : argocd-cd 설치
- ./argocd-apps : argocd applications(app)들을 관리하는 app
- ./harbor : harbor app
- ./nginx : nginx app
