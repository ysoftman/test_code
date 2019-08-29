-- lua test by ysoftman
-- argument test
-- 커맨드라인의 인자를 전역 arg 테이블로 제공한다.
-- lua -v argument.lua a b 10

-- arg 주소값
print(arg)

-- (.lua 뒤부터)인자 개수
print(#arg)
print(arg[0])   -- argument.lua
print(arg[1])   -- a
print(arg[2])   -- b
print(arg[3])   -- 10
print(arg[4])   -- nil
print(arg[-1])   -- -v
print(arg[-2])   -- lua
print(arg[-3])   -- nil
