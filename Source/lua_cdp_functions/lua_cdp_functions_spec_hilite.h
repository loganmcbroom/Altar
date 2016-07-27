#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_hilite_arpeg, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 1", 2, 9, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 2", 2, 9, WAV_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 3", 2, 9, WAV_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 4", 2, 9, WAV_TYPE, 1 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 5", 2, 5, WAV_TYPE, 1 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 6", 2, 5, WAV_TYPE, 1 );
	case 7: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 7", 2, 5, WAV_TYPE, 1 );
	case 8: LINEAR_MULTI_NPROC_TYPE( "hilite", "arpeg 8", 2, 5, WAV_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( hilite, band, 1, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( hilite, bltr, 2, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_hilite_filter, {
	case 1:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 1",  2, 0, WAV_TYPE, 1 );
	case 2:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 2",  2, 0, WAV_TYPE, 1 );
	case 3:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 3",  2, 0, WAV_TYPE, 1 );
	case 4:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 4",  2, 0, WAV_TYPE, 1 );
	case 5:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 5",  3, 0, WAV_TYPE, 1 );
	case 6:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 6",  3, 0, WAV_TYPE, 1 );
	case 7:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 7",  3, 0, WAV_TYPE, 1 );
	case 8:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 8",  3, 0, WAV_TYPE, 1 );
	case 9:  LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 9",  3, 0, WAV_TYPE, 1 );
	case 10: LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 10", 3, 0, WAV_TYPE, 1 );
	case 11: LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 11", 4, 0, WAV_TYPE, 1 );
	case 12: LINEAR_MULTI_NPROC_TYPE( "hilite", "filter 12", 4, 0, WAV_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( glisten, glisten, 2, 3, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_hilite_greq, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "hilite", "greq 1", 1, 1, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "hilite", "greq 2", 1, 1, WAV_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( hilite, pluck, 1, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_hilite_trace, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "hilite", "trace 1", 1, 0, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "hilite", "trace 2", 2, 1, WAV_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "hilite", "trace 3", 2, 1, WAV_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "hilite", "trace 4", 3, 1, WAV_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( hilite, vowels, 5, 0, WAV_TYPE, 1 )


void register_lua_cdp_functions_hilite( lua_State * L )
	{
	lua_register( L, "hilite_arpeg",	lua_cdp_hilite_arpeg		);
	lua_register( L, "hilite_band",		lua_cdp_hilite_band			);
	lua_register( L, "hilite_bltr",		lua_cdp_hilite_bltr			);
	lua_register( L, "hilite_filter",	lua_cdp_hilite_filter		);
	lua_register( L, "hilite_glisten",	lua_cdp_glisten_glisten		);
	lua_register( L, "hilite_greq",		lua_cdp_hilite_greq			);
	lua_register( L, "hilite_pluck",	lua_cdp_hilite_pluck		);
	lua_register( L, "hilite_trace",	lua_cdp_hilite_trace		);
	lua_register( L, "hilite_vowels",	lua_cdp_hilite_vowels		);
	}