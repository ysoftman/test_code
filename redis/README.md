# redis test

- redis 설치

```bash
bash ./install_redis.sh
```

- redis-server 시작

```bash
./redis/bin/redis-server redis7001.conf
./redis/bin/redis-server redis7002.conf
./redis/bin/redis-server redis7003.conf
./redis/bin/redis-server redis7004.conf
./redis/bin/redis-server redis7005.conf
./redis/bin/redis-server redis7006.conf
```

- redis-cluster 구성

```bash
# --cluster-replicas n 명시하지 않으면 마스터 노드로만 구성한다.
# 1 이면 master 당 slave 1개로 구성한다.
# 클러스터는 최소 3개의 마스터가 필요, 슬레이브까지 구성하려면 6개의 노드가 필요하다.
./redis/bin/redis-cli --cluster create --cluster-replicas 1 -a "ysoftmanPassword123" \
127.0.0.1:7001 \
127.0.0.1:7002 \
127.0.0.1:7003 \
127.0.0.1:7004 \
127.0.0.1:7005 \
127.0.0.1:7006

# cluster 확인
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c cluster nodes

# cluster 접속해서 테스트
# -c cluster 로 접속하지 않으면 다른 슬롯으로 이동이 되지 않는다.
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c
127.0.0.1:7001> set ysoftman lemon
-> Redirected to slot [8041] located at 127.0.0.1:7002
OK
127.0.0.1:7002> get ysoftman
"lemon"
# mset / mget 은 redis single 에서 동작하지만
# cluster 로 구성하면 각 노드(슬롯)로 분산되기 때문에 사용할 수 없다.
127.0.0.1:7002> mset aa lemon bb apple
(error) CROSSSLOT Keys in request don't hash to the same slot
# 대신 {같은번호} 로 명시해 같은 슬롯으로 저장하면 된다.
127.0.0.1:7002> mset {1}aa lemon {1}bb apple
OK
127.0.0.1:7002> mget {1}aa {1}bb
1) "lemon"
2) "apple"
```

- 3개의 sentinel 를 띄워 각각 마스터 노드3개를 모니터링

```bash
# 현재 마스터 노드의 포트 파악 후
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c cluster nodes | grep master | awk '{print $2}' | sed 's/.*://' | sed 's/@.*//' | tr '\n' ' '
# 설정에서 마스터 포트를 변경(명시)해서 sentinel 을 실행시킨다.
./redis/bin/redis-sentinel sentinel27001.conf
./redis/bin/redis-sentinel sentinel27002.conf
./redis/bin/redis-sentinel sentinel27003.conf
```

- sentinel 동작 테스트

