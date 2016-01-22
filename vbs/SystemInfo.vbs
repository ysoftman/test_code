'=================================================================
'ysoftman
'�ý��� ���� �ľ��ϱ�
'=================================================================
Set winmgmt = GetObject("winmgmts:" & "{impersonationLevel=impersonate}!\\" & "." & "\root\cimv2")
Set swr = CreateObject("WbemScripting.SWbemRefresher")

const ReadMode = 1, WriteMode = 2, AppendMode = 8
Set fso = CreateObject("Scripting.FileSystemObject")

' ��� �̸��� ���丮 ����
datedir = ""
If month(date) < 10 Then 
    datedir = year(date) & "0" & month(date)
Else
    datedir = year(date) & month(date)
End If

' �ش� ���丮�� �������� ������ �����Ѵ�.
If fso.FolderExists(datedir) = False Then
    fso.CreateFolder(datedir)
End If


FileName1 = datedir & "\SystemInfo-" & date & "-result.txt"
FileName2 = datedir & "\SystemInfo-" & date & "-debug.txt"

' ����׸� ���� ����
Set tempfile = fso.OpenTextFile(FileName2, WriteMode, True)
' ��� ����� ���� ����
Set resultfile = fso.OpenTextFile(FileName1, WriteMode, True)


' �ý��� ���� �ľ�
Set infoCPU = swr.AddEnum (winmgmt, "Win32_PerfFormattedData_PerfOS_Processor").ObjectSet
Set infoMemory = swr.AddEnum(winmgmt, "Win32_PerfFormattedData_PerfOS_Memory").objectSet
Set infoSystem = swr.AddEnum(winmgmt, "Win32_PerfFormattedData_PerfOS_System").objectSet
Set infoNIC = swr.AddEnum (winmgmt, "Win32_PerfFormattedData_Tcpip_NetworkInterface").objectSet
'Set infoTerminalSvc = swr.AddEnum (winmgmt, "Win32_PerfFormattedData_TermService_TerminalServices").ObjectSet
Set infoICMP = swr.AddEnum (winmgmt, "Win32_PerfFormattedData_Tcpip_ICMP").ObjectSet
Set infoLogiDisk = swr.AddEnum(winmgmt, "Win32_PerfFormattedData_PerfDisk_LogicalDisk").objectSet
Set infoProcesses = swr.AddEnum(winmgmt, "Win32_PerfFormattedData_PerfProc_Process").objectSet

' �ý��� ���� ���Ϸ� ���
cnt = 0
Do
	swr.Refresh
	For Each objCPU in infoCPU
		If IsNull(objCPU.PercentProcessorTime) = False Then
			resultfile.WriteLine "[" & now & "]" & _
			" [CPU] " & _
			" Name: " & objCPU.Name & _
			", ProcessorTime(%): " & objCPU.PercentProcessorTime & _
			", InterruptTime(%): " & objCPU.PercentInterruptTime
			End If
	Next
			
	For Each objMemory in infoMemory
		If IsNull(objMemory.PoolPagedBytes) = False Then
			resultfile.WriteLine "[" & now & "]" & _
		" [Memory] " & _
		" Available Mem(MB): " & objMemory.AvailableMBytes & _
		", Page Faults: " & objMemory.PageFaultsPerSec & _		
		", Pool Nonpaged Allocs: " & objMemory.PoolNonpagedAllocs & _
		", Pool Nonpaged Bytes: " & objMemory.PoolNonpagedBytes & _
		", Pool Paged Allocs: " & objMemory.PoolPagedAllocs & _
		", Pool Paged Bytes: " & objMemory.PoolPagedBytes
		End If
	Next

	'[System] ... 1 sec
	For Each objSystem in infoSystem	
		LogData = "[" & now & "]" & _
		" [System] " & _
		" Process Count: " & objSystem.Processes & _
		", Thread Count: " & objSystem.Threads & _
		", Conext Switch: " & objSystem.ContextSwitchesPerSec & _
		", System Call: " & objSystem.SystemCallsPerSec & _
		", SystemUpTime: " & objSystem.SystemUpTime
		If IsNull(objSystem.SystemUpTime) = False Then
			resultfile.WriteLine LogData
		End If

	Next	
	
	For Each objNIC in infoNIC
		Result = Instr( objNIC.Name, "MS TCP Loopback interface")
		If (Result <> 0) Then 
		Else
		If IsNull(objNIC.BytesTotalPerSec) Then
			Else
			resultfile.WriteLine "[" & now & "]" & _
			" [NIC] " & _
			" Rcv Bytes: " & objNIC.BytesReceivedPerSec & _
			", Snd Bytes: " & objNIC.BytesSentPerSec & _
			", Total Bytes: " & objNIC.BytesTotalPerSec & _
			", Rcv Packets: " & objNIC.PacketsReceivedPerSec & _
			", Snd Packets: " & objNIC.PacketsSentPerSec & _
			", Total Packets: " & objNIC.PacketsPerSec
			End If
		End If
	Next
	
'	For Each objTerminalSvc in infoTerminalSvc
'		LogData = "[" & now & "]" & _
'		" [TerminalSvc] " & _
'		" Total Sessions: " & objTerminalSvc.TotalSessions & _
'		", Active Sessions: " & objTerminalSvc.ActiveSessions		
'		If IsNull(objTerminalSvc.TotalSessions) = False Then
'			resultfile.WriteLine LogData
'		End If
'	Next
	
	For Each objICMP in infoICMP	
		LogData = "[" & now & "]" & _
		" [ICMP] " & _
		" Messages: " & objICMP.MessagesPerSec & _
		", Messages Outbound Errors: " & objICMP.MessagesOutboundErrors		
		If IsNull(objICMP.MessagesPerSec) = False Then
			resultfile.WriteLine LogData
		End If
	Next
		
	For Each objLogiDisk in infoLogiDisk	
		If objLogiDisk.Name <> "_Total" Then
			LogData = "[" & now & "]" & _
			" [DISK(Logical)] " & _
			" Name: " & objLogiDisk.Name & _            
			", Free Space: " & objLogiDisk.FreeMegabytes & "(MB)" & _
			", DiskTime: " & objLogiDisk.PercentDiskTime & "(%)" & _
			", IdleTime: " & objLogiDisk.PercentIdleTime & "(%)" & _
			", Disk Read Bytes: " & objLogiDisk.DiskReadBytesPerSec & _
			", Disk Write Bytes: " & objLogiDisk.DiskWriteBytesPerSec
			If IsNull(objLogiDisk.FreeMegabytes) = False Then
				resultfile.WriteLine LogData
			End If
		End If
	Next

	For Each objProcess in infoProcesses	
		result = Instr( objProcess.Name, "explorer")
		If result <> 0 Then
			LogData = "[" & now & "]" & _
			" [Processor] " & _
			" PN : " & objProcess.Name & _
			", Mem : " & objProcess.WorkingSet / 1024 & " KB" & _
			", PeakMem : " & objProcess.WorkingSetPeak / 1024 & " KB" & _
			", ThreadCnt : " & objProcess.ThreadCount & _
			", Handle : " & objProcess.HandleCount
			If IsNull(objProcess.WorkingSet) = False Then
				resultfile.WriteLine LogData
			End If
		End If
	Next
	
	'WScript.Sleep 1000*60	' 1��
	WScript.Sleep 1000	' 1��

	cnt = cnt + 1
	resultfile.WriteLIne ""
	resultfile.WriteLIne ""
Loop While cnt < 2

resultfile.close
tempfile.close

