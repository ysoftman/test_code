#!/bin/bash

# .sh 로 실행해야 할 경우 $COLUMNS, $LINES 는 사용할 수 없어 tput 을 사용한다.
docker exec -u root -e COLUMNS=$(tput cols) -e LINES=$(tput lines) -it ysoftman_centos_simple /bin/bash
