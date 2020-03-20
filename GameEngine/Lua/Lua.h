#ifndef LUA_H
#define LUA_H
#include <iostream>
#include <string>
using namespace std;

extern "C" {
#include "../../Lua53/include/lua.h" 
#include "../../Lua53/include/lauxlib.h" 
#include "../../Lua53/include/lualib.h" 
}

#ifdef _WIN32

#pragma comment(lib, "../../Lua53/liblua53.a")

#endif // _WIN32

class Lua {
public:
	static Lua* GetPTR();
	lua_State* GetState();
	void SetState(lua_State*);
	void Test(string fileName);
	void TestCallFunctionFromCPP(string fileName);
	void Lua_MoveObject(string fileName);
	void Lua_CreatePrimitve(string fileName);
	bool CheckLua(lua_State* l, int r);
private:
	static Lua* ptr;
	Lua();
	~Lua();
	lua_State* lua_state;
};

#endif LUA_H