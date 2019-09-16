#!/bin/bash
# build
aprver="1.6.5"
libapreq2ver="2.13"
export LD_LIBRARY_PATH=${HOME}/workspace/apr-${aprver}/lib:${HOME}/workspace/libapreq2-${libapreq2ver}/lib:
g++ -O2 -g -fPIC apr_test.cpp -o aprtest -std=c++11 \
-I${HOME}/workspace/apr-${aprver}/include/apr-1 \
-I${HOME}/workspace/libapreq2-${libapreq2ver}/include/apreq2 \
-I/usr/local/ssl/include \
-L${HOME}/workspace/apr-${aprver}/lib \
-L${HOME}/workspace/libapreq2-${libapreq2ver}/lib \
-L/usr/local/ssl/lib \
-lapr-1 \
-laprutil-1 \
-lapreq2 \
-lssl \
-lcrypto \
-ldl


# ld.so.conf.d shared library 경로 파일 생성
echo "${HOME}/workspace/apr-${aprver}/lib
${HOME}/workspace/libapreq2-${libapreq2ver}/lib
" > libapr.conf
sudo mv -v libapr.conf /etc/ld.so.conf.d/libapr.conf
sudo /sbin/ldconfig
