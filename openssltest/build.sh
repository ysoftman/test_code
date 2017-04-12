#!/bin/bash
rm -rfv openssl-1.0.2k.tar.gz openssl-1.0.2 openssl-1.0.2k
wget https://www.openssl.org/source/openssl-1.0.2k.tar.gz
tar zxvf openssl-1.0.2k.tar.gz
cd openssl-1.0.2k
if [ $(uname) == 'Linux' ]; then
    install_path='/home/ysoftman/workspace/test_code/openssltest/openssl-1.0.2'
    ./config --prefix=${install_path} -fPIC
elif [ $(uname) == 'Darwin' ]; then
    install_path='/Users/ysoftman/workspace/test_code/openssltest/openssl-1.0.2'
    ./configure darwin64-x86_64-cc --prefix=${install_path}
fi
make clean
make -j4 && make install
cd ..

rm a.out *.o core*
g++ -g -fPIC -c cryptography.cpp test_cryptography.cpp -I${install_path}/include
g++ -L${install_path}/lib -lcrypto -lssl cryptography.o test_cryptography.o
