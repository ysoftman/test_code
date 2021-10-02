#!/bin/bash

openssl_version="1.0.2k"
openssl_install_path="openssl-${openssl_version}"
install_openssl()
{
    rm -rfv openssl-${openssl_version}
    if [ -f 'openssl-${openssl_version}.tar.gz' ]; then
        echo 'ok'
    else
        echo 'download'
        wget https://www.openssl.org/source/openssl-${openssl_version}.tar.gz
    fi
    tar zxvf openssl-${openssl_version}.tar.gz
    cd openssl-${openssl_version}

    if [ $(uname) == 'Linux' ]; then
        ./config --prefix=${openssl_install_path}
    elif [ $(uname) == 'Darwin' ]; then
        ./Configure darwin64-x86_64-cc --prefix=${openssl_install_path}
    fi
    make clean
    make -j4 && make install
    cd ..
}


echo "install openssl library? [y/n]"
read yesno
yesno=$(echo $yesno | tr '[:upper:]' '[:lower:]')
if [ ${yesno} == 'y' ]; then
    install_openssl
fi

rm a.out *.o core*
g++ -g -fPIC -c cryptography.cpp test_cryptography.cpp -I${openssl_install_path}/include
g++ cryptography.o test_cryptography.o -L${openssl_install_path}/lib -lcrypto -lssl -ldl
