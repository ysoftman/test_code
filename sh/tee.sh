#!/bin/bash
rm -f tee_test.log

# tee 명령으로 화면과 파일에 동시 출력하기
# -a append
echo "ysoftman1" | tee -a tee_test.log
echo "ysoftman2" | tee -a tee_test.log
echo "ysoftman3" | tee -a tee_test.log



# 화면에 출력후 파일에도 기록된다.
echo '[tee_test.log]'
cat tee_test.log


# stderr 만 골라 출력
# stderr
asdf 2> >(tee -a tee_test.log)

