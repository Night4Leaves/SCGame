#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

#include "cocos2d.h"

USING_NS_CC;

class HelloLua : public Layer
{
public:
	HelloLua();
	virtual ~HelloLua();
	CREATE_FUNC(HelloLua);
	virtual bool init();

	static int getNumber(int num);
	
	static int cpp_GetNumber(lua_State* pl);
};