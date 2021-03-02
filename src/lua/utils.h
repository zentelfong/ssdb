#ifndef _LUA_UTILS_H_
#define _LUA_UTILS_H_

extern "C" {
#include "lua.h"
#include "lauxlib.h"
}


//used for resume lua stack
class LuaScope 
{
public:
	LuaScope(lua_State* l)
		:L(l),top(lua_gettop(l))
	{
	}

	~LuaScope() {
		lua_settop(L, top);
	}
private:
	lua_State* L;
	int top;
};





#endif

