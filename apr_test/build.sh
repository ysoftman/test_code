#!/bin/bash
# build
aprver="1.6.5"
libapreq2ver="2.13"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/workspace/apr-${aprver}/lib:${HOME}/workspace/libapreq2-${libapreq2ver}/lib:
g++ -O2 -g -fPIC apr_test.cpp -o aprtest -std=c++11 \
-I${HOME}/workspace/apr-${aprver}/include/apr-1 \
-I${HOME}/workspace/libapreq2-${libapreq2ver}/include/apreq2 \
-I/usr/local/ssl/include \
-L${HOME}/workspace/apr-${aprver}/lib \
-L${HOME}/workspace/libapreq2-${libapreq2ver}/lib \
-L/usr/local/ssl/lib \
-lapr-1 \
-lapreq2 \
-lssl \
-lcrypto \
-ldl

# aprtest 실행 환경 설정필요
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/workspace/apr-${aprver}/lib:${HOME}/workspace/libapreq2-${libapreq2ver}/lib:"
