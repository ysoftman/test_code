-- lua test by ysoftman
-- dofile test
dofile("./dofile_sub1.lua")
dofile("./dofile_sub2.lua")
-- 없는 파일을 사용하게 되면 다음과 같은 에러가 발생한다.
-- lua: cannot open ./dofile_sub3.lua: No such file or directory
-- dofile("./dofile_sub3.lua")

aaa()
bbb()
