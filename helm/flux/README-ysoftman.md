# flux

- 테스트를 위한 [Flux v2](https://github.com/fluxcd/flux2) GitOps 컨트롤러다.
  chart 는 공식 chart 가 아니라 upstream [fluxcd-community/flux2](https://github.com/fluxcd-community/helm-charts) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `podinfo-helmrelease.yaml`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `flux.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
  - community chart 는 flux 패치 릴리스 반영이 늦다. chart 2.20.0 은 flux v2.10.0 컨트롤러다(2026-11-25 기준 flux 최신은 v2.10.1).
- flux 는 argocd 와 달리 공식 웹 UI 없이 컨트롤러만 동작해 가볍고, flux cli 와 kubectl 로 사용한다.
- 컨트롤러는 `flux-system` namespace 에 설치한다(flux cli 기본 namespace).
- 컨트롤러 pod 에 chart 기본값으로 `prometheus.io/scrape` annotation 이 있어 prometheus 앱이 별도 설정 없이 수집한다.

## argocd 와 같이 쓸 때 주의

- **역할 분리**: argocd 는 flux 컨트롤러 설치/업그레이드만 맡고, flux 는 직접 넣은 `HelmRelease`/`Kustomization` 이 가리키는 앱만 배포한다.
- **같은 리소스를 argocd 와 flux 가 함께 관리하면 안 된다.**
  argocd 는 selfHeal 로 git 상태에, flux 는 interval 마다 자기 소스 상태에 맞추므로 서로의 변경을 계속 되돌린다.
  예를 들어 harbor 를 argocd Application 과 flux HelmRelease 로 동시에 배포하면 sync 와 reconcile 이 끝없이 반복된다.
  한 앱(리소스)은 반드시 한 도구만 관리한다.
- **`flux install`, `flux bootstrap` 을 실행하지 않는다.**
  flux 컨트롤러는 이미 argocd(flux 앱)가 관리하므로, cli 로 다시 설치하면 argocd 리소스를 덮어쓰고 selfHeal 이 되돌리면서 충돌한다.
  `flux bootstrap` 은 이 저장소에 flux 매니페스트를 커밋/push 하기까지 한다.
- argocd 는 자기가 만든 리소스(tracking annotation)만 앱에 표시하므로, flux 가 만든 리소스는 argocd UI 에 보이지 않는다.
  flux cli 나 kubectl 로 확인한다.
- chart 의 `flux check --pre` Job 은 helm `pre-install` hook 인데, argocd 는 install/upgrade 를 구분하지 않아 PreSync hook 으로 sync 때마다 실행한다.

### argocd 와 helm 처리 방식 차이

| | argocd | flux |
|---|---|---|
| helm 배포 | `helm template` 렌더링 후 apply. helm release 없음(`helm list` 에 안 나옴) | Helm SDK 로 실제 install/upgrade. release secret 생성(`helm list` 에 나옴) |
| `lookup`, helm hook | `lookup` 미지원, hook 은 argocd hook 으로 일부만 매핑 | helm 과 동일하게 동작 |
| 랜덤 secret 생성 chart | 렌더링마다 값이 바뀌어 항상 OutOfSync | chart/values 가 바뀔 때만 upgrade 해서 문제 없음 |
| release secret 1MB 제한 | 해당 없음 | helm 과 동일하게 적용 |

## flux cli

- cli 는 선택이다. 컨트롤러는 클러스터에서 동작하고, cli 는 상태 조회/즉시 reconcile 용 클라이언트다.
- ⚠️ homebrew core 의 `flux` 는 InfluxData 의 Flux 언어라 다른 패키지다. 반드시 fluxcd tap 으로 설치한다.

```bash
brew install fluxcd/tap/flux
flux version
```

- 자주 쓰는 명령

```bash
# 컨트롤러 상태 확인
flux check
# 모든 flux 리소스 상태
flux get all -A
# interval 을 기다리지 않고 바로 반영
flux reconcile helmrelease podinfo -n flux-system --with-source
# 컨트롤러 로그
flux logs -A --follow
```

- cli 없이 kubectl 로도 확인할 수 있다.

```bash
kubectl get pods -n flux-system
kubectl get ocirepositories,helmreleases -A
```

## podinfo 예제

- `podinfo-helmrelease.yaml` 은 flux 동작 확인용 예제로, argocd 가 아니라 kubectl 로 직접 넣는다.
  argocd 의 flux 앱은 이 디렉토리에서 values 파일만 참조하므로 이 파일을 배포하지 않는다.
- `OCIRepository` 가 `oci://ghcr.io/stefanprodan/charts/podinfo` chart 를 받고, `HelmRelease` 를 보고 helm-controller 가 podinfo namespace 에 helm install 한다.

```bash
kubectl apply -f podinfo-helmrelease.yaml
flux get sources oci -n flux-system
flux get helmreleases -n flux-system
# flux 가 만든 실제 helm release
helm list -n flux-system

# 확인(values 로 넣은 ui.message 가 나온다)
kubectl -n podinfo port-forward svc/podinfo 9898:9898
curl -s localhost:9898 | rg message

# 삭제(HelmRelease 를 지우면 flux 가 helm uninstall 한다, namespace 는 남는다)
kubectl delete -f podinfo-helmrelease.yaml
kubectl delete ns podinfo
```

## 수동 배포시

- argocd 없이 설치할 때만 사용한다(argocd 의 flux 앱과 동시에 쓰지 않는다).

```bash
helm upgrade --install flux flux2 \
--repo https://fluxcd-community.github.io/helm-charts \
--version 2.20.0 \
--namespace flux-system \
--create-namespace \
--values values-ysoftman.yaml
```
