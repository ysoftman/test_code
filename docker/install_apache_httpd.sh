#!/bin/bash
# 리눅스용 Apache Httpd 설치전 필요한 프로그램 설치
sudo yum install -y expat-devel pcre-devel zlib-devel libxml2-devel openldap-devel openssl-devel

# install apr
cd ~
wget http://apache.mirror.cdnetworks.com/apr/apr-1.6.3.tar.gz
tar zxvf apr-1.6.3.tar.gz
cd apr-1.6.3
./configure --prefix=/home/ysoftman/apr
make && make install


# install apr-util
cd ~
wget http://apache.mirror.cdnetworks.com/apr/apr-util-1.6.1.tar.gz
tar zxvf apr-util-1.6.1.tar.gz
cd apr-util-1.6.1
./configure --prefix=/home/ysoftman/apr-util --with-apr=/home/ysoftman/apr
make && make install


# install apache http 2.4
cd ~
wget http://apache.mirror.cdnetworks.com/httpd/httpd-2.4.29.tar.gz
tar zxvf httpd-2.4.29.tar.gz
cd httpd-2.4.29
# prefix 를 명시하지 않으면 디폴트는 /usr/local/apache2
./configure --prefix=/home/ysoftman/httpd --with-apr=/home/ysoftman/apr --with-apr-util=/home/ysoftman/apr-util --with-mpm=prefork --enable-mods-shared="rewrite alias dir"
make && make install
