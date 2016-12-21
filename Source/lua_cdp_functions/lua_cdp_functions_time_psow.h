#pragma once

#include "lua_cdp_utilities.h"

LUA_ERROR_FUNC( psow_chop, "I didn't do this one but I will if you ask" )
LUA_CDP_MODAL_MULTI( lua_cdp_psow_cutatgrain, {
	case 1: LINEAR_MULTI_PROC( "psow", "cutatgrain 1", 2, 1 );
	case 2: LINEAR_MULTI_PROC( "psow", "cutatgrain 2", 2, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, delete, 3, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, dupl, 3, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_psow_features, {
	case 1: LINEAR_MULTI_PROC( "psow", "features 1", 11, 1 );
	case 2: LINEAR_MULTI_PROC( "psow", "features 2", 11, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, grab, 8, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, impose, 4, 0, WAV_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, interleave, 6, 0, WAV_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, interp, 7, 0, WAV_TYPE, 2 )
INFO_PROC_FUNC( psow, locate, 2, 0, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( ptobrk, withzeroes, 1, 0, BRK_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_psow_reinforce, {
	case 1: LINEAR_MULTI_PROC( "psow", "reinforce 1", 2, 2 );
	case 2: LINEAR_MULTI_PROC( "psow", "reinforce 2", 2, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, replace, 3, 0, WAV_TYPE, 2 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, space, 5, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, split, 4, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, stretch, 3, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, strtrans, 4, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, sustain, 8, 1, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( psow, sustain2, 6, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_psow_synth, {
	case 1: LINEAR_MULTI_PROC( "psow", "synth 1", 3, 0 );
	case 2: LINEAR_MULTI_PROC( "psow", "synth 2", 3, 0 );
	case 3: LINEAR_MULTI_PROC( "psow", "synth 3", 3, 0 );
	case 4: LINEAR_MULTI_PROC( "psow", "synth 4", 3, 0 );
	case 5: LINEAR_MULTI_PROC( "psow", "synth 5", 3, 0 );
	})


void register_lua_cdp_functions_psow( lua_State * L )
	{
	lua_register( L, "psow_chop",			lua_cdp_psow_chop			);
	lua_register( L, "psow_cutatgrain",		lua_cdp_psow_cutatgrain		);
	lua_register( L, "psow_delete",			lua_cdp_psow_delete			);
	lua_register( L, "psow_dupl",			lua_cdp_psow_dupl			);
	lua_register( L, "psow_features",		lua_cdp_psow_features		);
	lua_register( L, "psow_grab",			lua_cdp_psow_grab			);
	lua_register( L, "psow_impose",			lua_cdp_psow_impose			);
	lua_register( L, "psow_interleave",		lua_cdp_psow_interleave		);
	lua_register( L, "psow_interp",			lua_cdp_psow_interp			);
	lua_register( L, "psow_locate",			lua_cdp_psow_locate			);
	lua_register( L, "psow_ptobrk",			lua_cdp_ptobrk_withzeroes	); //This mismatch is on purpose
	lua_register( L, "psow_withzeroes",		lua_cdp_ptobrk_withzeroes	); 
	lua_register( L, "psow_reinforce",		lua_cdp_psow_reinforce		);
	lua_register( L, "psow_replace",		lua_cdp_psow_replace		);
	lua_register( L, "psow_space",			lua_cdp_psow_space			);
	lua_register( L, "psow_split",			lua_cdp_psow_split			);
	lua_register( L, "psow_stretch",		lua_cdp_psow_stretch		);
	lua_register( L, "psow_strtrans",		lua_cdp_psow_strtrans		);
	lua_register( L, "psow_sustain",		lua_cdp_psow_sustain		);
	lua_register( L, "psow_sustain2",		lua_cdp_psow_sustain2		);
	lua_register( L, "psow_synth",			lua_cdp_psow_synth			);
	}