-------------------------------------------------
-- lua_for_c.lua
-- ysoftman
-- Lua <-> C ���� �׽�Ʈ
print ("lua_for_c test start...")

function myfunc1(arg1, arg2, arg3, arg4)
	print ("myfunc1() called.")
	print ("arg1 = " .. tostring(arg1))
	print ("arg2 = " .. arg2)
	print ("arg3 = " .. arg3)
	print ("arg4 = " .. arg4)
	return 111
end

function myfunc2(arg1, arg2)
	print ("myfunc2() called.")
	print ("arg1 = " .. arg1)
	print ("arg2 = " .. arg2)

	return arg1 + arg2
end

print ("---------------------------")
-- C �Լ� ȣ��
print ("Lua --> C")
result = DoSomething(9, 9, 9)
print ("result from C = " .. result)
print ("---------------------------")
