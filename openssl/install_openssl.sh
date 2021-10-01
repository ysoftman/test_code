#!/bin/bash
rm -rfv openssl-1.0.2 openssl-1.0.2k
if [ -f 'openssl-1.0.2k.tar.gz' ]; then
    echo 'ok'
else
    echo 'download'
    wget https://www.openssl.org/source/openssl-1.0.2k.tar.gz
fi
tar zxvf openssl-1.0.2k.tar.gz
cd openssl-1.0.2k
if [ $(uname) == 'Linux' ]; then
    install_path='/home/ysoftman/workspace/test_code/openssltest/openssl-1.0.2'
    ./config --prefix=${install_path}
elif [ $(uname) == 'Darwin' ]; then
    install_path='/Users/ysoftman/workspace/test_code/openssltest/openssl-1.0.2'
    ./Configure darwin64-x86_64-cc --prefix=${install_path}
fi
make clean
make -j4 && make install
cd ..
