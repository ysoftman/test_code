#!/bin/bash

# 현재 컨테이너 삭제
docker rm -f ysoftman_centos_simple

# 현재 이미지 삭제
docker rmi -f ysoftman/centos_simple

# dockerfile 로 이미지 빌드
docker build -f centos_simple.dockerfile -t ysoftman/centos_simple .

# dockerhub 로그인
docker login

# dockerhub 로 푸시
docker push ysoftman/centos_simple
