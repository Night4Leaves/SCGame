#include "HelloLua.h"

HelloLua::HelloLua()
{
}

HelloLua::~HelloLua()
{
}

bool HelloLua::init()
{
	lua_State* pl = lua_open();
	luaopen_base(pl);
	
	lua_register(pl, "cpp_GetNumber", cpp_GetNumber);

	int err = luaL_dofile(pl, "helloLua.lua");
	log("open : %d", err);

	lua_close(pl);
	return true;
}

int HelloLua::getNumber(int num)
{
	log("getNumber num = %d", num);
	return num + 1;
}

int HelloLua::cpp_GetNumber(lua_State * pl)
{
	int num = (int)lua_tonumber(pl, 1);

	lua_pushnumber(pl, getNumber(num));

	return 1;
}
