@rem ysoftman
@rem ������ �ý��� ȯ�� ���� Path �˻�
reg.exe query "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment" /v Path

@rem ������ �ý��� ȯ�� ���� Path �� ����
@rem /d �ɼ� ������ ��� ����
reg.exe add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment" /v Path /t REG_EXPAND_SZ /f /d "C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\EditPlus 3;C:\Program Files (x86)\FileZilla FTP Client;C:\Program Files (x86)\iPuTTY;C:\Program Files (x86)\The KMPlayer;C:\Program Files (x86)\Java\jdk1.7.0_21\bin;D:\ysoftman\Software\GetGnuWin32\gnuwin32\bin;"
