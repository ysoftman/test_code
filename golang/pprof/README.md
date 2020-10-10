# pprof test

```bash
#  빌드 및 실행
go build && ./pprof

# heap pprof 수행
# pprof 명령은 help 로 파악할 수 있다.
# -http=:9999 를 사용하면 웹(브라우저로 볼 수 있다.)
go tool pprof http://localhost:6060/debug/pprof/heap
Fetching profile over HTTP from http://localhost:6060/debug/pprof/heap
Saved profile in /Users/ysoftman/pprof/pprof.alloc_objects.alloc_space.inuse_objects.inuse_space.009.pb.gz
Type: inuse_space
Time: Apr 9, 2019 at 4:48pm (KST)
Entering interactive mode (type "help" for commands, "o" for options)
(pprof) top
Showing nodes accounting for 514.63kB, 100% of 514.63kB total
      flat  flat%   sum%        cum   cum%
  514.63kB   100%   100%   514.63kB   100%  math/rand.NewSource
         0     0%   100%   514.63kB   100%  math/rand.init.ializers
         0     0%   100%   514.63kB   100%  runtime.main
(pprof) exit


# 5초(디폴트30초)간 cpu 프로파일링
go tool pprof -seconds=5 http://localhost:6060/debug/pprof/profile
Fetching profile over HTTP from http://localhost:6060/debug/pprof/profile?seconds=5
Please wait... (5s)
Saved profile in /Users/ysoftman/pprof/pprof.samples.cpu.004.pb.gz
Type: cpu
Time: Apr 9, 2019 at 4:55pm (KST)
Duration: 5s, Total samples = 0
No samples were found with the default sample value type.
Try "sample_index" command to analyze different sample values.
Entering interactive mode (type "help" for commands, "o" for options)
(pprof) exit


# 위에서 저장된 프로파일링 파일을 다시 웹으로 볼 수 있다.
go tool pprof -http=:9999 /Users/ysoftman/pprof/pprof.samples.cpu.004.pb.gz

# 또는 go tool 을 이용해 콘솔에서 프로파일링할 수 있다.
# 5초동안 트레이스 덤프
curl 'http://localhost:6060/debug/pprof/trace?seconds=5' -o trace.out

# 트레이스 덤프 보기, http://127.0.0.1:xxxx 로 확인
go tool trace trace.out
```
