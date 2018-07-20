#!/bin/bash

# nginx 에 필요한 모듈 설치
if [ $(uname) == 'Darwin' ]; then
    echo `uname`
elif [ $(uname) == 'Linux' ]; then
    echo `uname`
    yum --version
    if [ $? == 0 ]; then
        sudo yum install -y pcre-devel
        sudo yum install -y openssl-devel
    else
        sudo apt-get install -y libpcre3-dev
        sudo apt-get install -y libssl-dev
        sudo apt-get install -y libz-dev
    fi
fi


# echo 모듈
git clone https://github.com/openresty/echo-nginx-module.git
export ECHO_PWD=$(pwd)/echo-nginx-module

# 다운로드
wget https://nginx.org/download/nginx-1.14.0.tar.gz
# 압축 해제
tar zxvf nginx-1.14.0.tar.gz
cd nginx-1.14.0

# configure 수행 및 빌드 및 설치
./configure --with-http_ssl_module --with-http_v2_module --with-http_stub_status_module --add-module=$ECHO_PWD
make
sudo make install

# nginx 시작
#sudo /usr/local/nginx/sbin/nginx
# nginx 재시작
#sudo /usr/local/nginx/sbin/nginx -s reload
# nginx 정지
#sudo /usr/local/nginx/sbin/nginx -s stop
# nginx 설명
#sudo /usr/local/nginx/sbin/nginx -h

# 설정 변경하면서 테스트할때
sudo cp -v ./nginx.conf /usr/local/nginx/conf/nginx.conf && sudo /usr/local/nginx/sbin/nginx -s stop && sudo /usr/local/nginx/sbin/nginx  && curl http://localhost:8080/echo
