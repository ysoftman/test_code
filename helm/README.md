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

## colima k8s 버전 업그레이드

- k8s 버전은 `~/.config/colima/default/colima.yaml` 의 `kubernetes.version` 에 고정되어 있다(k3s 릴리스 이름과 정확히 같아야 한다).
  설치 가능한 버전은 <https://update.k3s.io/v1-release/channels> 에서 확인한다.
- 이 값을 바꾸고 colima 를 재시작하면 colima 가 k3s 바이너리만 교체한다(reset 하지 않아 클러스터 데이터는 유지된다).
- minor 버전은 한 단계씩 올린다(예: 1.33 → 1.34 → 1.35). 다운그레이드는 지원하지 않으므로 먼저 백업한다.

```bash
# 현재 버전 확인
kubectl --context colima get nodes
# 제거 예정 API 를 쓰는 리소스가 있는지 확인(removed_release 가 올릴 버전 이하면 먼저 정리)
kubectl --context colima get --raw /metrics | rg apiserver_requested_deprecated_apis

# 백업: k3s 를 멈추고 sqlite DB 를 복사
colima ssh -- sudo systemctl stop k3s
colima ssh -- sudo cp -a /var/lib/rancher/k3s/server/db /var/lib/rancher/k3s/server/db.bak-v1.33.4

# colima.yaml 의 kubernetes.version 을 다음 minor 로 수정(예: v1.34.13+k3s1) 후 재시작
colima stop && colima start
# 노드가 Ready 이고 argocd 앱들이 Healthy 인지 확인한 뒤 다음 minor 로 반복
kubectl --context colima get nodes
kubectl --context colima -n argocd get applications

# 문제가 생기면 백업으로 복구: colima.yaml 의 version 을 이전 값으로 되돌리고 db 를 복원
colima ssh -- sudo systemctl stop k3s
colima ssh -- sudo rm -rf /var/lib/rancher/k3s/server/db
colima ssh -- sudo cp -a /var/lib/rancher/k3s/server/db.bak-v1.33.4 /var/lib/rancher/k3s/server/db
colima stop && colima start
```

- 프로비저닝
  - ./argo-cd 에서 argocd-cd 설치
  - ./argocd-apps 에서 argocd applications(app)들을 관리하는 app 설치
