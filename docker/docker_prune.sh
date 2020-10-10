#!/bin/bash

# dangling(unused) 이미지들 모두 삭제
docker image prune -f

# 중지된 컨테이너들 모두 삭제
docker container prune -f

# (필요하다면) 컨테이너 전체 삭제
#docker rm $(docker ps -aq)

# (필요하다면) 이미지 전체 삭제
#docker rmi $(docker images -q)
