'=================================================================
'ysoftman
'���� ��¥�� �������� �Ѵ� ������ �α�����(���丮)�� ������Ų��.
'=================================================================
datedir = Date - 30
wscript.echo datedir

' ��¥ ǥ���� - �� ����
newdatedir = Replace(datedir, "-", "")
wscript.echo newdatedir

' �ش� ���丮 ����
Set objshell = createobject("wscript.shell")
'objshell.run "cmd /c dir"
objshell.run "cmd /c rmdir /s /q " & newdatedir
