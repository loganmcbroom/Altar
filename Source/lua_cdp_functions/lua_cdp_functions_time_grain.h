#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_NPROC_TYPE_FUNC_2( grain, align, 2, 5, WAV_TYPE, 2 )
LUA_CDP_UNSUPPORTED( lua_cdp_grain_assess )
LUA_CDP_UNSUPPORTED( lua_cdp_grain_count )
LINEAR_MULTI_PROC_FUNC_2( grain, duplicate, 1, 5 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( grain, find, 1, 5, TXT_TYPE, 1 )
LINEAR_MULTI_PROC_FUNC_2( grain, extend, 4, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_grain_grev, {
	case 1: LINEAR_MULTI_PROC( "grain", "grev 1", 3, 0 );
	case 2: LINEAR_MULTI_PROC( "grain", "grev 2", 4, 0 );
	case 3: LINEAR_MULTI_PROC( "grain", "grev 3", 5, 0 );
	case 4: LINEAR_MULTI_PROC( "grain", "grev 4", 5, 0 );
	case 5: LINEAR_MULTI_PROC( "grain", "grev 5", 4, 0 );
	case 6: LINEAR_MULTI_PROC_TYPE( "grain", "grev 6", 3, 0, TXT_TYPE );
	case 7: LINEAR_MULTI_PROC( "grain", "grev 7", 4, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_newtex_newtex, {
	case 1: LINEAR_MULTI_PROC( "newtex", "newtex 1", 6, 9 );
	case 2: NONLINEAR_PROC( "newtex", "newtex 2", 6, 9, WAV_TYPE ); 
	case 3: NONLINEAR_PROC( "newtex", "newtex 3", 6, 9, WAV_TYPE ); 
	})
LINEAR_MULTI_PROC_FUNC_2( grain, noise_extend, 4, 1 )
LINEAR_MULTI_PROC_FUNC_2( grain, omit, 2, 5 )
LUA_CDP_MODAL_MULTI( lua_cdp_grain_remotif, {
	case 1: LINEAR_MULTI_PROC("grain", "remotif 1", 1, 5 );
	case 2: LINEAR_MULTI_PROC("grain", "remotif 2", 1, 5 );
	})
LINEAR_MULTI_PROC_FUNC_2( grain, reorder, 1, 5 )
LUA_CDP_MODAL_MULTI( lua_cdp_grain_repitch, {
	case 1: LINEAR_MULTI_PROC("grain", "repitch 1", 1, 5 );
	case 2: LINEAR_MULTI_PROC("grain", "repitch 2", 1, 5 );
	})
LINEAR_MULTI_PROC_FUNC_2( grain, reposition, 2, 5 )
LUA_CDP_MODAL_MULTI( lua_cdp_grain_rerhythm, {
	case 1: LINEAR_MULTI_PROC("grain", "rerhythm 1", 1, 5 );
	case 2: LINEAR_MULTI_PROC("grain", "rerhythm 2", 1, 5 );
	})
LINEAR_MULTI_PROC_FUNC_2( grain, reverse, 0, 5 )
LUA_CDP_MODAL_MULTI( lua_cdp_grain_r_extend, {
	case 1: LINEAR_MULTI_PROC("grain", "r_extend 1", 8, 1 );
	case 2: LINEAR_MULTI_PROC("grain", "r_extend 2", 12, 2 );
	case 3: LINEAR_MULTI_PROC("grain", "r_extend 3", 12, 2 );
	})
LINEAR_MULTI_PROC_FUNC_2( grain, timewarp, 1, 5 )
NONLINEAR_PROC_FUNC( wrappage, wrappage, 21, 3 )


void register_lua_cdp_functions_grain( lua_State * L )
	{
	lua_register( L, "grain_align",			lua_cdp_grain_align			);
	lua_register( L, "grain_assess",		lua_cdp_grain_assess		);
	lua_register( L, "grain_count",			lua_cdp_grain_count			);
	lua_register( L, "grain_duplicate",		lua_cdp_grain_duplicate		);
	lua_register( L, "grain_find",			lua_cdp_grain_find			);
	lua_register( L, "grain_extend",		lua_cdp_grain_extend		);
	lua_register( L, "grain_grev",			lua_cdp_grain_grev			);
	lua_register( L, "grain_newtex",		lua_cdp_newtex_newtex		);
	lua_register( L, "grain_noise_extend",	lua_cdp_grain_noise_extend	);
	lua_register( L, "grain_omit",			lua_cdp_grain_omit			);
	lua_register( L, "grain_remotif",		lua_cdp_grain_remotif		);
	lua_register( L, "grain_reorder",		lua_cdp_grain_reorder		);
	lua_register( L, "grain_repitch",		lua_cdp_grain_repitch		);
	lua_register( L, "grain_reposition",	lua_cdp_grain_reposition	);
	lua_register( L, "grain_rerhythm",		lua_cdp_grain_rerhythm		);
	lua_register( L, "grain_reverse",		lua_cdp_grain_reverse		);
	lua_register( L, "grain_r_extend",		lua_cdp_grain_r_extend		);
	lua_register( L, "grain_timewarp",		lua_cdp_grain_timewarp		);
	lua_register( L, "grain_wrappage",		lua_cdp_wrappage_wrappage	);
	}