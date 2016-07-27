#pragma once

#include "lua_cdp_utilities.h"

///Bad flags
//LUA_CDP_MODAL_MULTI( lua_cdp_strange_glis, {
//	case 1: LINEAR_MULTI_NPROC_TYPE( "strange", "glis 1", 
//	})

LUA_CDP_MODAL_MULTI( lua_cdp_strange_invert, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "strange", "invert 1", 0, 0, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "strange", "invert 2", 0, 0, WAV_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_strange_shift, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "strange", "shift 1", 1, 1, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "strange", "shift 2", 2, 1, WAV_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "strange", "shift 3", 2, 1, WAV_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "strange", "shift 4", 3, 1, WAV_TYPE, 1 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "strange", "shift 5", 3, 1, WAV_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_strange_waver, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "strange", "waver 1", 3, 0, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "strange", "waver 2", 3, 0, WAV_TYPE, 1 );
	})

void register_lua_cdp_functions_strange( lua_State * L )
	{
	//lua_register( L, "strange_glis",		lua_cdp_strange_glis		);
	lua_register( L, "strange_invert",		lua_cdp_strange_invert		);
	lua_register( L, "strange_shift",		lua_cdp_strange_shift		);
	lua_register( L, "strange_waver",		lua_cdp_strange_waver		);
	}