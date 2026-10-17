# tekton

- [Tekton Pipelines](https://tekton.dev/) 를 upstream [cdf/tekton-pipeline](https://github.com/cdfoundation/tekton-helm-chart) chart 로 설치한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `tekton.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- chart 가 리소스를 `tekton-pipelines` namespace 에 설치한다.
- 수동 배포시

```bash
helm repo add cdf https://cdfoundation.github.io/tekton-helm-chart
helm repo update
helm upgrade --install tekton cdf/tekton-pipeline \
--namespace tekton-pipelines \
--create-namespace \
--values values-ysoftman.yaml
```

- 설치 확인

```bash
kubectl get pods -n tekton-pipelines
```
