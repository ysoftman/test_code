-------------------------------------------------
-- lua_for_c.lua
-- ysoftman
-- Lua <-> C 연동 테스트
print ("[Lua] lua_for_c test start...")

function myfunc1(arg1, arg2, arg3, arg4)
	print ("[Lua] myfunc1() called.")
	print ("[Lua] arg1 = " .. tostring(arg1))
	print ("[Lua] arg2 = " .. arg2)
	print ("[Lua] arg3 = " .. arg3)
	print ("[Lua] arg4 = " .. arg4)
	return 111
end

function myfunc2(arg1)
	print ("[Lua] args1.title = " .. arg1.title)
	print ("[Lua] args1.date = " .. arg1.date)
	len = #arg1
	print ("[Lua] args1 size = " .. len)
	if len < 1 then
		return "fail"
	end
	for i = 1, len do
	print ("[Lua] arg1[" .. i .. "].name = " .. arg1[i].name)
	print ("[Lua] arg1[" .. i .. "].age = " .. arg1[i].age)
	end
	return "success"
end


print ("[Lua] ---------------------------")
-- C 함수 호출
print ("[Lua] Lua --> C")
result = DoSomething(9, 9, 9)
print ("[Lua] result from C = " .. result)
print ("[Lua] ---------------------------")
