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

# get dir path
# method1 - using dirname command
onlydir=`dirname ${fullpath}`
echo onlydir=${onlydir}

# method2 - using realpath command
onlydir2=$(realpath ../)
echo onlydir2=${onlydir2}


# if exist symbloic link file, delete
if [ -h $0.link ]; then
	echo "exist link file $0.link"
	unlink $0.link
fi
ln -s $0 $0.link

# show link file own contents
readlink $0.link

# show link contents
cat $0.link
