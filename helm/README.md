# helm test

helm 설치 테스트

## local kubernetes

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
# colima 선택(colima 시작하면 자동 선택)
kubectx minikube
```

## helm repo

```bash
helm repo add dcgm-exporter https://nvidia.github.io/dcgm-exporter/helm-charts
helm repo add prometheus    https://prometheus-community.github.io/helm-charts
helm repo add bitnami-etcd  https://charts.bitnami.com/bitnami
helm repo add hashicorp     https://helm.releases.hashicorp.com
helm repo add k8tz          https://k8tz.github.io/k8tz/
helm repo add vector        https://helm.vector.dev
helm repo add argo          https://argoproj.github.io/argo-helm
helm repo add bitnami       https://charts.bitnami.com/bitnami
helm repo list
helm update
```

## argo-cd

```bash
helm fetch argo/argo-cd --version 8.0.14
tar zxvf argo-cd-8.0.14.tgz
mv argo-cd argo-cd-8.0.14

# 설치/업그레이드시
cd argo-cd argo-cd-8.0.14
helm upgrade --install argocd argo/argo-cd \
--namespace argocd \
--create-namespace \
--values values-ysoftman.yaml

# 서비스 연결시
# admin / ysoftman
kubectl port-forward service/argocd-server -n argocd 8080:443

# 또는 ingress 활성화 설정되어 있는 경우
# minikube tunnel 명령을 사용해야 외부에서 80, 443 포트로 직접 접근, 127.0.0.1로 포트 포워딩
# sudo vim /etc/hosts 수정
# 127.0.0.1  argocd.ysoftman.net
http://argocd.ysoftman.net

# helm 리스트
helm list -A

# 삭제시
helm uninstall argocd --namespace argocd
```
