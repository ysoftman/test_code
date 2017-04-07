///////////////////////////////////////////////////////////
// c_for_lua.cpp
// ysoftman
// Lua <-> C 연동 테스트
#include "iostream"

#ifdef _WIN32
// lua 설치했으면 include 와 lib 경로 추가(Windows 기준)
// C:\Program Files (x86)\Lua\5.1\include
// C:\Program Files (x86)\Lua\5.1\lib
// lua lib 링크
#pragma comment(lib , "lua5.1.lib")

#elif __APPLE__
// curl -R -O http://www.lua.org/ftp/lua-5.3.3.tar.gz
// tar zxf lua-5.3.3.tar.gz
// cd lua-5.3.3
// make macosx test
// cd ..
// g++ c_for_lua.cpp -L./lua-5.3.3/src -llua
#endif

// lua(C 로 만들어짐) 헤더 include
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// lua에서 호출 할 수 있는 함수(int funcname(lua_State* L) 형식이어야 한다)
int DoSomethingForLua(lua_State *L)
{
	std::cout << "DoSomethingForLua() called." << std::endl;

	// lua에서 들어온 인자들 파악
	int a = luaL_checkint(L, 1);
	int b = luaL_checkint(L, 2);
	int c = luaL_checkint(L, 3);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;

	// lua에 스택에 결과 넣기
	lua_pushinteger(L, a+b+c);

	// lua에 리턴 개수 알리기
	return 1;
}

int main(int argc, char* argv[])
{
	std::cout << "c_for_lua test start..." << std::endl;

	// lua state 생성
	lua_State *L = luaL_newstate();
	// lua 라이브러리 오픈
	luaL_openlibs(L);

	// lua에서 C 함수를 호출 할 수 있도록 C 함수 등록
	lua_register(L, "DoSomething", DoSomethingForLua);

	// lua 파일 실행
	// luaL_dofile 은 luaL_loadfile(lua 로드) 와 lua_pcall(lua 초기화) 를 합친것
	luaL_dofile(L, "lua_for_c.lua");


	// lua 스크립트의 myfunc1 함수 가져오기
	lua_getglobal(L, "myfunc1");

	// lua 함수에 전달할 파라미터 스택에 넣기
	lua_pushboolean(L, true);
	lua_pushinteger(L, 99999);
	lua_pushnumber(L, 123.456);
	lua_pushstring(L, "string");
	
	std::cout << "---------------------------" << std::endl;
	std::cout << "C --> Lua" << std::endl;
	
	// lua 함수 호출
	// 파라미터 4개를 전달하고 리턴 1개 받은
	lua_call(L, 4, 1);

	// 스택(minus indexing)에 쌓인 리턴 결과 파악
	std::cout << "result from Lua = " << lua_tonumber(L, -1) << std::endl;
	std::cout << "---------------------------" << std::endl;
	
	// pop 을 해주지 않으면 스택이 계속 쌓인다.
	// lua_pop 은 내부적으로 lua_settop 으로 스택 위치를 설정
	lua_pop(L, 1);
	
	// lua 스크립트의 myfunc2 함수 가져오기
	lua_getglobal(L, "myfunc2");
		
	// lua 함수에 전달할 파라미터 스택에 넣기
	lua_pushnumber(L, 5);
	lua_pushnumber(L, 5);
	
	std::cout << "---------------------------" << std::endl;
	std::cout << "C --> Lua" << std::endl;
	
	// lua 함수 호출
	// 파라미터 2개를 전달하고 리턴 1개 받은
	lua_call(L, 2, 1);

	// 스택(minus indexing)에 쌓인 리턴 결과 파악
	std::cout << "result from Lua = " << lua_tonumber(L, -1) << std::endl;
	std::cout << "---------------------------" << std::endl;	
	
	// pop 을 해주지 않으면 스택이 계속 쌓인다.
	// lua_pop 은 내부적으로 lua_settop 으로 스택 위치를 설정
	lua_pop(L, 1);

	// lua state 제거
	lua_close(L);

	return 0;
}

