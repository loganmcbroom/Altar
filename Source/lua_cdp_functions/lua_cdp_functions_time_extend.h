#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_baktobak, "extend", "baktobak", 2, 0 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_ceracu_cerasu, "cerasu", "cerasu", 6, 2 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_doublets, "extend", "doublets", 2, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_extend_drunk, {
	case 1: LINEAR_MULTI_PROC( "extend", "drunk 1", 5, 4 );
	case 2: LINEAR_MULTI_PROC( "extend", "drunk 2", 7, 7 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_sfecho_echo, "sfecho", "echo", 3, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_extend_freeze, {
	case 1: LINEAR_MULTI_PROC( "extend", "freeze 1", 8, 1 );
	case 2: LINEAR_MULTI_PROC( "extend", "freeze 2", 8, 1 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_hover_hover, "hover", "hover", 6, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_extend_iterate, {
	case 1: LINEAR_MULTI_PROC( "extend", "iterate 1", 1, 7 );
	case 2: LINEAR_MULTI_PROC( "extend", "iterate 2", 1, 7 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_iterline_iterline, {
	case 1: LINEAR_MULTI_PROC( "iterline", "iterline 1", 2, 7 );
	case 2: LINEAR_MULTI_PROC( "iterline", "iterline 2", 2, 7 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_iterlinef_iterlinef, {
	case 1: LINEAR_MULTI_PROC( "iterlinef", "iterlinef 1", 2, 7 );
	case 2: LINEAR_MULTI_PROC( "iterlinef", "iterlinef 2", 2, 7 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_extend_loop, {
	case 1: LINEAR_MULTI_PROC( "extend", "loop 1", 3, 3 );
	case 2: LINEAR_MULTI_PROC( "extend", "loop 2", 3, 4 );
	case 3: LINEAR_MULTI_PROC( "extend", "loop 3", 3, 4 );
	})
LUA_CDP_UNSUPPORTED( lua_cdp_madrid_madrid )
LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_repetitions, "extend", "repetitions", 2, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_extend_scramble, {
	case 1: LINEAR_MULTI_PROC( "extend", "scramble 1", 3, 4 );
	case 2: LINEAR_MULTI_PROC( "extend", "scramble 2", 3, 4 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_sequence, "extend", "sequence", 2, 0 )
LUA_CDP_UNSUPPORTED( lua_cdp_extend_sequence2 )
LUA_CDP_UNSUPPORTED( lua_cdp_shifter_shifter )
//shrink, listed under sfedit
LUA_CDP_MODAL_MULTI( lua_cdp_extend_zigzag, {
	case 1: LINEAR_MULTI_PROC( "extend", "zigzag 1", 4, 3 );
	case 2: LINEAR_MULTI_PROC( "extend", "zigzag 2", 1, 1 );
	})



void register_lua_cdp_functions_extend( lua_State * L )
	{
	lua_register( L, "extend_baktobak", lua_cdp_extend_baktobak );
	lua_register( L, "extend_cerasu", lua_cdp_ceracu_cerasu );
	lua_register( L, "extend_doublets", lua_cdp_extend_doublets );
	lua_register( L, "extend_drunk", lua_cdp_extend_drunk );
	lua_register( L, "extend_echo", lua_cdp_sfecho_echo );
	lua_register( L, "extend_freeze", lua_cdp_extend_freeze );
	lua_register( L, "extend_hover", lua_cdp_hover_hover );
	lua_register( L, "extend_iterate", lua_cdp_extend_iterate );
	lua_register( L, "extend_iterline", lua_cdp_iterline_iterline );
	lua_register( L, "extend_iterlinef", lua_cdp_iterlinef_iterlinef );
	lua_register( L, "extend_loop", lua_cdp_extend_loop );
	//lua_register( L, "extend_", lua_cdp_madrid_madrid );
	lua_register( L, "extend_repetitions", lua_cdp_extend_repetitions );
	lua_register( L, "extend_scramble", lua_cdp_extend_scramble );
	lua_register( L, "extend_sequence", lua_cdp_extend_sequence );
	//lua_register( L, "extend_", lua_cdp_extend_sequence2 );
	//lua_register( L, "extend_", lua_cdp_shifter_shifter );
	//lua_register( L, "extend_shrink", lua_cdp_shrink_shrink );
	lua_register( L, "extend_zigzag", lua_cdp_extend_zigzag );
	}