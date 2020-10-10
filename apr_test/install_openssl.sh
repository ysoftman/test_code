#!/bin/bash
# openssl 설치
version="1.0.2k"
wget https://www.openssl.org/source/openssl-${version}.tar.gz
tar zxvf openssl-${version}.tar.gz
cd openssl-${version}
if [ $(uname) == 'Linux' ]; then
    ./config
elif [ $(uname) == 'Darwin' ]; then
    ./Configure darwin64-x86_64-cc
fi
make clean
make -j4 && sudo make install
cd ..

rm -rf openssl-${version} openssl-${version}.tar.gz
