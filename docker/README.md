# ysoftman docker

## 이미지 생성 및 푸시

```bash
# dockerfile 로 이미지 빌드
docker build -f Dockerfile -t ysoftman/centos .

# dockerhub 로그인
docker login

# dockerhub 로 푸시
docker push ysoftman/centos
```

## 이미지 사용하기

```bash
# 이미지 확인
docker images

# 컨테이너 상태 확인
docker ps -a

# dangling(unused) 이미지들 모두 삭제
docker image prune

# 중지된 컨테이너들 모두 삭제
docker container prune

# (필요하다면) 컨테이너 전체 삭제
docker rm $(docker ps -aq)

# (필요하다면) 이미지 전체 삭제
docker rmi $(docker images -q)

# 로컬에서 이미지가 있지만 최신 이미지를 가져오려면 pull 해야 한다.
docker pull ysoftman/centos

# 컨테이너 실행
# 로컬에 이미지가 없다면 자동으로 pull 받아온다.
# -v 에  명시한 경로의 디렉토리가 없다면 host, guest 모두 자동 생성된다.
docker run --name ysoftman_centos --hostname ysoftman_centos -p 10000:80 -v ${HOME}/workspace/from_guest:/home/ysoftman/workspace/to_host -dit -d ysoftman/centos

# 컨테이너 접속
docker exec -u root -it ysoftman_centos /bin/bash

# 또는
docker exec -u ysoftman -it ysoftman_centos /bin/bash
```
