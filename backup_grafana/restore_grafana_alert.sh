#!/bin/bash
host=http://localhost:80
token=aaabbbccc

# 백업된 alert  folderUID 생성
folders="sample-folder sample-worker-folder"
for folder_name in $folders; do
    echo "creating folder $folder_name"
    curl -s -X POST $host/api/folders \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $token" \
     -d "{
         \"uid\": \"${folder_name}-uid\",
         \"title\": \"${folder_name}\"
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
