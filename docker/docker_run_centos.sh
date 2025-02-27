#!/bin/bash

# 로컬에서 이미지가 있지만 최신 이미지를 가져오려면 pull 해야 한다.
docker pull ysoftman/centos

# 컨테이너 실행
# 로컬에 이미지가 없다면 자동으로 pull 받아온다.
# -v 에  명시한 경로의 디렉토리가 없다면 host, guest 모두 자동 생성된다.
docker run --name ysoftman_centos --hostname ysoftman_centos -p 10000:80 -v ${PWD}/from_guest:/home/ysoftman/workspace/to_host -dit -d ysoftman/centos

# ysoftman 컨테이너를 ysoftman/centos:dev 이미지로 저장하기
# docker commit ysoftman ysoftman/centos:dev

#  기존이미지 ->  새로운 이름의 이미지 생성해서 푸시하기
# docker tag ysoftman/centos:latest ysoftman/centos-rename:test
# docker push ysoftman/centos-rename:test
