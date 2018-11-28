#!/bin/bash
# build
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/workspace/apr/lib:
g++ -O2 -g -fPIC apr_test.cpp -o aprtest -I${HOME}/workspace/apr/include/apr-1 -I/usr/local/ssl/include -L${HOME}/workspace/apr/lib -L/usr/local/ssl/lib -lapr-1 -lssl -lcrypto -ldl
