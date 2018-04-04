#!/bin/bash
rm -f tee_test_file

# tee 명령으로 화면과 파일에 동시 출력하기
echo "ysoftman" | /usr/bin/tee tee_test_file

# 화면에 출력후 파일에도 기록된다.
# cat tee_test_file
