#!/bin/bash
host=http://localhost:80
token=aaabbbccc

backIFS=$IFS
IFS=$'\n'
for fname in ./dashboards/*; do
    echo "restoring $(jq .dashboard.title $fname)"
    curl -s -X POST $host/api/dashboards/db \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" \
     -d "$(jq 'del(.meta)|del(.dashboard.id)' $fname)"
done
IFS=$backIFS
