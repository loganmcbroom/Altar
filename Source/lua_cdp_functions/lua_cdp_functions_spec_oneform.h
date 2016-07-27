#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_NPROC_TYPE_FUNC_2( oneform, get, 1, 0, FOR_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_oneform_put, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "oneform", "put 1", 0, 3, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "oneform", "put 2", 0, 3, WAV_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( oneform, combine, 0, 0, WAV_TYPE, 2 )

void register_lua_cdp_functions_oneform( lua_State * L )
	{
	lua_register( L, "oneform_get",		lua_cdp_oneform_get		);
	lua_register( L, "oneform_put",		lua_cdp_oneform_put		);
	lua_register( L, "oneform_combine",	lua_cdp_oneform_combine	);
	}