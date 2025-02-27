#!/bin/bash

# 현재 컨테이너 삭제
docker rm -f ysoftman_multistage

# 현재 이미지 삭제
docker rmi -f ysoftman/multistage

# dockerfile 로 이미지 빌드
docker build \
    --build-arg myarg1="ysoftman" \
    -f multistage.dockerfile \
    -t ysoftman/multistage .

# multistage 를 빌드하면 최종 스테이지 말고는
# 모두 <none> dangling 이미지가 생성되니 지워준다.
docker image prune -f
