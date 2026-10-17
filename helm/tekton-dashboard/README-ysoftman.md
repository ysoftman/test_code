# tekton-dashboard

- [Tekton Dashboard](https://github.com/tektoncd/dashboard) 는 공식 helm chart 가 없어서 upstream release yaml 을 kustomize 로 설치한다.
- `kustomization.yaml` 이 github release 의 `release.yaml` 을 버전 고정 url 로 참조하고, traefik `ingress.yaml` 을 더한다.
  버전 올릴 때는 `kustomization.yaml` 의 url 버전만 바꾸면 된다.
- 리소스는 `tekton-pipelines` namespace 에 설치된다. tekton pipelines(`../tekton`) 가 먼저 설치되어 있어야 한다.
- 수동 배포시

```bash
kubectl apply -k .
```

- 설치 확인

```bash
kubectl get pods -n tekton-pipelines -l app.kubernetes.io/part-of=tekton-dashboard
# 브라우저: http://tekton-dashboard.ysoftman
```
