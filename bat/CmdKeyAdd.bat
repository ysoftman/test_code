@rem 20121001 ysoftman
@rem ���� ����Ʈ�� �α����� ���� �ڰ� ���� �߰� ��ũ��Ʈ
@rem cmdkey.exe �� windows vista ���� �������� ��� ������
@cls

@rem �����ݷк��� ���γ������� �ּ�ó��
@rem ���� �ϳ��� 3���� ��ū�� ������
@rem �ڰ� ���� ����
cmdkey.exe /list > CmdKeyDelete.txt
for /f "eol=; tokens=1,2,3" %%i in (CmdKeyDelete.txt) do cmdkey.exe /delete %%j

@rem ������ �ڰ������� /add �ɼ� ����Ͽ� �߰�
for /f "eol=; tokens=1,2,3 " %%i in (CmdKeyAdd_windows.txt) do cmdkey.exe /add:%%i /user:%%j /pass:%%k

@rem �Ϲ� �ڰ������� /generic �ɼ� ����Ͽ� �߰�
for /f "eol=; tokens=1,2,3 " %%i in (CmdKeyAdd_generic.txt) do cmdkey.exe /generic:%%i /user:%%j /pass:%%k

@pause
