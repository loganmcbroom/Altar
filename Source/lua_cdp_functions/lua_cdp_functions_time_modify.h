#pragma once

#include "lua_cdp_utilities.h"
LUA_CDP_MODAL_MULTI( lua_cdp_modify_brassage, {
	case 1: LINEAR_MULTI_PROC( "modify", "brassage 1", 1, 0 );
	case 2: LINEAR_MULTI_PROC( "modify", "brassage 2", 1, 0 );
	case 3: LINEAR_MULTI_PROC( "modify", "brassage 3", 3, 1 );
	case 4: LINEAR_MULTI_PROC( "modify", "brassage 4", 1, 1 );
	case 5: LINEAR_MULTI_PROC( "modify", "brassage 5", 1, 1 );
	case 6: LINEAR_MULTI_PROC( "modify", "brassage 6", 8, 7 );
	case 7: LINEAR_MULTI_PROC( "modify", "brassage 7", 16, 7 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_modify_convolve, {
	case 1: LINEAR_MULTI_NPROC( "modify", "convolve 1", 0, 0, 2 ); 
	case 2: LINEAR_MULTI_NPROC( "modify", "convolve 2", 1, 0, 2 );
	})
INFO_PROC_FUNC( modify, findpan, 1, 0, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_modify_loudness, {
	case 1: LINEAR_MULTI_PROC( "modify", "loudness 1", 1, 0 );
	case 2: LINEAR_MULTI_PROC( "modify", "loudness 2", 1, 0 );
	case 3: LINEAR_MULTI_PROC( "modify", "loudness 3", 0, 1 );
	case 4: LINEAR_MULTI_PROC( "modify", "loudness 4", 0, 1 );
	case 5: LINEAR_MULTI_NPROC( "modify", "loudness 5", 0, 0, 2 );
	case 6: LINEAR_MULTI_PROC( "modify", "loudness 6", 0, 0 );
	case 7: {
		lua_pushpairs( L, { {"modify", 1}, {"loudness 7", 2} } );
		return cdp( L, {cmdInfo, 0} );
		}
	case 8: {
		int numFiles = lua_gettop( L );
		lua_pushpairs( L, { {"modify", 1}, {"loudness 8", 2}, {WAV_TYPE, -1} } );
		return cdp( L, {outAppend, numFiles} );
		}
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_newdelay_newdelay, "newdelay", "newdelay", 3, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_phase_phase, {
	case 1: LINEAR_MULTI_PROC( "phase", "phase 1", 0, 0 );
	case 2: LINEAR_MULTI_PROC( "phase", "phase 2", 0, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_modify_radical, {
	case 1: LINEAR_MULTI_PROC( "modify", "radical 1", 0, 0 );
	case 2: LINEAR_MULTI_PROC( "modify", "radical 2", 2, 2 );
	case 3: LINEAR_MULTI_PROC( "modify", "radical 3", 1, 4 );
	case 4: LINEAR_MULTI_PROC( "modify", "radical 4", 2, 0 );
	case 5: LINEAR_MULTI_PROC( "modify", "radical 5", 1, 0 );
	case 6: LINEAR_MULTI_NPROC( "modify", "radical 6", 0, 0, 2 );
	case 7: LINEAR_MULTI_PROC( "modify", "radical 7", 1, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_modify_revecho, {
	case 1: LINEAR_MULTI_PROC( "modify", "revecho 1", 4, 2 );
	case 2: LINEAR_MULTI_PROC( "modify", "revecho 2", 8, 2 );
	case 3: LINEAR_MULTI_PROC( "modify", "revecho 3", 0, 4 );
	})
int lua_cdp_modify_sausage( lua_State * L )
	{ // params (16) | flags (7) | infile 1 | infile 2 | ...
	int extraParams = 16;
	for( int i = 0; i < 7 + 1; ++i )
		{
		const char * s = lua_tostring( L, i + 16 + 1 );
		if( s == nullptr ) return luaL_error( L, "Not enough parameters passed to lua_cdp_modify_sausage" );
		if( s[0] != '-' ) //We've passed the end of the flags
			{
			extraParams += i;
			break;
			}
		}
	int numFiles = lua_gettop( L ) - extraParams;
	for( int i = 0; i < numFiles; ++i )
		lua_insert( L, 1 );
	//  infile 1 | infile 2 | ... | params (17) | flags (7)

	lua_pushpairs( L, 
		{
		{"modify", 1},
		{"sausage", 2},
		{WAV_TYPE, numFiles + 3}
		});
	return cdp( L );
	}
LINEAR_MULTI_PROC_FUNC( lua_cdp_modify_scaledpan, "modify", "scaledpan", 1, 1 )
int lua_cdp_modify_shudder( lua_State * L )
	{
	return lua_multi_proc( L, 8, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"modify", 1}, {"shudder", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {modifyShudder, 0} );
		});
	}
LUA_CDP_MODAL_MULTI( lua_cdp_modify_space, {
	case 1: LINEAR_MULTI_PROC( "modify", "space 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "modify", "space 2", 0, 0 );
	case 3: LINEAR_MULTI_PROC_TYPE( "modify", "space 3", 0, 0, TXT_TYPE );
	case 4: LINEAR_MULTI_PROC( "modify", "space 4", 1, 0 );
	})
int lua_cdp_modify_spaceform( lua_State * L )
	{
	lua_pushpairs( L, 
		{
		{"modify", 1},
		{"spaceform", 2},
		{TXT_TYPE, 3 }
		});
	return cdp( L );
	}
LUA_CDP_MODAL_MULTI( lua_cdp_modify_speed, {
	case 1: LINEAR_MULTI_PROC( "modify", "speed 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "modify", "speed 2", 1, 1 );
	case 3: LINEAR_MULTI_INFO_PROC( "modify", "speed 3", 1, 1 );
	case 4: LINEAR_MULTI_INFO_PROC( "modify", "speed 4", 1, 1 );
	case 5: LINEAR_MULTI_PROC( "modify", "speed 5", 2, 1 );
	case 6: LINEAR_MULTI_PROC( "modify", "speed 6", 2, 0 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_modify_stack, "modify", "stack", 6, 1 );

void register_lua_cdp_functions_modify( lua_State * L )
	{
	lua_register( L, "modify_brassage",		lua_cdp_modify_brassage		);
	lua_register( L, "modify_convolve",		lua_cdp_modify_convolve		);
	lua_register( L, "modify_findpan",		lua_cdp_modify_findpan		);
	lua_register( L, "modify_loudness",		lua_cdp_modify_loudness		);
	lua_register( L, "modify_newdelay",		lua_cdp_newdelay_newdelay	);
	lua_register( L, "modify_phase",		lua_cdp_phase_phase			);
	lua_register( L, "modify_radical",		lua_cdp_modify_radical		);
	lua_register( L, "modify_revecho",		lua_cdp_modify_revecho		);
	lua_register( L, "modify_sausage",		lua_cdp_modify_sausage		);
	lua_register( L, "modify_scaledpan",	lua_cdp_modify_scaledpan	);
	lua_register( L, "modify_shudder",		lua_cdp_modify_shudder		);
	lua_register( L, "modify_space",		lua_cdp_modify_space		);
	lua_register( L, "modify_spaceform",	lua_cdp_modify_spaceform	);
	lua_register( L, "modify_speed",		lua_cdp_modify_speed		);
	lua_register( L, "modify_stack",		lua_cdp_modify_stack		);
	}