# Docker 17.05 부터 Dockerfile 하나에 여러개의 빌드 스테이지를 둘 수 있다.
# FROM 만큼 스테이지를 생성(이미지 빌드)하고
# 이전 스테이지의 결과를 다음 스테이즈로 복사해서 사용할 수 있다.
# 스테이지1) 소스 빌드 바이너리 --> 스테이지2) 바이너리만 포함된 이미지
# 와 같은 작업을 dockerfile 하나로 작성할 수 있어 편하다.
# https://docs.docker.com/develop/develop-images/multistage-build/


# Dockerfile
# buildstage 이름의 스테이지로 지정
FROM ubuntu:latest AS buildstage

ARG myarg1
WORKDIR /root
RUN if [ ${myarg1} = "ysoftman" ]; then \
    echo "test" | tee  output.txt; \
    else \
    echo "test2" | tee output.txt; \
    fi

CMD ["/bin/bash"]

##########

# 마지막 스테이지
FROM archlinux/base:latest

# buildstage 의 결과물을 현재 스테이지의 . 위치로 복사
COPY --from=buildstage /root/output.txt .

RUN echo "alias ll='ls -ahl'" > ~/.bashrc

# ARG 는 도커 빌드 타임동안만 유효하다.
ARG myarg1
# CMD 런타임에 인자를 전달 하기 위해서는 ENV 값을 이용해야 한다.
ENV aaa ${myarg1}
CMD echo ${aaa} > test.txt && /bin/bash


# multistage 를 빌드하면 최종 스테이지 말고는 
# 모두 <none> dangling 이미지가 생성되니 지워준다.
# docker image prune -f
