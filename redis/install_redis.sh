#!/bin/bash

redis_version=6.2.6

if [ ! -f redis-${redis_version}.tar.gz ]; then
    wget https://download.redis.io/releases/redis-${redis_version}.tar.gz
fi

rm -rf redis-${redis_version}
tar zxvf redis-${redis_version}.tar.gz
cd redis-${redis_version}
make -j8 PREFIX=../../redis install
cd ..
rm -rf redis-${redis_version}
rm -rf redis-${redis_version}.tar.gz
