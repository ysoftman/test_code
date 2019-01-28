#!/bin/bash
# ysoftman
# 디렉토리 존재여부
# -d file, True if file exists and is a directory.
if [ -d '/Users/ysoftman/workspace' ]; then
    echo "exist directory"
else
    echo "not exist directory"
fi

# 파일 존재여부
# e file, True if file exists.
if [ -e './exist_file.sh' ]; then
    echo "exist file"
else
    echo "not exist file"
fi

# 레귤러 파일 존재 하지 않는 경우
# -f file, True if file exists and is a regular file.
if [ ! -f './not_exist_file.sh' ]; then
    echo "not exist file"
fi
