#!/bin/bash

echo `uname`
# nginx 에 필요한 모듈 설치
if [ $(uname) == 'Darwin' ]; then
    which openssl
    if [ $? != 0 ]; then
        brew install openssl
    fi
    # openssl 을 gcc(g++) 에서 사용는 경로에도 추가해준다.
    echo 'y' | ln -s /usr/local/opt/openssl/include/openssl /usr/local/include
    echo 'y' | ln -s /usr/local/opt/openssl/lib/libssl.1.0.0.dylib /usr/local/lib
    # --with-openssl=openssl_source 옵션을 주게 되더라도
    # openssl 내에서 Configure darwin64-x86_64-cc 옵션으로 설정해야 하는데
    # nginx configure 로 설정할 수 없다.
    # 그냥 brew 로 nginx 설치는 할 수 있지만 echo 모듈은 사용할 수 없다.
    brew install nginx
    # 설정은 vi /usr/local/etc/nginx/nginx.conf
    exit 0

elif [ $(uname) == 'Linux' ]; then
    yum --version
    if [ $? == 0 ]; then
        sudo yum install -y pcre-devel
        sudo yum install -y openssl-devel
    else
        sudo apt-get install -y libpcre3-dev
        sudo apt-get install -y libssl-dev
        sudo apt-get install -y libz-dev
    fi
else
    echo 'not support system'
    exit 1
fi

# echo 모듈
git clone https://github.com/openresty/echo-nginx-module.git
echo_module_path=$(pwd)/echo-nginx-module

# nginx
if [ ! -e nginx-1.14.0.tar.gz ]; then
    # 다운로드
    wget https://nginx.org/download/nginx-1.14.0.tar.gz
fi
if [ ! -d nginx-1.14.0 ]; then
    # 압축 해제
    tar zxvf nginx-1.14.0.tar.gz
fi
cd nginx-1.14.0

# configure 수행 및 빌드 및 설치
./configure --with-http_ssl_module --with-http_v2_module --with-http_stub_status_module --add-module=$echo_module_path
make -j8
sudo make install

# nginx 시작
#sudo /usr/local/nginx/sbin/nginx
# nginx 재시작
#sudo /usr/local/nginx/sbin/nginx -s reload
# nginx 정지
#sudo /usr/local/nginx/sbin/nginx -s stop
# nginx 설명
#sudo /usr/local/nginx/sbin/nginx -h

cd ..

# 설정 변경하면서 테스트할때
sudo cp -v ./nginx.conf /usr/local/nginx/conf/nginx.conf
sudo /usr/local/nginx/sbin/nginx -s stop
sudo /usr/local/nginx/sbin/nginx
curl -Lv http://localhost:8080/echo