```bash
# 7001, 7002, 7003 포트가 마스터 노드인 상황
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c
# 7002 노드에 값을 저장
127.0.0.1:7001> set ysoftman orange
-> Redirected to slot [8041] located at 127.0.0.1:7002
OK
127.0.0.1:7002> get ysoftman
"orange"

# 7002 노드 제거
kill -9 $(ps -ef | grep -E ".*redis.*:7002" | grep -v "grep" | awk '{print $2}')

# 7002 master 노드 fail 상태, 7005 slave -> master 변경됨
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c cluster nodes
Warning: Using a password with '-a' or '-u' option on the command line interface may not be safe.
34b867023af79468bf4f2926b060eca5741455b1 127.0.0.1:7003@17003 master - 0 1635090090468 3 connected 10923-16383
972b73d32638376b59cb5e6609b217e3d3286f44 127.0.0.1:7002@17002 master,fail - 1635090070264 1635090063193 2 disconnected
6c3507cbc50ee1cae5bba336ff1168f1b92be67d 127.0.0.1:7004@17004 slave 06948db08ba4f8a59dc3b717f1325151ffe2fc8e 0 1635090091476 1 connected
92640be3b64770324a700418acacb7c770fd8b93 127.0.0.1:7005@17005 master - 0 1635090090000 7 connected 5461-10922
b8939e0cf3c49d6b62172fc2cfcd20225fbefd79 127.0.0.1:7006@17006 slave 34b867023af79468bf4f2926b060eca5741455b1 0 1635090092488 3 connected
06948db08ba4f8a59dc3b717f1325151ffe2fc8e 127.0.0.1:7001@17001 myself,master - 0 1635090091000 1 connected 0-5460

# 3개의 sentinel.log 에 7002 -> 7005 로 마스터 노드를 변경해 failover 처리 되었음을 알 수 있다.
57677:X 25 Oct 2021 00:41:26.895 # +switch-master redis2 127.0.0.1 7002 127.0.0.1 7005
57677:X 25 Oct 2021 00:41:26.896 * +slave slave 127.0.0.1:7002 127.0.0.1 7002 @ redis2 127.0.0.1 7005
57677:X 25 Oct 2021 00:41:36.935 # +sdown slave 127.0.0.1:7002 127.0.0.1 7002 @ redis2 127.0.0.1 7005

# 7005는 slave 였을때 7002 의 백업을 하고 있었고
# 이제 master 가 된 7005 에서 7002 에 저장 했던 값을 찾을 수 있다.
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c
Warning: Using a password with '-a' or '-u' option on the command line interface may not be safe.
127.0.0.1:7001> get ysoftman
-> Redirected to slot [8041] located at 127.0.0.1:7005
"orange"
127.0.0.1:7005>

# 죽은 7002 노드를 시작하면
./redis/bin/redis-server redis7002.con
# 7002 는 slave 로 동작한다.
./redis/bin/redis-cli -p 7001 -a "ysoftmanPassword123" -c cluster nodes
Warning: Using a password with '-a' or '-u' option on the command line interface may not be safe.
34b867023af79468bf4f2926b060eca5741455b1 127.0.0.1:7003@17003 master - 0 1635090263000 3 connected 10923-16383
972b73d32638376b59cb5e6609b217e3d3286f44 127.0.0.1:7002@17002 slave 92640be3b64770324a700418acacb7c770fd8b93 0 1635090262960 7 connected
6c3507cbc50ee1cae5bba336ff1168f1b92be67d 127.0.0.1:7004@17004 slave 06948db08ba4f8a59dc3b717f1325151ffe2fc8e 0 1635090262353 1 connected
92640be3b64770324a700418acacb7c770fd8b93 127.0.0.1:7005@17005 master - 0 1635090263364 7 connected 5461-10922
b8939e0cf3c49d6b62172fc2cfcd20225fbefd79 127.0.0.1:7006@17006 slave 34b867023af79468bf4f2926b060eca5741455b1 0 1635090264374 3 connected
06948db08ba4f8a59dc3b717f1325151ffe2fc8e 127.0.0.1:7001@17001 myself,master - 0 1635090263000 1 connected 0-5460

# 7002 노드의 replication 정보를 보면 7005 를 master 로 바라보고 있음을 알 수 있다.
./redis/bin/redis-cli -p 7002 -a "ysoftmanPassword123" info replication
# Replication
role:slave
master_host:127.0.0.1
master_port:7005
... 생략 ...
```

- sentinel, redis-server 종료, log,pid 등 파일 제거

```bash
kill -9 $(ps -ef | grep "redis" | grep -v "grep" | awk '{print $2}')
rm -rf nodes*.conf *.log *.pid dump.rdb
```

- 노드 추가 삭제

```bash
# 127.0.0.1:7001 의 클러스터에 신규 노드 127.0.0.1:7007 추가
# sentinel도 sentinel.conf 내용 변경 후  다시 적용해야 한다.
redis-cli -a "ysoftmanPassword123" --cluster add-node 127.0.0.1:7007 127.0.0.1:7001

# 추가된 노드 127.0.0.1:7007 슬롯 재분배
# 클러스터 마스터 노드 개수 만큼 수행되어 시간이 오래 걸림, 재분배 중에도 클러스터 사용 가능
redis-cli -a "ysoftmanPassword123" --cluster rebalance 127.0.0.1:7007 --cluster-use-empty-masters

# 127.0.0.1:7007 삭제전 slot 옮기기(옮길 슬롯 개수 선택,어디로 옮겨질 노드 hash id 선택)
# slave 노드는 reshard가 필요 없음
redis-cli -a "ysoftmanPassword123" --cluster reshard 127.0.0.1:7007
# 이제 클러스터에서 노드 127.0.0.1:7001 에서 127.0.0.1:7007(hash:111222333444555)
redis-cli -a "ysoftmanPassword123" --cluster del-node 127.0.0.1:7001 111222333444555

# shutdown(kill) 된 노드의 경우 삭제
# 클러스터 각 노드에서 111222333444555 를 제거 한다.
# 노드 마다 시 1분이 넘어가면 다시 생성되니, 다음과 같이 한번에 수행해야 한다.
redis-cli -h 127.0.0.1 -p 7001 -a "ysoftmanPassword123" cluster forget 111222333444555
redis-cli -h 127.0.0.1 -p 7002 -a "ysoftmanPassword123" cluster forget 111222333444555
redis-cli -h 127.0.0.1 -p 7003 -a "ysoftmanPassword123" cluster forget 111222333444555
redis-cli -h 127.0.0.1 -p 7004 -a "ysoftmanPassword123" cluster forget 111222333444555
redis-cli -h 127.0.0.1 -p 7005 -a "ysoftmanPassword123" cluster forget 111222333444555
redis-cli -h 127.0.0.1 -p 7006 -a "ysoftmanPassword123" cluster forget 111222333444555
```
