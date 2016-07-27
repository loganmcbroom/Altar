#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_filter_bank, {
	case 1: LINEAR_MULTI_PROC( "filter", "bank 1", 4, 2 );
	case 2: LINEAR_MULTI_PROC( "filter", "bank 2", 4, 2 );
	case 3: LINEAR_MULTI_PROC( "filter", "bank 3", 4, 2 );
	case 4: LINEAR_MULTI_PROC( "filter", "bank 4", 5, 2 );
	case 5: LINEAR_MULTI_PROC( "filter", "bank 5", 5, 2 );
	case 6: LINEAR_MULTI_PROC( "filter", "bank 6", 5, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_bankfrqs, {
	case 1: LINEAR_MULTI_PROC_TYPE( "filter", "bankfrqs 1", 2, 1, TXT_TYPE );
	case 2: LINEAR_MULTI_PROC_TYPE( "filter", "bankfrqs 2", 2, 1, TXT_TYPE );
	case 3: LINEAR_MULTI_PROC_TYPE( "filter", "bankfrqs 3", 2, 1, TXT_TYPE );
	case 4: LINEAR_MULTI_PROC_TYPE( "filter", "bankfrqs 4", 3, 1, TXT_TYPE );
	case 5: LINEAR_MULTI_PROC_TYPE( "filter", "bankfrqs 5", 3, 1, TXT_TYPE );
	case 6: LINEAR_MULTI_PROC_TYPE( "filter", "bankfrqs 6", 3, 1, TXT_TYPE );
	})
int lua_cdp_filter_filtrage( lua_State * L )
	{ 
	lua_pushpairs( L, { {"filtrage", 1}, {"filtrage", 2}, {TXT_TYPE, 4} } );
	return cdp( L );
	}
LUA_CDP_MODAL_MULTI( lua_cdp_filter_fixed, {
	case 1: LINEAR_MULTI_PROC( "filter", "fixed 1", 2, 1 );
	case 2: LINEAR_MULTI_PROC( "filter", "fixed 2", 2, 1 );
	case 3: LINEAR_MULTI_PROC( "filter", "fixed 3", 3, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_iterated, {
	case 1: LINEAR_MULTI_PROC( "filter", "fixed 1", 5, 8 );
	case 2: LINEAR_MULTI_PROC( "filter", "fixed 2", 5, 8 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_lohi, {
	case 1: LINEAR_MULTI_PROC( "filter", "lohi 1", 3, 1 );
	case 2: LINEAR_MULTI_PROC( "filter", "lohi 2", 3, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_phasing, {
	case 1: LINEAR_MULTI_PROC( "filter", "phasing 1", 2, 2 );
	case 2: LINEAR_MULTI_PROC( "filter", "phasing 2", 2, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_sweeping, {
	case 1: LINEAR_MULTI_PROC( "filter", "sweeping 1", 5, 1 );
	case 2: LINEAR_MULTI_PROC( "filter", "sweeping 2", 5, 1 );
	case 3: LINEAR_MULTI_PROC( "filter", "sweeping 3", 5, 1 );
	case 4: LINEAR_MULTI_PROC( "filter", "sweeping 4", 5, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_userbank, {
	case 1: LINEAR_MULTI_PROC( "filter", "userbank 1", 3, 1 );
	case 2: LINEAR_MULTI_PROC( "filter", "userbank 2", 3, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_variable, {
	case 1: LINEAR_MULTI_PROC( "filter", "variable 1", 3, 0 );
	case 2: LINEAR_MULTI_PROC( "filter", "variable 2", 3, 0 );
	case 3: LINEAR_MULTI_PROC( "filter", "variable 3", 3, 0 );
	case 4: LINEAR_MULTI_PROC( "filter", "variable 4", 3, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_varibank, {
	case 1: LINEAR_MULTI_PROC( "filter", "varibank 1", 3, 3 );
	case 2: LINEAR_MULTI_PROC( "filter", "varibank 2", 3, 3 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_filter_varibank2, {
	case 1: LINEAR_MULTI_PROC( "filter", "varibank2 1", 3, 3 );
	case 2: LINEAR_MULTI_PROC( "filter", "varibank2 2", 3, 3 );
	})
int lua_cdp_filters_vfilters( lua_State * L )
	{
	return luaL_error( L, "Filter VFilters isn't supported but it will be if you ask" );
	}

void register_lua_cdp_functions_filter( lua_State * L )
	{
	lua_register( L, "filter_bank",		lua_cdp_filter_bank			);
	lua_register( L, "filter_bankfrqs",	lua_cdp_filter_bankfrqs		);
	lua_register( L, "filter_filtrage",	lua_cdp_filter_filtrage		);
	lua_register( L, "filter_fixed",		lua_cdp_filter_fixed		);
	lua_register( L, "filter_iterated",	lua_cdp_filter_iterated		);
	lua_register( L, "filter_lohi",		lua_cdp_filter_lohi			);
	lua_register( L, "filter_phasing",		lua_cdp_filter_phasing		);
	lua_register( L, "filter_sweeping",	lua_cdp_filter_sweeping		);
	lua_register( L, "filter_userbank",	lua_cdp_filter_userbank		);
	lua_register( L, "filter_variable",	lua_cdp_filter_variable		);
	lua_register( L, "filter_varibank",	lua_cdp_filter_varibank		);
	lua_register( L, "filter_varibank2",	lua_cdp_filter_varibank2	);
	lua_register( L, "filter_vfilters",	lua_cdp_filters_vfilters	);
	}