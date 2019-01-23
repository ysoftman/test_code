#!/bin/bash
# speedtest cron 으로 기록하기

# speedtest-cli 
# https://github.com/sivel/speedtest-cli

# crontab -e 으로 등록
# macOS 의 경우 "operation not permitted" 발생시
# system preferences -> security & privacy -> privacy 에서 iterm2 를 추가해준다.
# 그리고 macOS 에는 sleep 모드에선 cron 이 작동하지 않는다.
# system preferences -> energy saver 에서 디스플레이가 꺼져도 잠자기 않도록 해야 한다.
# 0 * * * * bash /Users/ysoftman/workspace/test_code/speedtestcron/speedtestcron.sh 2>> $HOME/speedtestcron.log


# cron 환경설정
SHELL=/bin/bash
PATH=$PATH:/usr/local/bin
# speedtest-cli 설치
speedtestpath=$(which speedtest)
if [[ ${speedtestpath##*/} != 'speedtest' ]]; then
    pip install speedtest-cli
fi

outfile="$HOME/speedtestcron.out"
# 다운로드 속도만 주기적으로 기록해보자
date | tr '\n' '\t' >> ${outfile}
uptime | tr '\n' '\t' >> ${outfile}
# speedtest output(stdout 과 stderr) 을 tee 로 stderr 로 출력하고 Download 라인만 grep 해서 파일로 기록 한다.
speedtest --no-upload 2>&1 | tee /dev/stderr | grep -i -E "download:|error:" >> ${outfile}
