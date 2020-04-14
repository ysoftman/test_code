#!/bin/bash
rm -f tee_test_file

# tee 명령으로 화면과 파일에 동시 출력하기
# -a append
echo "ysoftman1" | /usr/bin/tee -a tee_test_file
echo "ysoftman2" | /usr/bin/tee -a tee_test_file
echo "ysoftman3" | /usr/bin/tee -a tee_test_file



# 화면에 출력후 파일에도 기록된다.
echo '[tee_test_file]'
cat tee_test_file

