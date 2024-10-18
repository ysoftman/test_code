#!/bin/bash
source ./auth.sh

folderUIDs=()
for fname in ./alerts/*; do
    folderUID=$(jq -r '.folderUID' $fname)
    folderUIDs+=("$folderUID")
done

# 백업된 alert  folderUID 생성
for fuid in "${folderUIDs[@]}"; do
    echo "creating folder(uid) $fuid"
    curl -s -X POST $host/api/folders \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" \
     -d "{
         \"uid\": \"${fuid}\",
         \"title\": \"${fuid}\"
     }"
    echo ""
done

backIFS=$IFS
IFS=$'\n'
for fname in ./alerts/*; do
    echo "restoring $(jq .title $fname)"
    curl -s -X POST $host/api/v1/provisioning/alert-rules \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" \
     -d "$(jq 'del(.id)' $fname)"
    echo ""
done
IFS=$backIFS
