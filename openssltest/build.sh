#!/bin/bash
# wget https://www.openssl.org/source/openssl-1.0.2k.tar.gz
# tar zxvf openssl-1.0.2k.tar.gz
# cd openssl-1.0.2k
# linux
# ./config --prefix=/Users/ysoftman/workspace/test_code/openssltest/openssl-1.0.2
# mac
# ./configure darwin64-x86_64-cc --prefix=/Users/ysoftman/workspace/test_code/openssltest/openssl-1.0.2
# make clean
# make && make install

rm a.out *.o core*
g++ -g -fPIC -c cryptography.cpp test_cryptography.cpp -I./openssl-1.0.2/include
g++ -shared -L./openssl-1.0.2/lib -lcrypto -lssl cryptography.o test_cryptography.o
