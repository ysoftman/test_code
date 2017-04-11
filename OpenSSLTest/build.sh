#!/bin/bash
# wget https://www.openssl.org/source/openssl-1.0.2k.tar.gz
# tar zxvf openssl-1.0.2k.tar.gz
# cd openssl-1.0.2k
# ./config --prefix=/home/ysoftman/workspace/test_code/OpenSSLTest/openssl-1.0.2
# make && make install

rm a.out *.o core*
g++ -g -fPIC -c Cryptography.cpp OpenSSLTest.cpp -I./openssl-1.0.2/include
g++ -shared -L./openssl-1.0.2/lib -lcrypto -lssl Cryptography.o OpenSSLTest.o

