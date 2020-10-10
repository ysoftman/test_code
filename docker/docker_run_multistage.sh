#!/bin/bash

# 로컬에서 이미지가 있지만 최신 이미지를 가져오려면 pull 해야 한다.
docker pull ysoftman/multistage

# 컨테이너 실행
# 로컬에 이미지가 없다면 자동으로 pull 받아온다.
docker run --name ysoftman_multistage -dit ysoftman/multistage
