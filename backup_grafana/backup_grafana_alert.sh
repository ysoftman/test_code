#!/bin/bash
source ./auth.sh

uids=$(curl -s -X GET $host/api/v1/provisioning/alert-rules \
 -H "Content-Type: application/json" \
 -H "Authorization: Bearer $token" | jq -r '.[].uid')

mkdir -p alerts

backIFS=$IFS
IFS=$'\n'
for uid in $uids; do
    echo "backup $uid"
    curl -s -X GET $host/api/v1/provisioning/alert-rules/$uid \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" | jq > ./alerts/$uid.json
done
IFS=$backIFS
