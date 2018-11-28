#!/bin/bash

# apr 설치 방법1
# apche httpd 설치하면 생성되는 apr 사용
# wget http://mirror.apache-kr.org//httpd/httpd-2.2.34.tar.gz
# tar zxvf httpd-2.2.34.tar.gz
# cd httpd-2.2.34
# ./configure --prefix="${HOME}/workspace/httpd" --with-mpm-prefork
# make && make install
# 빌드
# g++ -O2 -g -fPIC apr_test.cpp -o aprtest -I${HOME}/workspace/httpd/include -I/usr/local/ssl/include -L${HOME}/workspace/httpd/lib -L/usr/local/ssl/lib -lapr-1 -lssl -lcrypto -ldl


# apr 설치 방법2
aprver="1.6.5"
wget http://apache.mirror.cdnetworks.com/apr/apr-${aprver}.tar.gz
tar zxvf apr-${aprver}.tar.gz
cd apr-${aprver}
./configure --prefix="${HOME}/workspace/apr"
make && make install
cd ..
rm -rf apr-${aprver}.tar.gz apr-${aprver} 

#apr-util 설치
aprutilver="1.6.1"
wget http://apache.mirror.cdnetworks.com//apr/apr-util-${aprutilver}.tar.gz
tar zxvf apr-util-${aprutilver}.tar.gz
cd apr-util-${aprutilver}
./configure --prefix="${HOME}/workspace/apr" --with-apr="${HOME}/workspace/apr/bin/apr-1-config"
# make 시 expat.h 가 없어 에러가 난다면 
# centos : yum install expat-devel
# ubuntu : apt-get install libexpat1-dev
make && make install
cd ..
rm -rf apr-util-${aprutilver}.tar.gz apr-util-${aprutilver}

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/workspace/apr/lib:
# g++ -O2 -g -fPIC apr_test.cpp -o aprtest -I${HOME}/workspace/apr/include/apr-1 -I/usr/local/ssl/include -L${HOME}/workspace/apr/lib -L/usr/local/ssl/lib -lapr-1 -lssl -lcrypto -ldl