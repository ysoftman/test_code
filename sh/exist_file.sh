#!/bin/bash
# ysoftman
# 디렉토리 존재여부
if [ -d '/Users/ysoftman/workspace' ]; then
    echo "exist directory"
else
    echo "not exist directory"
fi


# 파일 존재여부
if [ -f './exist_file.sh' ]; then
    echo "exist file"
else
    echo "not exist file"
fi
