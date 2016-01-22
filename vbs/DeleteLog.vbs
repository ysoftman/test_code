'=================================================================
'ysoftman
'현재 날짜를 기준으로 한달 이전의 로그파일(디렉토리)는 삭제시킨다.
'=================================================================
datedir = Date - 30
wscript.echo datedir

' 날짜 표시의 - 를 제거
newdatedir = Replace(datedir, "-", "")
wscript.echo newdatedir

' 해당 디렉토리 삭제
Set objshell = createobject("wscript.shell")
'objshell.run "cmd /c dir"
objshell.run "cmd /c rmdir /s /q " & newdatedir
