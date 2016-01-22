'=================================================================
'ysoftman
'인자 받기 테스트
'=================================================================
Set args = WSCript.Arguments
For i=0 To args.Count-1
	WSCript.Echo args(i)
Next
