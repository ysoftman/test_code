#!/bin/bash
# speedtest cron 으로 기록하기

# speedtest-cli 
# https://github.com/sivel/speedtest-cli

# crontab -e 으로 등록
# macOS 의 경우 "operation not permitted" 발생시
# system preferences -> security & privacy -> privacy 에서 iterm2 를 추가해준다.
# 0 * * * * bash /Users/ysoftman/workspace/test_code/speedtestcron/speedtestcron.sh 2>&1 $HOME/speedtestcron.log


# cron 환경설정
SHELL=/bin/bash
PATH=$PATH:/usr/local/bin
# speedtest-cli 설치
speedtestpath=$(which speedtest)
if [[ ${speedtestpath##*/} != 'speedtest' ]]; then
    pip install speedtest-cli
else
    echo 'speedtest-cli installed'
fi

outfile="$HOME/speedtestcron.out"
# 다운로드 속도만 주기적으로 기록해보자
# zsh 에서 noclobber 설정때문에 강제(!) 추가
date | tr '\n' ' ' >> ${outfile}
# speedtest output(stdout) 을 tee 로 stderr 로 출력하고 Download 라인만 grep 해서 파일로 기록 한다.
speedtest --no-upload | tee /dev/stderr | grep "Download" >> ${outfile}
