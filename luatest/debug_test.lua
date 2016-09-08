-- lua test by ysoftman
-- debug 사용하기
-- 참고 http://www.lua.org/pil/23.1.html

function DPrintf(output)
	-- 디버그 정보를 파악할 대상 함수 선택
	-- 콜 스택 레벨 설정, 1이면 DPrintf, 2이면 DPrintf를 호출한 함수
	local level = 2
	-- 디버그 정보 파악
	-- `n´	selects fields name and namewhat
	-- `f´	selects field func
	-- `S´	selects fields source, short_src, what, and linedefined
	-- `l´	selects field currentline
	-- `u´	selects field nup
	local dinfo = debug.getinfo(level, "nfSlu")
	
	local name, value = debug.getupvalue(dinfo.func, 2)
	if name == nil then
		name = "nil"
	end
	if value == nil then
		value = "nil"
	end
	print("[func]" .. name .. ":" .. value)

	if dinfo.nup == nil then
		dinfo.nup = "nil"
	end

	print(string.format("[%s %d %s %s %s] %s",
		dinfo.source,
		dinfo.currentline,
		dinfo.name,
		dinfo.namewhat,	
		dinfo.nup,
		output))
end


function DoTest1()
	local a = 1
	local b = 2
	local c = a + b
	DPrintf(c .. "=" .. a .. "+" .. b)
	
end


function DoTest2()
	local a = "name : "
	local b = "ysoftman"
	local c = a .. b
	DPrintf(c)
end

function main()
	-- 디버그 정보 테스트
	DoTest1()
	DoTest2()
end

main()
