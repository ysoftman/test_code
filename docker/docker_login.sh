#!/bin/bash

# 호스트의 실제 터미널의 창은 크기($COLUMNS, $LINES) 값을 컨테이너 접속시 전달한다.
# docker exec -u ysoftman -e COLUMNS=$COLUMNS -e LINES=$LINES -it ysoftman_centos /bin/bash

# .sh 로 실행해야 할 경우 $COLUMSN, $LINES 는 사용할 수 없어 tput 을 사용한다.
docker exec -u ysoftman -e COLUMNS=$(tput cols) -e LINES=$(tput lines) -it ysoftman_centos /bin/bash
