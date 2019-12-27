#!/bin/bash
# http3 사용가능한 curl 빌드
# https://github.com/curl/curl/blob/master/docs/HTTP3.md

# quich 라이브러리 사용
# boringssl 빌드
git clone --recursive https://github.com/cloudflare/quiche
cd quiche/deps/boringssl
mkdir build
cd build
cmake -DCMAKE_POSITION_INDEPENDENT_CODE=on ..
make -j8
cd ..
mkdir -p .openssl/lib
cp build/crypto/libcrypto.a build/ssl/libssl.a .openssl/lib
ln -s $PWD/include .openssl

# quich 빌드
cd ../..
QUICHE_BSSL_PATH=$PWD/deps/boringssl cargo build --release --features pkg-config-meta

# cul 빌드
cd ..
git clone https://github.com/curl/curl
cd curl
./buildconf
# --disable-shared 로 바이너리 파일 하나로 작동되도록 한다.
# 하지만 quiche dynamic library 가 있어야 한다.
./configure --disable-shared LDFLAGS="-Wl,-rpath,$PWD/../quiche/target/release" --with-ssl=$PWD/../quiche/deps/boringssl/.openssl --with-quiche=$PWD/../quiche/target/release
make -j8

cp -fv ./src/curl ../curl-http3-mac
