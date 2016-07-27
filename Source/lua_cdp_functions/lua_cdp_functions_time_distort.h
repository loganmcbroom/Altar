#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_average, "distort", "average", 1, 2 )
static int lua_cdp_distort_cyclecnt( lua_State * L )
	{
	return lua_multi_proc( L, 0, 0, []( lua_State * L )
		{  
		lua_pushpairs( L, { {"distort", 1}, {"cyclecnt", 2} } );
		return cdp( L );
		} );
	}
LUA_CDP_MODAL_MULTI( lua_cdp_distort_delete, {
	case 1: LINEAR_MULTI_PROC( "distort", "delete 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "distort", "delete 2", 1, 1 );
	case 3: LINEAR_MULTI_PROC( "distort", "delete 3", 1, 1 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_divide, "distort", "divide", 1, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_distort_envel, {
	case 1: LINEAR_MULTI_PROC( "distort", "envel 1", 1, 2 );
	case 2: LINEAR_MULTI_PROC( "distort", "envel 2", 1, 2 );
	case 3: LINEAR_MULTI_PROC( "distort", "envel 3", 2, 1 );
	case 4: LINEAR_MULTI_PROC( "distort", "envel 4", 2, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_distort_filter, {
	case 1: LINEAR_MULTI_PROC( "distort", "filter 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "distort", "filter 2", 1, 1 );
	case 3: LINEAR_MULTI_PROC( "distort", "filter 3", 2, 1 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_fractal, "distort", "fractal", 2, 1 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_harmonic, "distort", "harmonic", 1, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_distort_interact, {
	case 1: LINEAR_MULTI_NPROC( "distort", "interact 1", 0, 0, 2 );
	case 2: LINEAR_MULTI_NPROC( "distort", "interact 2", 0, 0, 2 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_interpolate, "distort", "interpolate", 1, 1 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_multiply, "distort", "multiply", 1, 1 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_omit, "distort", "omit", 2, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_distort_overload, {
	case 1: LINEAR_MULTI_PROC( "distort", "overload 1", 2, 0 );
	case 2: LINEAR_MULTI_PROC( "distort", "overload 2", 3, 0 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_pitch, "distort", "pitch", 1, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_distort_pulsed, {
	case 1: LINEAR_MULTI_PROC( "distort", "pulsed 1", 8, 2 );
	case 2: LINEAR_MULTI_PROC( "distort", "pulsed 2", 9, 2 );
	case 3: LINEAR_MULTI_PROC( "distort", "pulsed 3", 9, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_distort_reform, {
	case 1: LINEAR_MULTI_PROC( "distort", "reform 1", 0, 0 );
	case 2: LINEAR_MULTI_PROC( "distort", "reform 2", 0, 0 );
	case 3: LINEAR_MULTI_PROC( "distort", "reform 3", 0, 0 );
	case 4: LINEAR_MULTI_PROC( "distort", "reform 4", 0, 0 );
	case 5: LINEAR_MULTI_PROC( "distort", "reform 5", 0, 0 );
	case 6: LINEAR_MULTI_PROC( "distort", "reform 6", 0, 0 );
	case 7: LINEAR_MULTI_PROC( "distort", "reform 7", 0, 0 );
	case 8: LINEAR_MULTI_PROC( "distort", "reform 8", 1, 0 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_repeat, "distort", "repeat", 1, 2 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_repeat2, "distort", "repeat2", 1, 2 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_replace, "distort", "replace", 1, 1 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_replim, "distort", "replim", 1, 3 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_reverse, "distort", "reverse", 1, 0 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_shuffle, "distort", "shuffle", 1, 2 )
LINEAR_MULTI_PROC_FUNC( lua_cdp_distort_telescope, "distort", "telescope", 1, 2 )

void register_lua_cdp_functions_distort( lua_State * L )
	{
	lua_register( L, "distort_average",			lua_cdp_distort_average );
	lua_register( L, "distort_cyclecnt",		lua_cdp_distort_cyclecnt );
	lua_register( L, "distort_delete",			lua_cdp_distort_delete );
	lua_register( L, "distort_divide",			lua_cdp_distort_divide );
	lua_register( L, "distort_envel",			lua_cdp_distort_envel );
	lua_register( L, "distort_filter",			lua_cdp_distort_filter );
	lua_register( L, "distort_fractal",			lua_cdp_distort_fractal );
	lua_register( L, "distort_harmonic",		lua_cdp_distort_harmonic );
	lua_register( L, "distort_interact",		lua_cdp_distort_interact );
	lua_register( L, "distort_interpolate",		lua_cdp_distort_interpolate );
	lua_register( L, "distort_multiply",		lua_cdp_distort_multiply );
	lua_register( L, "distort_omit",			lua_cdp_distort_omit );
	lua_register( L, "distort_overload",		lua_cdp_distort_overload );
	lua_register( L, "distort_pitch",			lua_cdp_distort_pitch );
	lua_register( L, "distort_pulsed",			lua_cdp_distort_pulsed );
	lua_register( L, "distort_reform",			lua_cdp_distort_reform );
	lua_register( L, "distort_repeat",			lua_cdp_distort_repeat );
	lua_register( L, "distort_repeat2",			lua_cdp_distort_repeat2 );
	lua_register( L, "distort_replace",			lua_cdp_distort_replace );
	lua_register( L, "distort_replim",			lua_cdp_distort_replim );
	lua_register( L, "distort_reverse",			lua_cdp_distort_reverse );
	lua_register( L, "distort_shuffle",			lua_cdp_distort_shuffle );
	lua_register( L, "distort_telescope",		lua_cdp_distort_telescope );
	}