# backup_grafana

grafana dashbard 를 백업합니다.

## prerequsites

- api 사용을 위해 서비스 계정 생성 및 토큰 생성
- grafana > administration > service accounts > add service account, add service account token (no expiration) > 토큰 복사해서 auth.sh 설정

## usage

- backup dashboard

```bash
bash ./backup_grafana_dashboard.sh

# 저장소에 저장해두기
git add ./dashboards
git commit -m "backup dashboards"
git push
```

- restore dashboard

```bash
bash ./restore_grafana_dashboard.sh
```

- backup alert

```bash
bash ./backup_grafana_alert.sh

# 저장소에 저장해두기
git add ./alerts
git commit -m "backup alerts"
git push
```

- restore alert

```bash
# 필요시 folder 새로 생성이 필요한 경우
bash ./delete_grafana_alert.sh.sh

# 필요시 folder 새로 새성이 필요한 경우 스크립트내 folder 이름 변경 필요
bash ./restore_grafana_alert.sh
```

# 참고

- https://grafana.com/docs/grafana/latest/developers/http_api/dashboard/
- https://grafana.com/docs/grafana/latest/developers/http_api/folder_dashboard_search/
- https://grafana.com/docs/grafana/latest/developers/http_api/folder/
- https://grafana.com/docs/grafana/latest/developers/http_api/alerting_provisioning/
