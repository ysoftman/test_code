# fg, bg, jobs 테스트

```bash
# & 백드라운드 작업으로 실행(running)
sleep 10 &
# job 상태가 다음과 같이 표시된다.
jobs
# [1]  + running    sleep 10

# 명령 실행 후 ctrl+z 로 잡을 백그라운드로 보내고 대기(suspended) 상태로 만든다.
sleep 10
# 백그라운드 잡이 running 중이지 않고 대기중이라 10초가 지나도 끝나지 않는다.
# job 상태가 다음과 같이 표시된다.
jobs
# [1]  + suspended  sleep 10


# 방법1
# 백그라운드 잡을 현재 쉘로 가져와 실행(foreground)
fg
# [1]  + 28304 continued  sleep 10
# ~/w/t/sh ❯❯❯

# 방법2
# 백그라운 잡을 백그라운드에서 실행(running)
bg
# [1]  + 28219 continued  sleep 10
# ~/w/t/sh ❯❯❯
# [1]  + 28219 done       sleep 10
```
