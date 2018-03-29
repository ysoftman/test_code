#!/bin/bash

# 컨테이너 접속
#docker exec -u root -it ysoftman_centos /bin/bash

# 또는
docker exec -u ysoftman -e COLUMNS=$COLUMNS -e LINES=$LINES -it ysoftman_centos /bin/bash
