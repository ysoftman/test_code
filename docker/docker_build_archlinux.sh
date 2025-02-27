#!/bin/bash

# 현재 컨테이너 삭제
docker rm -f ysoftman_archlinux

# 현재 이미지 삭제
docker rmi -f ysoftman/archlinux

# dockerfile 로 이미지 빌드
docker build -f archlinux.dockerfile -t ysoftman/archlinux .

# dockerhub 로그인
docker login

# dockerhub 로 푸시
docker push ysoftman/archlinux
