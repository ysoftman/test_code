#!/bin/bash
# crontab 과 같이 반복 예약 작업 아닌 일회성 예약 작업을 위해 at 명령을 사용한다.
# at 데몬이 실행되어 있어야 한다.
# linux 
# sudo service atd start
# mac
# launchctl load -w /System/Library/LaunchDaemons/com.apple.atrun.plist
# launchctl list | grep atrun

# 1분후에 명령 실행, 명령은 프롬프트에서 입력 후 ctrl+d
# 시간 단위(자세한 설명은 man page 참고)
# tody 또는 tommorow
# now + minutes, hours, days, weeks, months, years
# now + 초는 지원안함
# at now + 1 minute
# at> cd /Users/ysoftman; rm -f at_job.out; echo "at jobs ysoftman" > at_job.out

# 스크립트 실행
# at -f 스크립트파일 now + 1 minute

# 예약된 작업 리스트
at -l

# 예약된 작업 내용 보기
# /bin/sh 로 실행되기 때문에 환경변수등이 같이 설정되어 보인다.
# at -c 잡번호

# 예약 작업 삭제
# alias for atrm
# at -d (deprecated)
at -r 

# 예약된 작업들 모두 삭제
at -r $(at -l | awk '{print $1}' ORS=' ')
