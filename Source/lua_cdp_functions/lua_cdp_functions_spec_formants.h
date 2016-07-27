#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_NPROC_TYPE_FUNC_2( formants, get, 0, 2, BIN_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( formants, getsee, 0, 3, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_formants_put, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "formants", "put 1", 0, 4, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "formants", "put 2", 0, 3, WAV_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( formants, see, 0, 1, WAV_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( formants, vocode, 0, 5, WAV_TYPE, 2 )


void register_lua_cdp_functions_formants( lua_State * L )
	{
	lua_register( L, "formants_get",		lua_cdp_formants_get			);
	lua_register( L, "formants_getsee",	lua_cdp_formants_getsee			);
	lua_register( L, "formants_put",		lua_cdp_formants_put			);
	lua_register( L, "formants_see",		lua_cdp_formants_see			);
	lua_register( L, "formants_vocode",	lua_cdp_formants_vocode			);
	}