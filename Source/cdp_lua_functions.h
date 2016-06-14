#pragma once

struct lua_State;

void registerCdpLuaFunctions( lua_State * L );

/* Lua Interface

Token replacement:
	$ -> generated .wav file name

cdp( moduleName, arg1, arg2, arg3, ... )

Modify
	cdp_normalize( infile, volume = 0.9 )

*/