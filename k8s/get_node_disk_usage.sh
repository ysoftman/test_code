#!/bin/bash
# k8s node 별 디스크 사용량 파악 스크립트
# prerequisite : kubectl, jq

nodes=$(kubectl get nodes | grep -vi name | awk '{print $1}')
for node in ${nodes}; do
    echo "[node:${node}]"
    temp+=$(kubectl get --raw /api/v1/nodes/${node}/proxy/stats/summary | jq '.node | {"node": .nodeName, "fs_usedBytes": .fs.usedBytes, "runtime_imageFs_usedBytes": .runtime.imageFs.usedBytes}')
done
echo $temp | jq -s 'sort_by(.fs_usedBytes)'
