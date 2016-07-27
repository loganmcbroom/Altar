#pragma once

#include "lua_cdp_utilities.h"

NONLINEAR_PROC_FUNC_TYPE( submix, addtomix, 0, 0, TXT_TYPE )
NONLINEAR_PROC_FUNC_TYPE( submix, atstep, 1, 0, TXT_TYPE )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( submix, attenuate, 1, 2, TXT_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( submix, balance, 1, 3, TXT_TYPE, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_submix_crossfade, {
	case 1: LINEAR_MULTI_NPROC( "submix", "crossfade 1", 0, 3, 2 );
	case 2: LINEAR_MULTI_NPROC( "submix", "crossfade 2", 0, 4, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_submix_dummy, {
	case 1: NONLINEAR_PROC( "submix", "dummy 1", 0, 0, TXT_TYPE );
	case 2: NONLINEAR_PROC( "submix", "dummy 2", 0, 0, TXT_TYPE );
	})
NONLINEAR_PROC_FUNC_TYPE( submix, faders, 2, 0, WAV_TYPE )
LUA_ERROR_FUNC( submix_fileformat, "Like I'm gonna map fileformat" );
LUA_CDP_MODAL_MULTI( lua_cdp_submix_getlevel, {
	case 1: LINEAR_MULTI_INFO_PROC ( "submix", "getlevel 1", 0, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "submix", "getlevel 2", 0, 2, TXT_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "submix", "getlevel 3", 0, 2, TXT_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_submix_inbetween,{
	case 1: 
		{
		int count = lua_tointeger( L, 1 );
		return lua_multi_proc( L, 1, 0, [count]( lua_State * L )
			{
			lua_pushpairs( L, { {"submix", 1}, {"inbetween 1", 2}, {WAV_TYPE, 5} } );
			return cdp( L, {outAppendP3S1, count} );
			}, 2 );
		}
	case 2:
		{
		return lua_multi_proc( L, 1, 0, []( lua_State * L )
			{
			lua_pushpairs( L, { {"submix", 1}, {"inbetween 2", 2}, {WAV_TYPE, 5} } );
			return cdp( L, {outAppendP3S1Unknown, 0} );
			}, 2 );
		}
	})
int lua_cdp_submix_inbetween2( lua_State * L )
	{
	int count = lua_tointeger( L, 1 );
	return lua_multi_proc( L, 2, 0, [count]( lua_State * L )
		{
		lua_pushpairs( L, { {"submix", 1}, {"inbetween2", 2}, {WAV_TYPE, 5} } );
		return cdp( L, {outAppendP3S1, count} );
		}, 2 );
	}
NONLINEAR_PROC_FUNC( submix, interleave, 0, 0 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( submix, merge, 0, 5, WAV_TYPE, 2 )
NONLINEAR_PROC_FUNC( submix, mergemany, 0, 0 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( submix, mix, 0, 4, WAV_TYPE, 1 )
NONLINEAR_PROC_FUNC_TYPE( submix, model, 0, 0, TXT_TYPE )
NONLINEAR_PROC_FUNC_TYPE( submix, ongrid, 1, 0, TXT_TYPE )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( submix, pan, 0, 1, TXT_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_submix_shuffle, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 1", 0, 2, TXT_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 2", 0, 2, TXT_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 3", 0, 2, TXT_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 4", 0, 2, TXT_TYPE, 1 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 5", 0, 2, TXT_TYPE, 1 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 6", 0, 2, TXT_TYPE, 1 );
	case 7: LINEAR_MULTI_NPROC_TYPE( "submix", "shuffle 7", 1, 3, TXT_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_submix_spacewarp, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 1", 1, 2, TXT_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 2", 1, 2, TXT_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 3", 2, 2, TXT_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 4", 2, 2, TXT_TYPE, 1 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 5", 2, 2, TXT_TYPE, 1 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 6", 2, 2, TXT_TYPE, 1 );
	case 7: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 7", 0, 0, TXT_TYPE, 1 );
	case 8: LINEAR_MULTI_NPROC_TYPE( "submix", "spacewarp 8", 1, 0, TXT_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_submix_sync, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "submix", "sync 1", 0, 0, TXT_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "submix", "sync 2", 0, 0, TXT_TYPE, 1 );

	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( submix, syncattack, 0, 2, TXT_TYPE, 1 )
INFO_PROC_FUNC( submix, test, 0, 0, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_submix_timewarp, {
	case 1:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 1",  1, 0, TXT_TYPE, 1 );
	case 2:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 2",  1, 2, TXT_TYPE, 1 );
	case 3:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 3",  1, 2, TXT_TYPE, 1 );
	case 4:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 4",  1, 2, TXT_TYPE, 1 );
	case 5:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 5",  1, 2, TXT_TYPE, 1 );
	case 6:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 6",  1, 2, TXT_TYPE, 1 );
	case 7:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 7",  1, 2, TXT_TYPE, 1 );
	case 8:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 8",  1, 2, TXT_TYPE, 1 );
	case 9:  LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 9",  1, 2, TXT_TYPE, 1 );
	case 10: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 10", 1, 2, TXT_TYPE, 1 );
	case 11: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 11", 1, 2, TXT_TYPE, 1 );
	case 12: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 12", 1, 2, TXT_TYPE, 1 );
	case 13: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 13", 1, 2, TXT_TYPE, 1 );
	case 14: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 14", 1, 2, TXT_TYPE, 1 );
	case 15: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 15", 1, 2, TXT_TYPE, 1 );
	case 16: LINEAR_MULTI_NPROC_TYPE( "submix", "timewarp 16", 1, 2, TXT_TYPE, 1 );
	})

void register_lua_cdp_functions_submix( lua_State * L )
	{
	lua_register( L, "submix_addtomix",		lua_cdp_submix_addtomix		);
	lua_register( L, "submix_atstep",		lua_cdp_submix_atstep		);
	lua_register( L, "submix_attenuate",	lua_cdp_submix_attenuate	);
	lua_register( L, "submix_balance",		lua_cdp_submix_balance		);
	lua_register( L, "submix_crossfade",	lua_cdp_submix_crossfade	);
	lua_register( L, "submix_dummy",		lua_cdp_submix_dummy		);
	lua_register( L, "submix_faders",		lua_cdp_submix_faders		);
	lua_register( L, "submix_fileformat",	lua_cdp_submix_fileformat	);
	lua_register( L, "submix_getlevel",		lua_cdp_submix_getlevel		);
	lua_register( L, "submix_inbetween",	lua_cdp_submix_inbetween	);
	lua_register( L, "submix_inbetween2",	lua_cdp_submix_inbetween2	);
	lua_register( L, "submix_interleave",	lua_cdp_submix_interleave	);
	lua_register( L, "submix_merge",		lua_cdp_submix_merge		);
	lua_register( L, "submix_mergemany",	lua_cdp_submix_mergemany	);
	lua_register( L, "submix_mix",			lua_cdp_submix_mix			);
	lua_register( L, "submix_model",		lua_cdp_submix_model		);
	lua_register( L, "submix_ongrid",		lua_cdp_submix_ongrid		);
	lua_register( L, "submix_pan",			lua_cdp_submix_pan			);
	lua_register( L, "submix_shuffle",		lua_cdp_submix_shuffle		);
	lua_register( L, "submix_spacewarp",	lua_cdp_submix_spacewarp	);
	lua_register( L, "submix_sync",			lua_cdp_submix_sync			);
	lua_register( L, "submix_syncattack",	lua_cdp_submix_syncattack	);
	lua_register( L, "submix_test",			lua_cdp_submix_test			);
	lua_register( L, "submix_timewarp",		lua_cdp_submix_timewarp		);
	}