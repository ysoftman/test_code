# backup_grafana

grafana dashbard 를 백업합니다.

## prerequsites

- api 사용을 위해 서비스 계정 생성 및 토큰 생성
- grafana > administration > service accounts > add service account, add service account token (no expiration) > 토큰 복사해두기

## usage

- backup

```bash
bash ./backup_grafana_dashboard.sh

# 저장소에 저장해두기
git add ./dashboards
git commit -m "backup dashboards"
git push
```

- restore

```bash
bash ./restore_grafana_dashboard.sh
```
