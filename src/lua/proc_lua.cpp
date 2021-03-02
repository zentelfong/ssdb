/*
Copyright (c) 2012-2018 The SSDB Authors. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
*/
#include "proc_lua.h"
#include "utils.h"
#include "sha1.h"

int proc_eval(NetworkServer *net, Link *link, const Request &req, Response *resp){
	CHECK_NUM_PARAMS(1);

	SSDBServer *serv = (SSDBServer *)net->data;
	lua_State* L = net->lua;

	LuaScope lscope(L);

	char key[32];
	SHA1(key,req[0].data(), req[0].size());

	//get loaded script
	lua_pushstring(L, key);
	lua_gettable(L, LUA_REGISTRYINDEX);

	if (!lua_isfunction(L, -1)) {
		//load script
		lua_pop(L, -1); //pop nil
		if (luaL_loadbuffer(L, req[0].data(), req[0].size(), key) == 0) {

			//set upvalue
			lua_newtable(L);
			lua_setupvalue(L, -2, 1);

			lua_pushstring(L, key);
			lua_pushvalue(L, -2);
			lua_settable(L,LUA_REGISTRYINDEX);
		} else {
			//script error
			resp->push_back("error");
			resp->push_back(lua_tostring(L, -1));
			return 0;
		}
	}

	//push args
	lua_newtable(L);
	for (size_t i = 1; i < req.size(); ++i) {
		lua_pushlstring(L,req[i].data(), req[i].size());
		lua_seti(L, -2, i);
	}


	//run script
	int rslt = lua_pcall(L, 0, 1, 0);
	if (rslt < 0) {
		//call error
		resp->push_back("error");
		resp->push_back(lua_tostring(L, -1));
		return 0;
	}

	int type = lua_type(L, -1);
	resp->push_back("ok");

	switch (type) {
	case LUA_TSTRING:
		resp->push_back(lua_tostring(L, -1));
		break;
	case LUA_TNUMBER:
		resp->push_back(std::to_string(lua_tonumber(L,-1)));
		break;
	case LUA_TBOOLEAN:
		resp->push_back(lua_toboolean(L, -1)?"true":"false");
		break;
	case LUA_TTABLE:

		break;
	}
	return 0;
}


