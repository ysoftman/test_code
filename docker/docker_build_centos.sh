#!/bin/bash

# 현재 컨테이너 삭제
docker rm -f ysoftman_centos

# 현재 이미지 삭제
docker rmi -f ysoftman/centos

# dockerfile 로 이미지 빌드
docker build -f Dockerfile_centos -t ysoftman/centos .

# dockerhub 로그인
docker login

# dockerhub 로 푸시
docker push ysoftman/centos
