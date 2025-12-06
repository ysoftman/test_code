# argocd-apps

argocd application(app)들을 통합 관리하기 위한 app of apps 패턴의 리소스입니다.

## argocd settings

- argocd UI 접속 > settings > repositories
- connection method: via https
- repository url: <https://github.com/ysoftman/test_code>

## 참고로 일반적인 신규 app 생성시

- argocd UI 접속 > +NEW app
- source
  - repository URL: "<https://github.com/ysoftman/test_code>" (위 argocd settings 에 등록되어 있어 리스트에 보인다.), GIT
  - revision : HEAD, Branches
  - path: helm/charts/ysoftman-app1
