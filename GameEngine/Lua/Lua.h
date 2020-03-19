#ifndef LUA_H
#define LUA_H
#include <iostream>
using namespace std;
extern "C" {
#include "../../Lua53/include/lua.h" 
#include "../../Lua53/include/lauxlib.h" 
#include "../../Lua53/include/lualib.h" 
}

#ifdef _WIN32
#pragma comment(lib, "../Lua53/lib_lua.a")
#endif // _WIN32

class Lua {
public:

	Lua();
	~Lua();

	void LoadFile(string fileName);
	bool CheckLua(lua_State* l, int r);

};

#endif LUA_H