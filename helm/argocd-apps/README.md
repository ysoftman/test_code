# argocd-apps

argocd application(app)들을 통합 관리하기 위한 app of apps 패턴의 리소스입니다.

## argocd settings

- argocd UI 접속 > settings > repositories > connection method: via https, repository url: <https://github.com/ysoftman/test_code>
- 또는 argocd cli 사용시

```bash
argocd login --insecure ysoftman.argocd --grpc-web --username admin --password ysoftman
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
  --dest-namespace argocd-apps \
  --sync-policy automated

```

> [!TIP]
>
> - helm values(.yaml) 수정후 템플릿 렌더링이 잘되는지 확인할 때
>
> ```bash
> cd charts/argocd-apps
> helm template . -f values-ysoftman.yaml
