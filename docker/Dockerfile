FROM centos:latest
RUN yum install -y sudo vim tar git rsync gcc gcc-c++ net-tools which iproute man-pages man setuptool ncurses-devel python-devel libevent-expat-devel bzip2-devel expat-devel pcre-devel zlib-devel libxml2-devel openldap-devel openssl-devel curl wget
RUN yum groupinstall -y 'development tools'
RUN localedef -f UTF-8 -i ko_KR ko_KR.utf8 && ln -sf /usr/share/zoneinfo/Asia/Seoul /etc/localtime
RUN groupadd programmer && useradd -d /home/ysoftman -g programmer -p ysoftman ysoftman
RUN echo 'ysoftman      ALL=NOPASSWD: ALL, !/sbin/reboot, !/sbin/shutdown, !/sbin/halt, !/usr/bin/poweroff, !/usr/bin/halt' >> /etc/sudoers
USER ysoftman
# 환경설정 저장소 클론 받아 놓기
RUN mkdir -p /home/ysoftman/workspace && cd /home/ysoftman/workspace && git clone https://github.com/ysoftman/myenv && cd /home/ysoftman/workspace/myenv/ && bash ./installconfig.sh && bash ./installvimplugin.sh
# apache httpd 설치 스크립트 복사, 절대 경로로 명시해야 한다.
COPY install_apache_httpd.sh /home/ysoftman/workspace
# apache httpd 설치
RUN bash /home/ysoftman/workspace/install_apache_httpd.sh
COPY httpd.conf /home/ysoftman/httpd/conf/httpd.conf
# 컨테이너 실행시 실행할 명령들
CMD sudo /home/ysoftman/httpd/bin/apachectl -k start; /bin/bash
