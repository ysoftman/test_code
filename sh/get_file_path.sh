#!/bin/bash
# get this file fullpath
fullpath=''
if [ $(uname) == 'Darwin' ]; then
    # fullpath=${PWD}
    fullpath=`cd $(dirname $0); pwd`
elif [ $(uname) == 'Linux' ]; then
    fullpath=`readlink -f $0`
fi
echo fullpath=${fullpath}

onlydir=`dirname ${fullpath}`
echo onlydir=${onlydir}
