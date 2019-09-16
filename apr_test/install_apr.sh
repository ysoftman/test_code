#!/bin/bash

# apche httpd
# libapreq 설치시 apxs(apxs - APache eXtenSion tool) 실행파일이 필요하다.
httpdver="2.2.34"
wget https://archive.apache.org/dist/httpd/httpd-${httpdver}.tar.gz
tar zxvf httpd-${httpdver}.tar.gz
cd httpd-${httpdver}
./configure --prefix="${HOME}/workspace/httpd-${httpdver}" --with-mpm-prefork
make -j8 && make install
cd ..
rm -rf httpd-${httpdver}.tar.gz httpd-${httpdver}

# libapreq2 설치
libapreq2ver="2.13"
wget http://apache.mirror.cdnetworks.com//httpd/libapreq/libapreq2-${libapreq2ver}.tar.gz
tar zxvf libapreq2-${libapreq2ver}.tar.gz
cd libapreq2-${libapreq2ver}
./configure --prefix="${HOME}/workspace/libapreq2-${libapreq2ver}" --with-apache2-apxs=${HOME}/workspace/httpd-${httpdver}/bin/apxs
make -j8 && make install
cd ..
rm -rf libapreq2-${libapreq2ver}.tar.gz libapreq2-${libapreq2ver}

# apr 설치 방법2
aprver="1.6.5"
wget http://apache.mirror.cdnetworks.com/apr/apr-${aprver}.tar.gz
tar zxvf apr-${aprver}.tar.gz
cd apr-${aprver}
./configure --prefix="${HOME}/workspace/apr-${aprver}"
make -j8 && make install
cd ..
rm -rf apr-${aprver}.tar.gz apr-${aprver} 

# apr-util 설치
aprutilver="1.6.1"
wget http://apache.mirror.cdnetworks.com//apr/apr-util-${aprutilver}.tar.gz
tar zxvf apr-util-${aprutilver}.tar.gz
cd apr-util-${aprutilver}
./configure --prefix="${HOME}/workspace/apr-${aprver}" --with-apr="${HOME}/workspace/apr-${aprver}/bin/apr-1-config"
# make 시 expat.h 가 없어 에러가 난다면 
# centos : yum install expat-devel
# ubuntu : apt-get install libexpat1-dev
make -j8 && make install
cd ..
rm -rf apr-util-${aprutilver}.tar.gz apr-util-${aprutilver}
