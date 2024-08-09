#!/bin/bash
host=http://localhost:80
token=aaabbbccc
tag=ysoftman

uids=$(curl -s -X GET $host/api/search\?tag=$tag \
 -H "Content-Type: application/json" \
 -H "Authorization: Bearer $token" | jq -r '.[].uid')

mkdir -p dashboards

backIFS=$IFS
IFS=$'\n'
for uid in $uids; do
    echo "backup $uid"
    curl -s -X GET $host/api/dashboards/uid/$uid \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" > ./dashboards/$uid.json
done
IFS=$backIFS
