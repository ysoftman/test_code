@rem ysoftman
@rem 실행창의 최근 실행 목록 지우기
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\RunMRU /f

@rem 최근 열어본 문서,이미지,음악,동영상등의 파일 목록 지우기
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\RecentDocs /f

@rem 대화상자로 최근 열기/저장한 파일 목록 지우기
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\ComDlg32\OpenSavePidlMRU /f

@rem 최근 입력한 경로 목록 지우기
reg delete HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\TypedPaths /f

@rem 윈도우 탐색기 최근 항목 지우기
del /s /f /q %appdata%\Microsoft\Windows\Recent\AutomaticDestinations

@rem 윈도우 탐색기 최근 항목을 포함한 최근 열어본 문서,이미지,음악,동영상등의 파일 목록 지우기(windows7 점프목록)
del /s /f /q %appdata%\Microsoft\Windows\Recent
