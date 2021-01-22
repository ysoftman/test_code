#!/bin/bash

# 현재 컨테이너 삭제
docker rm -f redis_cluster_proxy

# 현재 이미지 삭제
docker rmi -f ysoftman/redis_cluster_proxy

# dockerfile 로 이미지 빌드
docker build -f Dockerfile_redis_cluster_proxy -t ysoftman/redis_cluster_proxy .

# dockerhub 로그인
docker login

# dockerhub 로 푸시
docker push ysoftman/redis_cluster_proxy
