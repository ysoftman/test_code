@rem ysoftman
@rem ��ġ�ϸ� c:\windows\system32\imdisk.exe �� c:\windows\syswow64\imdisk.exe �� �����.
@rem imdisk.exe �� �����ϸ� ������� �� �� �ִ�
@rem ����ũ �߰� �� (a����̺�� �߰��Ǹ� �������� �ʿ� ����)
start /d "c:\windows\system32\" imdisk.exe -a -m a: -s 10G -p "/fs:NTFS /v:ysoftman_ramdisk /q /y" 

@rem ����ũ ���� ��(�������� �ʿ� ����)
@rem start /d "c:\windows\system32\" imdisk -d -m a:

@rem ����ũ ����ϰ� �־ ���� ���� ��(�������� �ʿ� ����)
@rem start /d "c:\windows\system32\" imdisk -D -m a:
