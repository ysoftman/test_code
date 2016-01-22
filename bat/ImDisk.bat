@rem ysoftman
@rem 설치하면 c:\windows\system32\imdisk.exe 와 c:\windows\syswow64\imdisk.exe 가 생긴다.
@rem imdisk.exe 를 실행하면 사용방법을 알 수 있다
@rem 램디스크 추가 예 (a드라이브로 추가되며 리부팅이 필요 없다)
start /d "c:\windows\system32\" imdisk.exe -a -m a: -s 10G -p "/fs:NTFS /v:ysoftman_ramdisk /q /y" 

@rem 램디스크 삭제 예(리부팅이 필요 없다)
@rem start /d "c:\windows\system32\" imdisk -d -m a:

@rem 램디스크 사용하고 있어도 강제 삭제 예(리부팅이 필요 없다)
@rem start /d "c:\windows\system32\" imdisk -D -m a:
