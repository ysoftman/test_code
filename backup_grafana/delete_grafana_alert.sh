#!/bin/bash
source ./auth.sh

uids=$(curl -s -X GET $host/api/v1/provisioning/alert-rules \
 -H "Content-Type: application/json" \
 -H "Authorization: Bearer $token" | jq -r '.[].uid')

backIFS=$IFS
IFS=$'\n'
for uid in $uids; do
    echo "deleting $uid"
    curl -s -X DELETE $host/api/v1/provisioning/alert-rules/$uid \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token"
    echo ""
done
IFS=$backIFS
