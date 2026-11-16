# tikv

- 테스트를 위한 [tikv](https://github.com/tikv/tikv) 입니다.
- tikv 전용 chart([tikv-operator](https://github.com/tikv/tikv-operator))는 유지보수가 중단되어(README 에서 tidb-operator 사용 안내),
  upstream [pingcap/tidb-operator](https://github.com/pingcap/tidb-operator) chart 로 operator 를 설치하고
  `TidbCluster` 리소스에서 tidb 를 빼고 pd + tikv 만 띄운다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `kustomization.yaml`, `tidbcluster.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
  - `values-ysoftman.yaml`: tidb-operator chart values
  - `kustomization.yaml`: CRD(chart 에 없어 upstream manifest 를 버전 고정 url 로 참조) + `tidbcluster.yaml`
  - `tidbcluster.yaml`: pd 1개 + tikv 1개 클러스터 정의(tikv 버전은 `spec.version`)
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `tikv.source.targetRevision`).
  operator 버전을 올릴 때는 `kustomization.yaml` 의 CRD url 버전도 같이 바꾼다.
- CRD 가 커서 client-side apply 는 annotation 크기 제한으로 실패한다. argocd 는 `ServerSideApply=true`, 수동은 `--server-side` 를 쓴다.
- 수동 배포시

```bash
# operator
helm upgrade --install tikv tidb-operator \
--repo https://charts.pingcap.com/ \
--version v1.6.6 \
--namespace tikv \
--create-namespace \
--values values-ysoftman.yaml

# CRD + pd/tikv 클러스터
# 처음에는 CRD 가 등록되기 전이라 TidbCluster 가 "no matches for kind" 로 실패하므로 CRD 등록을 기다렸다가 한번 더 적용한다.
kubectl --context colima -n tikv apply --server-side -k .
kubectl --context colima wait --for=condition=Established crd/tidbclusters.pingcap.com
kubectl --context colima -n tikv apply --server-side -k .
```

- `tidbcluster.yaml` 의 `config` 는 operator 가 정규화한 toml 문자열 그대로 적는다.
  yaml map 이나 다른 모양의 toml 로 쓰면 operator 가 값을 다시 써서 필드 소유권을 가져가고,
  다음 server-side apply(argocd sync 포함)가 `.spec.tikv.config` conflict 로 실패한다.
  설정을 바꾼 뒤에는 `kubectl -n tikv diff --server-side -k .` 가 비어 있는지 확인한다.

- 동작 확인

```bash
kubectl --context colima -n tikv get tidbcluster,pods,pvc
# pd api 로 tikv store 상태(Up) 확인
kubectl --context colima -n tikv port-forward svc/tikv-pd 2379:2379
curl -s localhost:2379/pd/api/v1/stores
```

- 클러스터 안에서 접속할 pd 주소는 `tikv-pd.tikv.svc.cluster.local:2379` 이다(tikv client 는 pd 주소로 접속한다).
