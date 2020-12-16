#!/bin/bash

filename="touch_test_file.txt"

# touch 로 파일 생성
touch $filename

# access, modify 날짜 변경
# touch -d "1 min ago" $filename
# touch -d "1 hour ago" $filename

# access 날짜만 변경
touch -a -d "10 min ago" $filename

# modify 날짜만 변경
touch -m -d "5 min ago" $filename


# stat 메타 정보 파악
stat $filename

# touch 수정날짜

rm -f $filename
