#!/bin/bash
rm a.out *.o core*
if [ $(uname) == 'Linux' ]; then
    install_path='/home/ysoftman/workspace/test_code/openssltest/openssl-1.0.2'
elif [ $(uname) == 'Darwin' ]; then
    install_path='/Users/ysoftman/workspace/test_code/openssltest/openssl-1.0.2'
fi
g++ -g -fPIC -c cryptography.cpp test_cryptography.cpp -I${install_path}/include
g++ cryptography.o test_cryptography.o -L${install_path}/lib -lcrypto -lssl -ldl
