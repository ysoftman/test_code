@rem ysoftman
@rem ����ǻ��\HKEY_CLASSES_ROOT\Directory\shell\ ���� Command Prompt Here ��� Ű�� ����� ���� Command &Prompt Here �� �����Ѵ�.
reg add "HKEY_CLASSES_ROOT\Directory\shell\Command Prompt Here" /v "Command &Prompt Here" /f

@rem ����ǻ��\HKEY_CLASSES_ROOT\Directory\shell\Command Prompt Here ���� command ��� Ű�� ����� ���� cmd.exe /k cd /d %1 �� �����ϸ� �ȴ�.
reg add "HKEY_CLASSES_ROOT\Directory\shell\Command Prompt Here\command" /v "" /d "cmd.exe /k cd /d %%1" /f /t REG_SZ
