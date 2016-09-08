-- lua test by ysoftman
-- 문자열 테스트
function main()
	print("lua test by ysoftman")

	local temp
	print(temp)

	local str1 = "문자열"
	local str2 = "합치기"
	local str3 = str1 .. " ".. str2
	print(str3)

	local array = {100,101,102}
	print("array elements count : " .. #array)
	local idx = 1
	for idx = 1, #array do
		print(array[idx])
	end


	local str1 = "aaa 123 ccc 456"
	for word in string.gmatch(str1, "%a+") do
		print(word)
	end
	for word in string.gmatch(str1, "%d+") do
		print(word)
	end

end

main()


