#!/bin/bash
# ysoftman

# 테스트를 위한 임시 서버 리스트 파일 생성
echo 'server-lemon
server-apple
server-orange' > temp_server_list.txt

# 여러 호스트에 ssh 명령 실행
# stdin(< temp_server_list.txt) 파이프라인을 사용중 ssh 로 원격 명령실
while read server
do
    echo ${server}
    # stdin("hostname" 명령) 을 사용하면 기존 stdin(< temp_server_list.txt)이 끝나게 되어 루프가 끝나게 된다.
    # < /dev/null 로 stdin 을 사용하지 않도록 한다.
    # -o "StrictHostKeyChecking no" 접속시 호스트 체크 안하기
    out=`ssh -o "StrictHostKeyChecking no" ysoftman@server "hostname" < /dev/null`
    echo ${out}
done < temp_server_list.txt

# 테스트를 위한 임시 파일 삭제
rm temp_server_list.txt
