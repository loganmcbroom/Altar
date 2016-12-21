#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_envel_attack, {
	case 1: LINEAR_MULTI_PROC( "envel", "attack 1", 4, 1 );
	case 2: LINEAR_MULTI_PROC( "envel", "attack 2", 4, 1 );
	case 3: LINEAR_MULTI_PROC( "envel", "attack 3", 4, 1 );
	case 4: LINEAR_MULTI_PROC( "envel", "attack 4", 3, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, brktoenv, 1, 0, BIN_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envel_create, {
	case 1: return lua_multi_proc( L, 1, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"envel", 1}, {"create 1", 2}, {BIN_TYPE, 3} } );
		return cdp( L );
		} );
	case 2: return lua_multi_proc( L, 0, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"envel", 1}, {"create 2", 2}, {TXT_TYPE, 3} } );
		return cdp( L );
		} );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_envel_curtail, {
	case 1: LINEAR_MULTI_PROC( "envel", "curtail 1", 3, 1 );
	case 2: LINEAR_MULTI_PROC( "envel", "curtail 2", 3, 1 );
	case 3: LINEAR_MULTI_PROC( "envel", "curtail 3", 2, 1 );
	case 4: LINEAR_MULTI_PROC( "envel", "curtail 4", 3, 1 );
	case 5: LINEAR_MULTI_PROC( "envel", "curtail 5", 4, 1 );
	case 6: LINEAR_MULTI_PROC( "envel", "curtail 6", 1, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_envel_cyclic, {
	case 1: 
		{
		lua_pushpairs( L, { {"envel", 1}, {"cyclic 1", 2}, {BIN_TYPE, 3} } );
		return cdp( L );
		}
	case 2:
		{
		lua_pushpairs( L, { {"envel", 1}, {"cyclic 2", 2}, {BIN_TYPE, 3} } );
		return cdp( L );
		} 
	case 3: 
		{
		lua_pushpairs( L, { {"envel", 1}, {"cyclic 3", 2}, {BIN_TYPE, 3} } );
		return cdp( L );
		} 
	case 4: return lua_multi_proc( L, 4, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"envel", 1}, {"cyclic 4", 2}, {BIN_TYPE, 3} } );
		return cdp( L );
		} );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, dbtoenv, 1, 0, BIN_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, dbtogain, 0, 0, TXT_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envel_dovetail, {
	case 1: LINEAR_MULTI_PROC( "envel", "dovetail 1", 4, 1 );
	case 2: LINEAR_MULTI_PROC( "envel", "dovetail 2", 2, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, envtobrk, 0, 1, TXT_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, envtodb, 0, 1, TXT_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envel_extract, {
	case 1: LINEAR_MULTI_PROC_TYPE( "envel", "extract 1", 1, 0, BIN_TYPE );
	case 2: LINEAR_MULTI_PROC_TYPE( "envel", "extract 2", 1, 1, TXT_TYPE );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, gaintodb, 0, 0, TXT_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envel_impose, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "envel", "impose 1", 1, 0, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "envel", "impose 2", 0, 0, WAV_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "envel", "impose 3", 0, 0, WAV_TYPE, 2 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "envel", "impose 4", 0, 0, WAV_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, pluck, 2, 2, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envel_replace, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "envel", "replace 1", 1, 0, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "envel", "replace 2", 0, 0, WAV_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "envel", "replace 3", 1, 0, WAV_TYPE, 2 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "envel", "replace 4", 1, 0, WAV_TYPE, 2 );
	})

