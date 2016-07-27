#pragma once

#include "lua_cdp_utilities.h"

LUA_ERROR_FUNC( focus_accu, "Use Focus Superaccu over Focus Accu" );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, exag, 1, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, focus, 2, 5, WAV_TYPE, 1 ) //Test this, it has dork flags
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, fold, 2, 1, WAV_TYPE, 1 ) 
LUA_CDP_MODAL_MULTI( lua_cdp_focus_freeze, {
	case 1: LINEAR_MULTI_PROC( "focus", "freeze 1", 1, 0 );
	case 2: LINEAR_MULTI_PROC( "focus", "freeze 2", 1, 0 );
	case 3: LINEAR_MULTI_PROC( "focus", "freeze 3", 1, 0 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, hold, 1, 0, WAV_TYPE, 1 ) 
LUA_CDP_MODAL_MULTI( lua_cdp_superaccu_superaccu, {
	case 1: LINEAR_MULTI_PROC( "superaccu", "superaccu 1", 0, 3 );
	case 2: LINEAR_MULTI_PROC( "superaccu", "superaccu 2", 0, 3 );
	case 3: LINEAR_MULTI_PROC( "superaccu", "superaccu 3", 1, 3 );
	case 4: LINEAR_MULTI_PROC( "superaccu", "superaccu 4", 1, 3 );
	})


void register_lua_cdp_functions_focus( lua_State * L )
	{
	lua_register( L, "focus_accu",		lua_cdp_focus_accu			);
	lua_register( L, "focus_exag",		lua_cdp_focus_exag			);
	lua_register( L, "focus_focus",		lua_cdp_focus_focus			);
	lua_register( L, "focus_fold",		lua_cdp_focus_fold			);
	lua_register( L, "focus_freeze",	lua_cdp_focus_freeze		);
	lua_register( L, "focus_hold",		lua_cdp_focus_hold			);
	lua_register( L, "focus_superaccu",	lua_cdp_superaccu_superaccu	);

	}