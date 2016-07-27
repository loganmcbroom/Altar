#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_stretch_spectrum, {
	case 1: LINEAR_MULTI_PROC( "stretch", "spectrum 1", 3, 1 );
	case 2: LINEAR_MULTI_PROC( "stretch", "spectrum 2", 3, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_stretch_time, {
	case 1: LINEAR_MULTI_PROC( "stretch", "time 1", 1, 0 );
	case 2: LINEAR_MULTI_INFO_PROC( "stretch", "time 2", 1, 0 );
	})
LUA_ERROR_FUNC( stretcha, "I do not understand the syntax of stretcha" );

void register_lua_cdp_functions_stretch( lua_State * L )
	{
	lua_register( L, "stretch_spectrum",	lua_cdp_stretch_spectrum	);
	lua_register( L, "stretch_time",		lua_cdp_stretch_time		);
	lua_register( L, "stretch_stretcha",	lua_cdp_stretcha			);
	}