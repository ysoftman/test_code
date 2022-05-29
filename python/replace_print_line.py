import time
import sys
import signal

# https://docs.python.org/3/howto/curses.html
import curses

# for i in range(2):
#     # print(f"\rtesting...{i}")
#     # newline(\n) 대신 carriage return(\r) 를 사용해 다음 출력도 같은 라인에서 시작하도록 한다.
#     print(f"testing1...{i}s", end="\r")
#     time.sleep(1)

# for i in range(2):
#     sys.stdout.write(f"\rtesting2...{i}s")
#     sys.stdout.flush()
#     time.sleep(1)


# curses 를 사용하면 좀더 세밀하게 조정할 수 있다.
stdscr = curses.initscr()
curses.noecho()
stdscr.clear()


def signal_handler(sig, frame):
    print("You pressed Ctrl+C!")
    # 터미널을 원래 작동 모드로 복원(복원 하지 않으면 ls 등 출력이 깨져 반드시 복원 처리가 필요)
    curses.endwin()
    sys.exit(0)


signal.signal(signal.SIGINT, signal_handler)
for i in range(3):
    stdscr.addstr(0, 0, f"testing1....{i}s\n")
    stdscr.addstr(1, 0, f"testing2....{i}s")
    lastyx = stdscr.getyx()
    stdscr.addstr(2,0, f"last positiion(y:{lastyx[0]}, x:{lastyx[1]})")
    stdscr.refresh()
    time.sleep(1)

# 터미널을 원래 작동 모드로 복원(복원 하지 않으면 ls 등 출력이 깨져 반드시 복원 처리가 필요)
curses.endwin()
