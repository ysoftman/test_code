# argocd-apps

argocd application(app)들을 통합 관리하기 위한 app of apps 패턴의 리소스입니다.

## argocd settings

- argocd UI 접속 > settings > repositories > connection method: via https, repository url: <https://github.com/ysoftman/test_code>
- 또는 argocd cli 사용시

```bash
argocd login --insecure argocd.ysoftman --grpc-web --username admin --password ysoftman
argocd repo add https://github.com/ysoftman/test_code
```

## argocd-apps 생성

- argocd UI 접속 > +NEW app
- application name: argocd-apps
- source
  - repository URL: "<https://github.com/ysoftman/test_code>" (위 argocd settings 에 등록되어 있어 리스트에 보인다.), GIT
  - revision : HEAD, Branches
  - path: helm/argocd-apps
- helm > values files: values-ysoftman.yaml
- 또는 argocd cli 사용시

```bash
argocd app create argocd-apps \
  --repo https://github.com/ysoftman/test_code \
  --revision HEAD \
  --path helm/argocd-apps \
  --dest-server https://kubernetes.default.svc \
  --sync-policy automated \
  --values values-ysoftman.yaml
```

> [!TIP]
>
> - helm values(.yaml) 수정후 템플릿 렌더링이 잘되는지 확인할 때
>
> ```bash
> cd charts/argocd-apps
> helm template . -f values-ysoftman.yaml
> ```

## 앱 중단 (리소스 정리)

- 하위 앱(Application)은 argocd-apps 가 만들기 때문에 하위 앱만 지우면 다음 sync 때 다시 생긴다.
- 그래서 argocd-apps 의 `<앱>.enabled` 를 parameter override 로 `false` 로 바꾸고 prune 한다.
- 하위 앱에는 `resources-finalizer` 가 있어 Application 이 지워지면 배포된 리소스(pod 등)도 같이 지워진다.
- argocd UI 접속 > argocd-apps > Details > Parameters > EDIT > `harbor.enabled` 를 `false` 로 저장 > SYNC > PRUNE 체크 > SYNCHRONIZE
- 또는 argocd cli 사용시

```bash
# -p 를 반복해서 여러 앱을 한 번에 끌 수 있다.
argocd app set argocd-apps -p harbor.enabled=false -p tikv.enabled=false
# argocd-apps 는 auto-prune 이 아니라서 빠진 Application 을 지우려면 --prune 으로 sync 해야 한다.
argocd app sync argocd-apps --prune
```

- 다시 띄울 때는 override 를 지우면 values-ysoftman.yaml 의 `enabled: true` 로 돌아가 자동 sync 된다.
- override 가 values 파일보다 우선하므로, override 가 남아 있으면 git 에서 `enabled` 를 바꿔도 반영되지 않는다.

```bash
argocd app unset argocd-apps -p harbor.enabled -p tikv.enabled
```

- 전부 내리려면 argocd-apps 를 지운다(기본 cascade 라 하위 앱과 리소스가 모두 지워진다). 다시 띄울 때는 위 argocd-apps 생성을 다시 한다.

```bash
argocd app delete argocd-apps
```

> [!NOTE]
>
> - StatefulSet 의 volumeClaimTemplates 로 생긴 PVC 는 argocd 관리 대상이 아니라 앱을 지워도 남는다(다시 띄우면 그 데이터를 그대로 쓴다).
> - 디스크까지 비우려면 `kubectl delete pvc -n <namespace> --all` 로 지운다.
