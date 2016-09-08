-- lua test by ysoftman
-- 주간 번호 테스트
function main()

	local current_time = os.date("%c", os.time())
	print("current_time:" .. current_time)

	-- os.date() 관련 참고
	-- http://lua-users.org/wiki/OsLibraryTutorial (List all params at http://www.cplusplus.com/reference/ctime/strftime/)

	-- 현재 요일 파악
	-- 0 ~ 6 = Sunday ~ Saturday (참고로 "*t" 사용시 wday = 1 ~ 7 = Sunday ~ Saturday)
	local current_week = os.date("%w", os.time())
	print("current_week:" .. current_week)

	-- 현재 올해 몇번째 주인지 파악(월요일이 일주일의 시작)
	local current_week = os.date("%W", os.time())
	print("current_week:" .. current_week)

	-- 2014년 마지막날이 2014년의 몇번째 주인지 파악
	current_week = os.date("%W", os.time({year=2014,month=12,day=31}))
	print("current_week:" .. current_week)

	-- 2015년 첫날이 2015년의 몇번째 주인지 파악(전년도 마지막 주가 완료되지 않아 2015년 0번째 주로 처리됨)
	current_week = os.date("%W", os.time({year=2015,month=1,day=1}))
	print("current_week:" .. current_week)

	-- 2015년 첫날이 2015년의 몇번째 주인지 파악(전년도 마지막 주가 완료되지 않아 2015년 1번째 주로 처리됨)
	current_week = os.date("%W", os.time({year=2015,month=1,day=5}))
	print("current_week:" .. current_week)


	if tonumber(current_week) == 1 then
		print ("aa")
	else
		print ("bb")
	end

end

main()

