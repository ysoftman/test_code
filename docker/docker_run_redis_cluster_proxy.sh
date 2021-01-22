#!/bin/bash

# 로컬에서 이미지가 있지만 최신 이미지를 가져오려면 pull 해야 한다.
docker pull ysoftman/redis_cluster_proxy

# 컨테이너 실행
# 로컬에 이미지가 없다면 자동으로 pull 받아온다.
# -v 에  명시한 경로의 디렉토리가 없다면 host, guest 모두 자동 생성된다.
docker run --name ysoftman_redis_cluster_proxy --hostname ysoftman_redis_cluster_proxy -dit -d ysoftman/redis_cluster_proxy
