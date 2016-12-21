#pragma once

#include "lua_cdp_utilities.h"

LUA_ERROR_FUNC( focus_accu, "Use Focus Superaccu over Focus Accu" );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, exag, 1, 0, ANA_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, focus, 2, 5, ANA_TYPE, 1 ) //Test this, it has dork flags
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, fold, 2, 1, ANA_TYPE, 1 ) 
LUA_CDP_MODAL_MULTI( lua_cdp_focus_freeze, {
	case 1: LINEAR_MULTI_PROC_TYPE( "focus", "freeze 1", 1, 0, ANA_TYPE );
	case 2: LINEAR_MULTI_PROC_TYPE( "focus", "freeze 2", 1, 0, ANA_TYPE );
	case 3: LINEAR_MULTI_PROC_TYPE( "focus", "freeze 3", 1, 0, ANA_TYPE );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, hold, 1, 0, ANA_TYPE, 1 ) 
LINEAR_MULTI_NPROC_TYPE_FUNC_2( focus, step, 1, 0, ANA_TYPE, 1 ) 
LUA_CDP_MODAL_MULTI( lua_cdp_superaccu_superaccu, {
	case 1: LINEAR_MULTI_PROC_TYPE( "superaccu", "superaccu 1", 0, 3, ANA_TYPE );
	case 2: LINEAR_MULTI_PROC_TYPE( "superaccu", "superaccu 2", 0, 3, ANA_TYPE );
	case 3: LINEAR_MULTI_PROC_TYPE( "superaccu", "superaccu 3", 1, 3, ANA_TYPE );
	case 4: LINEAR_MULTI_PROC_TYPE( "superaccu", "superaccu 4", 1, 3, ANA_TYPE );
	})


void register_lua_cdp_functions_focus( lua_State * L )
	{
	lua_register( L, "focus_accu",		lua_cdp_focus_accu			);
	lua_register( L, "focus_exag",		lua_cdp_focus_exag			);
	lua_register( L, "focus_focus",		lua_cdp_focus_focus			);
	lua_register( L, "focus_fold",		lua_cdp_focus_fold			);
	lua_register( L, "focus_freeze",	lua_cdp_focus_freeze		);
	lua_register( L, "focus_hold",		lua_cdp_focus_hold			);
	lua_register( L, "focus_step",		lua_cdp_focus_step			);
	lua_register( L, "focus_superaccu",	lua_cdp_superaccu_superaccu	);
	}