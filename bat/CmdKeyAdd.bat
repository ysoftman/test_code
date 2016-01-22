@rem 20121001 ysoftman
@rem 원격 데스트톱 로그인을 위한 자격 증명 추가 스크립트
@rem cmdkey.exe 는 windows vista 이후 버전에서 사용 가능함
@cls

@rem 세미콜론부터 라인끝까지는 주석처리
@rem 라인 하나에 3개의 토큰을 가져옴
@rem 자격 증명 삭제
cmdkey.exe /list > CmdKeyDelete.txt
for /f "eol=; tokens=1,2,3" %%i in (CmdKeyDelete.txt) do cmdkey.exe /delete %%j

@rem 윈도우 자격증명은 /add 옵션 사용하여 추가
for /f "eol=; tokens=1,2,3 " %%i in (CmdKeyAdd_windows.txt) do cmdkey.exe /add:%%i /user:%%j /pass:%%k

@rem 일반 자격증명은 /generic 옵션 사용하여 추가
for /f "eol=; tokens=1,2,3 " %%i in (CmdKeyAdd_generic.txt) do cmdkey.exe /generic:%%i /user:%%j /pass:%%k

@pause
