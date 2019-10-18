# matplotlib on wsl

```bash
# wsl(windows subsystem for linux) 에서 matplotlib 사용시
# 다음과 같이 그래프를 출력하는데
import matplotlib.pyplot as plt
plt.show()

# 다음과 같은 에러가 발생한다.
UserWarning: Matplotlib is currently using agg, which is a non-GUI backend, so cannot show the figure.

# 해결방법
# python3-tk 설치
sudo apt-get install python3-tk
# DISPLAY 환경변수 설정(.bashrc 에 추가하자)
export DISPLAY=localhost:0.0
# 윈도우용 xserver 설치 후 multiple windows 로 실행한다.
https://sourceforge.net/projects/vcxsrv/

# 이제 다시 실행하면 그래프 창을 볼 수 있다.
```
