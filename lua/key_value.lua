-- lua test by ysoftman
-- 테이블(key, value) 테스트
function table_test()
	local tb1 = {}
	local tb2 = {}


	local temp = {
		a = 1,
		b = "str1"
	}
	-- 테이블 추가하기 
	-- table.insert 사용한 경우 테이블은 배열형태로 액세스
	-- 테이블의 개수가 늘어남
	table.insert(tb1, temp)
	print ("#tb1 ", #tb1)
	print ("tb1[" .. #tb1 .. "].a = ", tb1[#tb1].a)
	print ("tb1[" .. #tb1 .. "].b = ", tb1[#tb1].b)
	table.insert(tb1, temp)
	print ("#tb1 ", #tb1)
	print ("tb1[" .. #tb1 .. "].a = ", tb1[#tb1].a)
	print ("tb1[" .. #tb1 .. "].b = ", tb1[#tb1].b)



	-- 테이블 내용 변경(테이블 추가 아님)
	tb2.temp2 = {
		aa = 2,
		bb = "str2"
	}
	tb2.temp3 = {
		aa = 3,
		bb = "str3"
	}
	print ("#tb2 ", #tb2)

	-- 액세스 방법1
	print ("tb2.temp2.aa = ", tb2.temp2.aa)
	print ("tb2.temp2.bb = ", tb2.temp2.bb)
	print ("tb2.temp3.aa = ", tb2.temp3.aa)
	print ("tb2.temp3.bb = ", tb2.temp3.bb)
	-- 액세스 방법2
	print ("tb2['temp2'].aa = ", tb2['temp2'].aa)
	print ("tb2['temp2'].bb = ", tb2['temp2'].bb)
	print ("tb2['temp3'].aa = ", tb2['temp3'].aa)
	print ("tb2['temp3'].bb = ", tb2['temp3'].bb)

	

end

function key_value()

	local temp = {
		aa = {},
		bb = { val1 = 1, val2 = 2, val3 = 3 },
		cc = { val1 = 4, val2 = 5 },
		dd = { val1 = 6, val2 = 7, val3 = 8, val4 = 9 }
	}

	local mydata = {
		cnt = 999,
		desc = "test table"
	}
	-- 테이블 insert 를 이용해서 추가
	table.insert(mydata, temp)

	-- 테이블 안의 테이블 액세스
	for k1, v1 in pairs(mydata) do
		print ("".. k1, v1)

		if type(v1) == "table" then
			for k2, v2 in pairs(v1) do
				print ("\t".. k2, v2)

				if type(v2) == "table" then
					for k3, v3 in pairs(v2) do
						print ("\t\t".. k3, v3)
					end
				end
			end
		end
	end

end


table_test()
key_value()

