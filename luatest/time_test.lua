-- lua test by ysoftman
-- 시간 테스트
function main()

	local cur_epoch = os.time()

	print("cur_epoch : " .. cur_epoch)
	local cur_date1 = os.date("%Y-%m-%d %H:%M:%S", cur_epoch)
	print("cur_date1 : " .. cur_date1)

	local cur_date2 = os.date("%c", cur_epoch)
	print("cur_date2 : " .. cur_date2)


	local cur_date3 = os.date("*t", cur_epoch)
	print("cur_date3 year : " .. cur_date3.year)
	print("cur_date3 month : " .. cur_date3.month)
	print("cur_date3 day : " .. cur_date3.day)
	print("cur_date3 yday : " .. cur_date3.yday)
	print("cur_date3 hour : " .. cur_date3.hour)
	print("cur_date3 min : " .. cur_date3.min)
	print("cur_date3 sec : " .. cur_date3.sec)

end

main()


