#!/bin/bash
# k8s node 별 디스크 사용량 파악 스크립트
# prerequisite : kubectl, jq


calc_unit="/(1024*1024*1024)"
nodes=$(kubectl get nodes | grep -vi name | awk '{print $1}')
for node in ${nodes}; do
    echo "[node:${node}]"
    temp+=$(kubectl get --raw /api/v1/nodes/${node}/proxy/stats/summary | jq '.node | { "node": .nodeName, "fs_capacityBytes(GiB)": ((.fs.capacityBytes'${calc_unit}')), "fs_availableBytes(GiB)": ((.fs.availableBytes'${calc_unit}')), "fs_usedBytes(GiB)": ((.fs.usedBytes'${calc_unit}')), "Use(%)": (( (.fs.usedBytes/.fs.capacityBytes)*100 )) }')
done
# echo $temp | jq -s 'sort_by(.fs_usedBytes)'
echo $temp | jq
