#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_baktobak, "extend", "baktobak", 2, 0 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_ceracu_ceracu, "ceracu", "ceracu", 6, 2 )
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
	case 1: LINEAR_MULTI_PROC( "iterline", "iterline 1", 8, 1 );
	case 2: LINEAR_MULTI_PROC( "iterline", "iterline 2", 8, 1 );
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
LUA_CDP_MODAL_MULTI( lua_cdp_madrid_madrid, {
	case 1: NONLINEAR_PROC( madrid, madrid 1, 6, 5, WAV_TYPE );
	case 2: NONLINEAR_PROC( madrid, madrid 2, 6, 3, WAV_TYPE );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_repetitions, "extend", "repetitions", 2, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_extend_scramble, {
	case 1: LINEAR_MULTI_PROC( "extend", "scramble 1", 3, 4 );
	case 2: LINEAR_MULTI_PROC( "extend", "scramble 2", 3, 4 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_extend_sequence, "extend", "sequence", 2, 0 )
NONLINEAR_PROC_FUNC_TYPE( extend, sequence2, 2, 0, WAV_TYPE )
LUA_CDP_MODAL_MULTI( lua_cdp_shifter_shifter, { //8 is correct for these 2
	case 1: LINEAR_MULTI_PROC( "shifter", "shifter 1", 8, 2 );
	case 2: NONLINEAR_PROC( shifter, shifter 2, 8, 2, WAV_TYPE );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_extend_shrink, {
	case 1:  LINEAR_MULTI_PROC( "shrink", "shrink 1",  5, 5 );
	case 2:  LINEAR_MULTI_PROC( "shrink", "shrink 2",  5, 5 );
	case 3:  LINEAR_MULTI_PROC( "shrink", "shrink 3",  5, 5 );
	case 4:  LINEAR_MULTI_PROC( "shrink", "shrink 4",  6, 5 );
	case 5: return lua_multi_proc( L, 5, 10, []( lua_State * L )
		{
		lua_pushpairs( L, { {"shrink", 1}, {"shrink 5", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	case 6: return lua_multi_proc( L, 6, 9, []( lua_State * L )
		{
		lua_pushpairs( L, { {"shrink", 1}, {"shrink 6", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	})
LUA_CDP_MODAL_MULTI( lua_cdp_extend_zigzag, {
	case 1: LINEAR_MULTI_PROC( "extend", "zigzag 1", 4, 3 );
	case 2: LINEAR_MULTI_PROC( "extend", "zigzag 2", 1, 1 );
	})



void register_lua_cdp_functions_extend( lua_State * L )
	{
	lua_register( L, "extend_baktobak", lua_cdp_extend_baktobak );
	lua_register( L, "extend_ceracu", lua_cdp_ceracu_ceracu );
	lua_register( L, "extend_doublets", lua_cdp_extend_doublets );
	lua_register( L, "extend_drunk", lua_cdp_extend_drunk );
	lua_register( L, "extend_echo", lua_cdp_sfecho_echo );
	lua_register( L, "extend_freeze", lua_cdp_extend_freeze );
	lua_register( L, "extend_hover", lua_cdp_hover_hover );
	lua_register( L, "extend_iterate", lua_cdp_extend_iterate );
	lua_register( L, "extend_iterline", lua_cdp_iterline_iterline );
	lua_register( L, "extend_iterlinef", lua_cdp_iterlinef_iterlinef );
	lua_register( L, "extend_loop", lua_cdp_extend_loop );
	lua_register( L, "extend_madrid", lua_cdp_madrid_madrid );
	lua_register( L, "extend_repetitions", lua_cdp_extend_repetitions );
	lua_register( L, "extend_scramble", lua_cdp_extend_scramble );
	lua_register( L, "extend_sequence", lua_cdp_extend_sequence );
	lua_register( L, "extend_sequence2", lua_cdp_extend_sequence2 );
	lua_register( L, "extend_shifter", lua_cdp_shifter_shifter );
	lua_register( L, "extend_shrink", lua_cdp_extend_shrink );
	lua_register( L, "extend_zigzag", lua_cdp_extend_zigzag );
	}