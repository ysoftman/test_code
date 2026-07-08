# argo-cd

- chart 원본 파일(Chart.yaml, templates/, charts/, values.yaml 등 tgz 압축 해제 결과물)은
  `.gitignore` 로 커밋 대상에서 제외되어 있다.
  git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- 따라서 클론 직후에는 chart 원본이 없으므로 아래처럼 helm fetch 로 받아서 압축을 풀어야 한다.

```bash
# helm(상위) 디렉토리에서 실행하면 argo-cd/ 에 chart 파일이 풀리면서 기존 커스텀 파일과 병합된다.
cd ..
helm repo add argo https://argoproj.github.io/argo-helm
helm repo update
helm fetch argo/argo-cd --version 10.1.2
tar zxvf argo-cd-10.1.2.tgz
rm argo-cd-10.1.2.tgz
```

- argo-cd 설치

```bash
# 설치/업그레이드시
cd argo-cd
helm upgrade --install argocd . \
--namespace argocd \
--create-namespace \
--values ../values-ysoftman.yaml

# 서비스 연결시
# admin / ysoftman
kubectl port-forward service/argocd-server -n argocd 8080:443

# 또는 ingress 활성화 설정되어 있는 경우
# minikube tunnel 명령을 사용해야 외부에서 80, 443 포트로 직접 접근, 127.0.0.1로 포트 포워딩
# sudo vim /etc/hosts 수정
# 127.0.0.1  argocd.ysoftman
http://argocd.ysoftman

# helm 리스트
helm list -A

# 삭제시
helm uninstall argocd --namespace argocd
```

- colima 환경에서 argocd-dex-server runAsNonRoot 에러 발생하면, deployment > spec > template > spec > 0(argocd-dex) > securityContext > runAsNonRoot: false 로 변경
- argocd notification - slack 연동<https://argo-cd.readthedocs.io/en/stable/operator-manual/notifications/services/slack/>

```bash
# 기본 트리거 설정을 다음과 같이 설치하면 configmap 에 추가된다.
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/notifications_catalog/install.yaml

# argocd-notifications-secret 에 슬랙 토큰을 추가한다.
# 참고로 stringData 로 저장하면 data 로 바뀌고 값은 base64 인코딩된다.
kind: Secret
stringData:
  slack-token: <slack oauth access token>

# argocd-notifications-cm 슬랙 사용시 위에서 저장한 시크릿을 토큰으로 참조하도록 한다.
kind: ConfigMap
data:
  context: |
    argocdUrl: https://argocd.ysoftman
  service.slack: |
    token: $slack-token

# 알림을 발생한 앱에 annotations 설정
apiVersion: argoproj.io/v1alpha1
kind: Application
metadata:
  annotations:
    notifications.argoproj.io/subscribe.on-sync-running.slack: my_channel
    notifications.argoproj.io/subscribe.on-sync-succeeded.slack: my_channel
```
