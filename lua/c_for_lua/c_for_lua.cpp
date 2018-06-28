///////////////////////////////////////////////////////////
// c_for_lua.cpp
// ysoftman
// Lua <-> C 연동 테스트
#include "iostream"

// windows
// lua 설치했으면 include 와 lib 경로 추가(Windows 기준)
// C:\Program Files (x86)\Lua\5.1\include
// C:\Program Files (x86)\Lua\5.1\lib
// lua lib 링크
// #pragma comment(lib, "lua5.1.lib")

// linux / mac
// curl -R -O http://www.lua.org/ftp/lua-5.3.3.tar.gz
// tar zxf lua-5.3.3.tar.gz
// cd lua-5.3.3
// 리눅스
// make generic test
// 맥
// make macosx test
// cd ..
// g++ c_for_lua.cpp -I./lua-5.3.3/src -L./lua-5.3.3/src -llua && ./a.out

// lua(C 로 만들어짐) 헤더 include
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// lua 스택 인덱싱
// 양수 - bottom(1), 2, 3 .. top(n) 으로 인덱싱
// 음수 - top(-1) -2, -3 .. bottom(-n) 으로 인덱싱

// lua에서 호출 할 수 있는 함수(int funcname(lua_State* L) 형식이어야 한다)
int DoSomethingForLua(lua_State *L)
{
	std::cout << "DoSomethingForLua() called." << std::endl;

	// lua에서 들어온 인자들 파악
	int a = luaL_checkinteger(L, 1);
	int b = luaL_checkinteger(L, 2);
	int c = luaL_checkinteger(L, 3);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;

	// lua에 스택에 결과 넣기
	lua_pushinteger(L, a + b + c);

	// lua에 리턴 개수 알리기
	return 1;
}

void printCurrentLuaStack(lua_State *L)
{
	lua_Debug dbg;
	int top = lua_gettop(L);
	std::cout << "stack top position = " << top << std::endl;
	// for (int i = 1; i < LUAI_MAXSTACK; i++)
	for (int i = 1; i <= top; i++)
	{
		if (lua_isnil(L, -i))
		{
			std::cout << "stack(-" << i << ") = nil  " << std::endl;
			break;
		}
		else if (lua_isboolean(L, -i))
		{
			std::cout << "stack(-" << i << ") = bool,  " << lua_toboolean(L, -i) << std::endl;
		}
		else if (lua_isinteger(L, -i))
		{
			std::cout << "stack(-" << i << ") = integer, " << lua_tointeger(L, -i) << std::endl;
		}
		else if (lua_isnumber(L, -i))
		{
			std::cout << "stack(-" << i << ") = number, " << lua_tonumber(L, -i) << std::endl;
		}
		else if (lua_isstring(L, -i))
		{
			std::cout << "stack(-" << i << ") = string, " << lua_tostring(L, -i) << std::endl;
		}
		else if (lua_istable(L, -i))
		{
			std::cout << "stack(-" << i << ") = table, " << lua_topointer(L, -i) << std::endl;
		}
	}
}

int main(int argc, char *argv[])
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

	printCurrentLuaStack(L);

	std::cout << "C --> Lua" << std::endl;

	// lua 함수 호출
	// 파라미터 4개를 전달하고 리턴 1개 받음
	lua_call(L, 4, 1);

	// lua_call 이후 L 스택은 lua 함수 결과 하나만 들어가 있다.
	printCurrentLuaStack(L);

	// 스택(minus indexing)에 쌓인 리턴 결과 파악
	std::cout << "result from Lua = " << lua_tonumber(L, -1) << std::endl;

	// pop 을 해주지 않으면 스택이 계속 쌓인다.
	// lua_pop 은 내부적으로 lua_settop 으로 스택 위치를 설정
	// 스택에서 1개를 pop 한다.
	lua_pop(L, 1);

	printCurrentLuaStack(L);

	std::cout << "---------------------------" << std::endl;

	// lua 스크립트의 myfunc2 함수 가져오기
	lua_getglobal(L, "myfunc2");

	// lua 함수에 테이블을 파라미터로 전달하기
	// 다음과 모양의 테이블 만들기
	// {
	// 	title : "this is title"
	// 	date : "2010-12-31"
	//	[
	// 		{
	// 			"name" : "ysoftman1",
	// 			"age" : 10
	// 		},
	// 		{
	// 			"name" : "ysoftman2",
	// 			"age" : 20
	// 		}
	// 	]
	// }
	// 상위 테이블 생성
	// lua 내부적으로 별도의 신규(가상의) 스택을 만들다.
	// 스택 top은 실제 신규 테이블 포인터 값을 가진다.
	lua_newtable(L);

	lua_pushstring(L, "this is title");
	lua_setfield(L, -2, "title");
	lua_pushstring(L, "2010-12-31");
	lua_setfield(L, -2, "date");

	for (int i = 1; i < 3; i++)
	{
		std::string name = "ysoftman" + std::to_string(i);
		int age = i * 10;

		// 내부테이블의 인덱스를 위해
		lua_pushinteger(L, i);

		// 내부테이블 생성
		lua_newtable(L);
		// 스택에 top 에 ysoftman 푸시
		lua_pushstring(L, name.c_str());
		// 현재 스택의 -2 위치는 위에 새로 만든 테이블로 이 테이블에 필드를 설정한다는 의미
		// 현재 스택의 top 값의 키로 name 설정
		lua_setfield(L, -2, "name");
		lua_pushnumber(L, age);
		lua_setfield(L, -2, "age");

		// 위에서 설정한 인덱스로의 값으로 내부테이블 설정(연결)
		lua_settable(L, -3);
	}

	printCurrentLuaStack(L);

	std::cout << "C --> Lua" << std::endl;

	// lua 함수 호출
	// 파라미터 1개를 전달하고 리턴 1개 받은
	lua_call(L, 1, 1);

	printCurrentLuaStack(L);

	// 스택(minus indexing)에 쌓인 리턴 결과 파악
	std::cout << "result from Lua = " << lua_tostring(L, -1) << std::endl;

	// pop 을 해주지 않으면 스택이 계속 쌓인다.
	// lua_pop 은 내부적으로 lua_settop 으로 스택 위치를 설정
	// 스택에서 1개를 pop 한다.
	lua_pop(L, 1);

	printCurrentLuaStack(L);

	// lua state 제거
	lua_close(L);

	return 0;
}
