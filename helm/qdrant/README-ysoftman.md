# qdrant

- 테스트를 위한 [qdrant](https://github.com/qdrant/qdrant) 입니다. chart 는 upstream [qdrant/qdrant](https://github.com/qdrant/qdrant-helm) 를 사용한다.
- git 으로 관리하는 파일은 `values-ysoftman.yaml`, `README-ysoftman.md`, `.gitignore` 뿐이다.
- argocd 배포는 upstream helm repo 의 chart 를 직접 쓴다(버전은 `argocd-apps/values-ysoftman.yaml` 의 `qdrant.source.targetRevision`).
  버전 올릴 때는 그 값만 바꾸면 된다.
- 단일 인스턴스(replica 1) + PVC 2Gi 로 구성하고, 인증(api key)은 쓰지 않는다.
  chart 의 `apiKey: true` 는 랜덤 키를 만들어 argocd 에서 항상 OutOfSync 가 되므로 켜지 않는다.
- 수동 배포시

```bash
helm upgrade --install qdrant qdrant \
--repo https://qdrant.github.io/qdrant-helm \
--version 1.20.1 \
--namespace qdrant \
--create-namespace \
--values values-ysoftman.yaml
```

- 로컬에 ingress 도메인 접근을 위해

```bash
# /etc/hosts 에 추가
127.0.0.1 qdrant.ysoftman
```

- 접속
  - web ui: <http://qdrant.ysoftman/dashboard>
  - REST api: <http://qdrant.ysoftman> (클러스터 안: `http://qdrant.qdrant.svc.cluster.local:6333`)
  - gRPC: 클러스터 안 `qdrant.qdrant.svc.cluster.local:6334`

- 동작 확인

```bash
curl -s http://qdrant.ysoftman/healthz
curl -s http://qdrant.ysoftman/collections
```
