FROM centos:latest
RUN yum install -y sudo tar git rsync gcc gcc-c++ net-tools which iproute man-pages man setuptool ncurses-devel python-devel libevent-expat-devel bzip2-devel
RUN yum groupinstall -y 'development tools'
RUN localedef -f UTF-8 -i ko_KR ko_KR.utf8
