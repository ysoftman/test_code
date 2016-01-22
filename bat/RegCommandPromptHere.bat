@rem ysoftman
@rem 내컴퓨터\HKEY_CLASSES_ROOT\Directory\shell\ 에서 Command Prompt Here 라는 키를 만들고 값은 Command &Prompt Here 로 설정한다.
reg add "HKEY_CLASSES_ROOT\Directory\shell\Command Prompt Here" /v "Command &Prompt Here" /f

@rem 내컴퓨터\HKEY_CLASSES_ROOT\Directory\shell\Command Prompt Here 에서 command 라는 키를 만들고 값은 cmd.exe /k cd /d %1 로 설정하면 된다.
reg add "HKEY_CLASSES_ROOT\Directory\shell\Command Prompt Here\command" /v "" /d "cmd.exe /k cd /d %%1" /f /t REG_SZ
