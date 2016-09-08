///////////////////////////////////////////////////////////
// c_for_lua.cpp
// ysoftman
// Lua <-> C ���� �׽�Ʈ
#include "iostream"

#ifdef _WIN32
// ��� ��ġ������ include �� lib ��� �߰�(Windows ����)
// C:\Program Files (x86)\Lua\5.1\include
// C:\Program Files (x86)\Lua\5.1\lib
// lua lib ��ũ
#pragma comment(lib , "lua5.1.lib")

#elif __APPLE__
// curl -R -O http://www.lua.org/ftp/lua-5.3.3.tar.gz
// tar zxf lua-5.3.3.tar.gz
// cd lua-5.3.3
// make macosx test
// cd ..
// g++ c_for_lua.cpp -L./lua-5.3.3/src -llua
#endif

// lua(C �� �������) ��� include
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// ��ƿ��� ȣ�� �� �� �ִ� �Լ�(int funcname(lua_State* L) �����̾�� �Ѵ�)
int DoSomethingForLua(lua_State *L)
{
	std::cout << "DoSomethingForLua() called." << std::endl;

	// ��ƿ��� ���� ���ڵ� �ľ�
	int a = luaL_checkint(L, 1);
	int b = luaL_checkint(L, 2);
	int c = luaL_checkint(L, 3);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;

	// ��ƿ� ���ÿ� ��� �ֱ�
	lua_pushinteger(L, a+b+c);

	// ��ƿ� ���� ���� �˸���
	return 1;
}

int main(int argc, char* argv[])
{
	std::cout << "c_for_lua test start..." << std::endl;

	// ��� state ����
	lua_State *L = luaL_newstate();
	// ��� ���̺귯�� ����
	luaL_openlibs(L);

	// ��ƿ��� C �Լ��� ȣ�� �� �� �ֵ��� C �Լ� ���
	lua_register(L, "DoSomething", DoSomethingForLua);

	// ��� ���� ����
	// luaL_dofile �� luaL_loadfile(��� �ε�) �� lua_pcall(��� �ʱ�ȭ) �� ��ģ��
	luaL_dofile(L, "lua_for_c.lua");


	// ��� ��ũ��Ʈ�� myfunc1 �Լ� ��������
	lua_getglobal(L, "myfunc1");

	// ��� �Լ��� ������ �Ķ���� ���ÿ� �ֱ�
	lua_pushboolean(L, true);
	lua_pushinteger(L, 99999);
	lua_pushnumber(L, 123.456);
	lua_pushstring(L, "string");
	
	std::cout << "---------------------------" << std::endl;
	std::cout << "C --> Lua" << std::endl;
	
	// ��� �Լ� ȣ��
	// �Ķ���� 4���� �����ϰ� ���� 1�� ����
	lua_call(L, 4, 1);

	// ����(minus indexing)�� ���� ���� ��� �ľ�
	std::cout << "result from Lua = " << lua_tonumber(L, -1) << std::endl;
	std::cout << "---------------------------" << std::endl;
	
	// pop �� ������ ������ ������ ��� ���δ�.
	// ���������� lua_settop ���� ���� ��ġ�� ����
	lua_pop(L, 1);
	
	// ��� ��ũ��Ʈ�� myfunc2 �Լ� ��������
	lua_getglobal(L, "myfunc2");
		
	// ��� �Լ��� ������ �Ķ���� ���ÿ� �ֱ�
	lua_pushnumber(L, 5);
	lua_pushnumber(L, 5);
	
	std::cout << "---------------------------" << std::endl;
	std::cout << "C --> Lua" << std::endl;
	
	// ��� �Լ� ȣ��
	// �Ķ���� 2���� �����ϰ� ���� 1�� ����
	lua_call(L, 2, 1);

	// ����(minus indexing)�� ���� ���� ��� �ľ�
	std::cout << "result from Lua = " << lua_tonumber(L, -1) << std::endl;
	std::cout << "---------------------------" << std::endl;	
	
	// pop �� ������ ������ ������ ��� ���δ�.
	// ���������� lua_settop ���� ���� ��ġ�� ����
	lua_pop(L, 1);

	// ��� state ����
	lua_close(L);

	return 0;
}

