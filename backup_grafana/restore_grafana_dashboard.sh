#!/bin/bash
host=http://localhost:80
token=aaabbbccc

backIFS=$IFS
IFS=$'\n'
for fname in ./dashboards/*; do
    echo "restoring $(jq .dashboard.title $fname)"
    # 백업 json 중 meta object 가 있으면 에러가 발생해 삭제해야 한다.
    # 새로 추가되는 경우 dashboard.id 값이  있으면 업데이트 시도로 에러가 발생해 삭제해야 한다.
    curl -s -X POST $host/api/dashboards/db \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" \
     -d "$(jq 'del(.meta)|del(.dashboard.id)' $fname)"
done
IFS=$backIFS
