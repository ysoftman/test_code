-- lua test by ysoftman
-- tostring 테스트
function main()

	local flag = true
	-- print("flag : " .. flag)
	-- print("flag : " .. tonumber(flag))
	print("flag : " .. tostring(flag))

	local num = 123
	print("num : " .. num)
	print("num : " .. tonumber(num))
	print("num : " .. tostring(num))
end

main()


