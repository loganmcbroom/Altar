#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_NPROC_TYPE_FUNC_2( combine, cross, 0, 1, ANA_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( combine, diff, 0, 2, ANA_TYPE, 2 )
NONLINEAR_PROC_FUNC( combine, interleave, 1, 0 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( combine, make, 0, 0, ANA_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( combine, make2, 0, 0, ANA_TYPE, 3 )
NONLINEAR_PROC_FUNC_TYPE( combine, max, 0, 0, ANA_TYPE )
LUA_CDP_MODAL_MULTI( lua_cdp_combine_mean, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 1", 0, 4, ANA_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 2", 0, 4, ANA_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 3", 0, 4, ANA_TYPE, 2 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 4", 0, 4, ANA_TYPE, 2 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 5", 0, 4, ANA_TYPE, 2 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 6", 0, 4, ANA_TYPE, 2 );
	case 7: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 7", 0, 4, ANA_TYPE, 2 );
	case 8: LINEAR_MULTI_NPROC_TYPE( "combine", "mean 8", 0, 4, ANA_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specross, partials, 9, 2, ANA_TYPE, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_specsphinx_specsphinx, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "specsphinx", "specsphinx 1", 0, 2, ANA_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "specsphinx", "specsphinx 2", 0, 2, ANA_TYPE, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_spectwin_spectwin, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "spectwin", "spectwin 1", 0, 5, ANA_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "spectwin", "spectwin 2", 0, 5, ANA_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "spectwin", "spectwin 3", 0, 5, ANA_TYPE, 2 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "spectwin", "spectwin 4", 0, 5, ANA_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( combine, sum, 0, 1, ANA_TYPE, 2 )


void register_lua_cdp_functions_combine( lua_State * L )
	{
	lua_register( L, "combine_cross",		lua_cdp_combine_cross			);
	lua_register( L, "combine_diff",		lua_cdp_combine_diff			);
	lua_register( L, "combine_interleave",	lua_cdp_combine_interleave		);
	lua_register( L, "combine_make",		lua_cdp_combine_make			);
	lua_register( L, "combine_make2",		lua_cdp_combine_make2			);
	lua_register( L, "combine_max",			lua_cdp_combine_max				);
	lua_register( L, "combine_mean",		lua_cdp_combine_mean			);
	lua_register( L, "combine_partials",	lua_cdp_specross_partials		);
	lua_register( L, "combine_specsphinx",	lua_cdp_specsphinx_specsphinx	);
	lua_register( L, "combine_spectwin",	lua_cdp_spectwin_spectwin		);
	lua_register( L, "combine_sum",			lua_cdp_combine_sum				);
	}