#define ENVEL_15_FUNC( proc, vp1, vp2, vp3, flags, outType ) LUA_CDP_MODAL_MULTI( lua_cdp_envel_ ## proc, {\
	case 1:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 1",  vp1 + 0, flags, outType );\
	case 2:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 2",  vp1 + 0, flags, outType );\
	case 3:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 3",  vp1 + 1, flags, outType );\
	case 4:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 4",  vp1 + 1, flags, outType );\
	case 5:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 5",  vp1 + 1, flags, outType );\
	case 6:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 6",  vp1 + 1, flags, outType );\
	case 7:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 7",  vp1 + 1, flags, outType );\
	case 8:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 8",  vp1 + 2, flags, outType );\
	case 9:  LINEAR_MULTI_PROC_TYPE( "envel", #proc " 9",  vp1 + 2, flags, outType );\
	case 10: LINEAR_MULTI_PROC_TYPE( "envel", #proc " 10", vp1 + 2, flags, outType );\
	case 11: LINEAR_MULTI_PROC_TYPE( "envel", #proc " 11", vp1 + 2, flags, outType );\
	case 12: LINEAR_MULTI_PROC_TYPE( "envel", #proc " 12", vp1 + 3, flags, outType );\
	case 13: LINEAR_MULTI_PROC_TYPE( "envel", #proc " 13", vp2 + 4, flags, outType );\
	case 14: LINEAR_MULTI_PROC_TYPE( "envel", #proc " 14", vp3 + 0, flags, outType );\
	case 15: LINEAR_MULTI_PROC_TYPE( "envel", #proc " 15", vp3 + 2, flags, outType );\
	})
ENVEL_15_FUNC( replot,	1, 2, 1, 1, TXT_TYPE )
ENVEL_15_FUNC( reshape, 0, 1, 0, 0, BRK_TYPE )
ENVEL_15_FUNC( warp,	1, 2, 1, 0, WAV_TYPE )

LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, scaled, 0, 0, WAV_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envel, swell, 2, 0, WAV_TYPE, 1 )
int lua_cdp_envel_timegrid( lua_State * L )
	{
	return luaL_error( L, "Envelope Timegrid isn't supported but will be if you ask" );
	}
LINEAR_MULTI_NPROC_TYPE_FUNC_2( topantail2, topantail, 2, 2, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envel_tremolo, {
	case 1: LINEAR_MULTI_PROC( "envel", "tremolo 1", 3, 0 );
	case 2: LINEAR_MULTI_PROC( "envel", "tremolo 2", 3, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_tremolo_tremolo, {
	case 1: LINEAR_MULTI_PROC( "tremolo", "tremolo 1", 4, 0 );
	case 2: LINEAR_MULTI_PROC( "tremolo", "tremolo 2", 4, 0 );
	})

//EnvNu
LINEAR_MULTI_NPROC_TYPE_FUNC_2( envnu, expdecay, 2, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_envnu_peakchop, {
	case 1: LINEAR_MULTI_PROC( "envnu", "peakchop 1", 5, 6 );
	case 2: LINEAR_MULTI_PROC( "envnu", "peakchop 2", 3, 2 );
	})


void register_lua_cdp_functions_envel( lua_State * L )
	{
	lua_register( L, "envel_attack",		lua_cdp_envel_attack			);
	lua_register( L, "envel_brktoenv",	lua_cdp_envel_brktoenv			);
	lua_register( L, "envel_create",		lua_cdp_envel_create			);
	lua_register( L, "envel_curtail",		lua_cdp_envel_curtail			);
	lua_register( L, "envel_cyclic",		lua_cdp_envel_cyclic			);
	lua_register( L, "envel_dbtoenv",		lua_cdp_envel_dbtoenv			);
	lua_register( L, "envel_dbtogain",	lua_cdp_envel_dbtogain			);
	lua_register( L, "envel_dovetail",	lua_cdp_envel_dovetail			);
	lua_register( L, "envel_envtobrk",	lua_cdp_envel_envtobrk			);
	lua_register( L, "envel_envtodb",		lua_cdp_envel_envtodb			);
	lua_register( L, "envel_extract",		lua_cdp_envel_extract			);
	lua_register( L, "envel_gaintodb",	lua_cdp_envel_gaintodb			);
	lua_register( L, "envel_impose",		lua_cdp_envel_impose			);
	lua_register( L, "envel_pluck",		lua_cdp_envel_pluck				);
	lua_register( L, "envel_replace",		lua_cdp_envel_replace			);
	lua_register( L, "envel_replot",		lua_cdp_envel_replot			);
	lua_register( L, "envel_reshape",		lua_cdp_envel_reshape			);
	lua_register( L, "envel_warp",		lua_cdp_envel_warp				);
	lua_register( L, "envel_scaled",		lua_cdp_envel_scaled			);
	lua_register( L, "envel_swell",		lua_cdp_envel_swell				);
	lua_register( L, "envel_timegrid",	lua_cdp_envel_timegrid			);
	lua_register( L, "envel_topantail",	lua_cdp_topantail2_topantail	);
	lua_register( L, "envel_tremolo",		lua_cdp_envel_tremolo			);

	//EnvNu
	lua_register( L, "envnu_expdecay",	lua_cdp_envnu_expdecay			);
	lua_register( L, "envnu_peakchop",	lua_cdp_envnu_peakchop			);
	}