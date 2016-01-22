@rem 20110720 ysoftman
@rem 경로명이 너무 길면(약 256자이상) 삭제할 수 없게 된다.
@rem 이런 경우 하위 디렉토리를 상위로 이동을 반복하면 경로 길이가 줄어들어 삭제할 수 있다.

@cls
@rem @echo off

@echo [사용방법]
@echo %0 시작위치 상위로_이동할_디렉토리명
@echo [예시]
@echo c:\a\1\1\1\1\1\1\.... 로 되어 있을 경우
@echo %0 c:\a 1

cd %1

@rem 1부터 2000까지 1씩 증가하면서
@rem 만약 디렉토리 깊이가 훨씬 더 크다면 배치를 반복 실행하도록 한다.
@rem 디렉토리를 상위로 새로운 이름으로 옮기고 이동한다.
for /l %%i in (1,1,2000) do move %2 \ysoftman_%%i & cd \ysoftman_%%i

cd \

@rem 상위로 이동된 디렉토리는 ysoftman_1~2000까지의 이름으로 이를 삭제한다.
for /l %%i in (1,1,2000) do rmdir /s /q \ysoftman_%%i

