# argo-cd

- argo-cd 설치

```bash
helm repo add argo https://argoproj.github.io/argo-helm
helm repo list
helm update
helm fetch argo/argo-cd --version 8.0.14
tar zxvf argo-cd-8.0.14.tgz

# 설치/업그레이드시
cd argo-cd
helm upgrade --install argocd . \
--namespace argocd \
--create-namespace \
--values values-ysoftman.yaml

# 서비스 연결시
# admin / ysoftman
kubectl port-forward service/argocd-server -n argocd 8080:443

# 또는 ingress 활성화 설정되어 있는 경우
# minikube tunnel 명령을 사용해야 외부에서 80, 443 포트로 직접 접근, 127.0.0.1로 포트 포워딩
# sudo vim /etc/hosts 수정
# 127.0.0.1  ysoftman.argocd
http://ysoftman.argocd

# helm 리스트
helm list -A

# 삭제시
helm uninstall argocd --namespace argocd
```

- colima 환경에서 argocd-dex-server runAsNonRoot 에러 발생하면, deployment > spec > template > spec > 0(argocd-dex) > securityContext > runAsNonRoot: false 로 변경
