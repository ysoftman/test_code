@rem ysoftman
@rem ����â�� �ֱ� ���� ��� �����
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\RunMRU /f

@rem �ֱ� ��� ����,�̹���,����,��������� ���� ��� �����
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\RecentDocs /f

@rem ��ȭ���ڷ� �ֱ� ����/������ ���� ��� �����
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\ComDlg32\OpenSavePidlMRU /f

@rem �ֱ� �Է��� ��� ��� �����
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\TypedPaths /f

@rem ������ Ž���� �ֱ� �׸� �����
del /s /f /q %appdata%\Microsoft\Windows\Recent\AutomaticDestinations

@rem ������ Ž���� �ֱ� �׸��� ������ �ֱ� ��� ����,�̹���,����,��������� ���� ��� �����(windows7 �������)
del /s /f /q %appdata%\Microsoft\Windows\Recent
