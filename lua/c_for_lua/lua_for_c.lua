-------------------------------------------------
-- lua_for_c.lua
-- ysoftman
-- Lua <-> C 연동 테스트
print ("lua_for_c test start...")

function myfunc1(arg1, arg2, arg3, arg4)
	print ("myfunc1() called.")
	print ("arg1 = " .. tostring(arg1))
	print ("arg2 = " .. arg2)
	print ("arg3 = " .. arg3)
	print ("arg4 = " .. arg4)
	return 111
end

function myfunc2(arg1)
	print ("args1.title = " .. arg1.title)
	print ("args1.date = " .. arg1.date)
	len = #arg1
	print ("args1 size = " .. len)
	if len < 1 then
		return "fail"
	end
	for i = 1, len do
	print ("arg1[" .. i .. "].name = " .. arg1[i].name)
	print ("arg1[" .. i .. "].age = " .. arg1[i].age)
	end
	return "success"
end


print ("---------------------------")
-- C 함수 호출
print ("Lua --> C")
result = DoSomething(9, 9, 9)
print ("result from C = " .. result)
print ("---------------------------")
