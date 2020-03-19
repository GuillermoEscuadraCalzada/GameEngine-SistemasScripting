#include "../Lua.h"

Lua::Lua()
{
}

Lua::~Lua()
{
}

void Lua::LoadFile(string fileName)
{
	try {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		if (CheckLua(L, luaL_dofile(L, fileName.c_str()))) {
			lua_getglobal(L, "AddStuff");
			if (lua_isfunction(L, -1)) {
				lua_pushnumber(L, 2.3f);
				lua_pushnumber(L, 5.5f);
				if (CheckLua(L, lua_pcall(L, 2, 1, 0))) {
					cout << "[C++] Called in Lua 'AddStuff(2.3f,  5.5f)', go: " << (float)lua_tonumber(L, -1) << endl;
				}
			}
		}
	}
	catch (...) {

	}
}

bool Lua::CheckLua(lua_State* l, int r)
{
	try {
		
		if (r != LUA_OK) {
			throw(false);
		}
		return true;
	}
	catch (bool b) {
		string errorMSG= lua_tostring(l, -1);
		cout << errorMSG << endl;
	}
	return false;
}
