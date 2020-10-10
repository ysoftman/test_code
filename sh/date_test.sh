#!/bin/bash
# 현재 년도
date +%Y

# 현재 월
date +%m

# 현재 시간,분
date +%H:%M

# 현재 unix (epoch) time seconds
date +%s


# [linux]
# 특정 date -> unix time
date -d "2014-02-15" +%s

# 특정 unix time -> date
date -d "@1392390000"


# [mac]
# 특정 date -> unix time
# -j do not try to set the date
# -f user input_fmt
date -j -f "%Y-%m-%d %H:%M:%S" "2014-02-15 15:02:17" "+%s"

# 특정 unix time -> date
date -r 1392390000
