FROM centos:7
RUN yum install -y sudo vim tar git rsync gcc gcc-c++ net-tools which iproute man-pages man setuptool ncurses-devel python-devel libevent-expat-devel bzip2-devel expat-devel pcre-devel zlib-devel libxml2-devel openldap-devel openssl-devel curl wget deltarpm
RUN yum groupinstall -y 'development tools'
# tsflags='' 옵션으로 man 재설치
RUN yum --setopt=tsflags='' reinstall -y man man-pages
RUN localedef -f UTF-8 -i ko_KR ko_KR.utf8 && ln -sf /usr/share/zoneinfo/Asia/Seoul /etc/localtime
RUN groupadd programmer && useradd -m -d /home/ysoftman -g programmer -p ysoftman ysoftman
RUN echo 'ysoftman      ALL=NOPASSWD: ALL, !/sbin/reboot, !/sbin/shutdown, !/sbin/halt, !/usr/bin/poweroff, !/usr/bin/halt' >> /etc/sudoers
# EPEL(Extra Packages for Enterprise Linux, Fedora 에서 제공되는 최신 패키지 저장소) 를 추가
RUN rpm -Uvh https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
USER ysoftman
COPY --chown=ysoftman:programmer .bashrc /home/ysoftman/.bashrc
COPY --chown=ysoftman:programmer .vimrc /home/ysoftman/.vimrc
# 환경설정 저장소 클론 받아 놓기
RUN mkdir -p /home/ysoftman/workspace \
&& cd /home/ysoftman/workspace \
&& git clone https://github.com/ysoftman/myenv \
&& cd /home/ysoftman/workspace/myenv \
&& bash ./installcommon.sh \
&& bash ./installconfig.sh \
&& zsh ./installprezto.zsh
# apache httpd 설치 스크립트 복사, 절대 경로로 명시해야 한다.
# symlink 파일은 복사가 안됨. 현재 위치 밖의 파일은 복사가 안됨
COPY --chown=ysoftman:programmer install_apache_httpd.sh /home/ysoftman/workspace
COPY --chown=ysoftman:programmer httpd.conf /home/ysoftman/httpd/conf/httpd.conf
# apache httpd 설치
RUN sudo chown -R ysoftman:programmer /home/ysoftman/workspace/install_apache_httpd.sh \
&& bash /home/ysoftman/workspace/install_apache_httpd.sh
RUN sudo chown -R ysoftman:programmer /home/ysoftman/httpd/conf/httpd.conf
EXPOSE 80
# 컨테이너 실행시 실행할 명령들
CMD sudo /home/ysoftman/httpd/bin/apachectl -k start; /bin/bash
