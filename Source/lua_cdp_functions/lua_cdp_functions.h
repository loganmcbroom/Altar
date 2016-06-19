#pragma once

#include <string>

struct lua_State;

//Lua function used for calling arbitrary cdp modules
int cdp( lua_State * L, const std::string & info = "" );

void register_lua_cdp_functions( lua_State * L );
