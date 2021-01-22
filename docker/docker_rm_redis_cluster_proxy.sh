#!/bin/bash
docker rm -f ysoftman_redis_cluster_proxy

# multistage 를 빌드하면 최종 스테이지 말고는 
# 모두 <none> dangling 이미지가 생성되니 지워준다.
docker image prune -f
