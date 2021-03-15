FROM centos:7

RUN echo $PATH
RUN yum install -y sudo vim
RUN mkdir -p /ysoftman && cd /ysoftman && echo 'echo ysoftman' > ysoftman.sh
RUN echo "PATH=${PATH}:/ysoftman" >> ${HOME}/.bashrc
RUN cat ${HOME}/.bashrc
# source 현재 쉘에 PATH 환경변수를 새로 반영해도 현재 RUN에서만 유효하다.
# RUN source ${HOME}/.bashrc && echo $PATH
# 위 RUN source 내용은 현재 RUN 에 반영되지 않는다.
RUN echo $PATH
# dockerfile 처리중 환경변수 반영은 ENV 를 사용해야 한다.
ENV PATH=${PATH}:/ysoftman
RUN ls -ahl /ysoftman/
RUN echo $PATH && cd ${HOME} && bash ysoftman.sh


#####


# 기본 root 계정으로 실행한다.
RUN whoami
# root 의 HOME 디렉토리인 /root 가 찍한다.
RUN echo ${HOME}

# ENV 에선 HOME 변수가 설정된것이 없다.
ENV mypath="${HOME}:aa"
# :aa 로 찍힌다.
RUN echo ${mypath}

# HOME 환경변수를 별도로 설정해야 한다.
ENV HOME="/root"
ENV mypath="${HOME}:aa"
# /root:aa 로 찍힌다.
RUN echo ${mypath}
