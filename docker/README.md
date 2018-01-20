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

# (필요하다면) 컨테이너 전체 삭제
docker rm $(docker ps -aq)

# (필요하다면) 이미지 전체 삭제
docker rmi $(docker images -q)

# 컨테이너 실행(로컬에 이미지가 없다면 자동으로 pull 받아온다.)
docker run --name ysoftman_centos -dit -d ysoftman/centos

# 컨테이너 접속
docker exec -u root -it ysoftman_centos /bin/bash
```
