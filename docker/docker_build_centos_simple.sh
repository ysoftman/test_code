#!/bin/bash

# 현재 컨테이너 삭제
docker rm -f ysoftman_centos_simple

# 현재 이미지 삭제
docker rmi -f ysoftman/centos_simple

# dockerfile 로 이미지 빌드
docker build -f Dockerfile_centos_simple -t ysoftman/centos_simple .
