#!/bin/bash
# ysoftman

# /etc/passwd nobody 가 라인번호만 출력
line=$(grep -n nobody /etc/passwd | awk -F ':' '{print $1}')
echo $line

# /etc/passwd nobody 내용 찾아서 파일 내용 변경
sudo sed -i -e 's/nobody:x:99:99:Nobody:\/:\/bin\/bash/nobody:x:99:99:Nobody:\/:\/sbin\/nologin/' /etc/passwd
