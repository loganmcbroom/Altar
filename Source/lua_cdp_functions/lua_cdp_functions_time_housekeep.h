#pragma once

#include <string>

#include "lua_cdp_utilities.h"

static int lua_cdp_housekeep_bakup( lua_State * L )
	{
	lua_pushpairs( L,
		{
		{ "housekeep",	1 },
		{ "bakup",		2 }
		});
	lua_pushstring( L, WAV_TYPE );
	return cdp( L );
	}
static int lua_cdp_housekeep_batchexpand( lua_State * L )
	{
	lua_pushpairs( L,
		{
		{ "housekeep",	 1 },
		{ "batchexpand", 2 }
		});
	return cdp( L );
	}
static int lua_cdp_housekeep_bundle( lua_State * L )
	{
	lua_pushpairs( L,
		{
		{ "housekeep",	1 },
		{ "bundle",		2 }
		});
	return cdp( L );
	}
LUA_CDP_MULTI( lua_cdp_chanphase_chanphase, 1, 0,{
	lua_pushpairs( L,
		{
		{ "chanphase", 1 },
		{ "chanphase", 2 },
		{ WAV_TYPE, 4 }
		});
	return cdp( L );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_housekeep_chans, {
	case 1: return lua_multi_proc( L, 1, 0, []( lua_State * L )
			{ 
			lua_pushpairs( L, { {"housekeep", 1}, {"chans 1", 2} } );
			return cdp( L, { inChannelSingle, lua_tonumber( L, 4 ) } );
			});
	case 2: return lua_multi_proc( L, 0, 0, []( lua_State * L )
			{ 
			int numChannels = getNumChannels( lua_tostring( L, 1 ) );
			lua_pushpairs( L, { { "housekeep", 1 }, { "chans 2", 2  } } );
			return cdp( L, {inChannel, numChannels} );
			});
	case 3: LINEAR_MULTI_PROC( "housekeep", "chans 3", 1, 0 );
	case 4: LINEAR_MULTI_PROC( "housekeep", "chans 4", 0, 1 );
	case 5: LINEAR_MULTI_PROC( "housekeep", "chans 5", 0, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_housekeep_copy, {
	case 1: LINEAR_MULTI_PROC( "housekeep", "copy 1", 0, 0 );
	case 2: return lua_multi_proc( L, 1, 0, []( lua_State * L ){
		int numOuts = lua_tointeger( L, 1 );
		lua_pushpairs( L, { {"housekeep", 1}, {"copy 2", 2} } );
		return cdp( L, {housekeepCopy, numOuts} );
		});
	})
LUA_CDP_MULTI( lua_cdp_housekeep_deglitch, 5, 1,{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "deglitch", 2 },
		{ WAV_TYPE, 4 }
		});
	return cdp( L );
	})
LUA_CDP_UNSUPPORTED_CONST( lua_cdp_housekeep_disk )
LUA_CDP_MULTI( lua_cdp_housekeep_endclicks, 2, 2,{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "endclicks", 2 },
		{ WAV_TYPE, 4 }
		});
	return cdp( L );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_housekeep_extract, {
	case 1: return luaL_error( L, "Housekeep extract 1 is unsupported due to outputting bad file names" );
	case 2: LINEAR_MULTI_PROC( "housekeep", "extract 2", 0, 0 );
	case 3: LINEAR_MULTI_PROC( "housekeep", "extract 3", 0, 4 );
	case 4: LINEAR_MULTI_PROC( "housekeep", "extract 4", 1, 0 );
	case 5: return luaL_error( L, "Housekeep extract 5 is no longer supported by the CDP" );
	case 6: return lua_multi_proc( L, 7, 0, []( lua_State * L )
			{ 
			lua_pushpairs( L, { {"housekeep", 1}, {"extract 6", 2}, {TXT_TYPE, 4} } );
			return cdp( L );
			});
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( housekeep, gate, 0, 1, WAV_TYPE, 1 )
LUA_CDP_MULTI( lua_cdp_gate_gate, 2, 0,{					// file | mode | gatelevel
	lua_insert( L, 2 ); // file | gatelevel | mode
	lua_insert( L, 1 );	// mode | file | gatelevel 
	lua_pushpairs( L,
		{	
		{ "gate", 1 },
		{ "gate", 2 },
		{ WAV_TYPE, 5 }
		});
	return cdp( L );
	})
LUA_CDP_MULTI( lua_cdp_housekeep_remove, 0, 1,{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "remove", 2 }
		});
	return cdp( L );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_housekeep_respec, {
	case 1: LINEAR_MULTI_PROC( "housekeep", "respec 1", 1, 0 );
	case 2: LINEAR_MULTI_PROC( "housekeep", "respec 2", 0, 0 );
	case 3: LINEAR_MULTI_PROC( "housekeep", "respec 3", 0, 3 );
	})
LUA_CDP_UNSUPPORTED_CONST( lua_cdp_housekeep_sort )

void register_lua_cdp_functions_housekeep( lua_State * L )
	{
	lua_register( L, "housekeep_bakup",			lua_cdp_housekeep_bakup			);
	lua_register( L, "housekeep_batchexpand",	lua_cdp_housekeep_batchexpand	);
	lua_register( L, "housekeep_bundle",		lua_cdp_housekeep_bundle		);
	lua_register( L, "housekeep_chanphase",		lua_cdp_chanphase_chanphase		);
	lua_register( L, "housekeep_chans",			lua_cdp_housekeep_chans			);
	lua_register( L, "housekeep_copy",			lua_cdp_housekeep_copy			);
	lua_register( L, "housekeep_deglitch",		lua_cdp_housekeep_deglitch		);
	lua_register( L, "housekeep_disk",			lua_cdp_housekeep_disk			);
	lua_register( L, "housekeep_endclicks",		lua_cdp_housekeep_endclicks		);
	lua_register( L, "housekeep_extract",		lua_cdp_housekeep_extract		);
	lua_register( L, "housekeep_gate",			lua_cdp_housekeep_gate			);
	lua_register( L, "gate_gate",				lua_cdp_gate_gate				);
	lua_register( L, "housekeep_respec",		lua_cdp_housekeep_respec		);
	lua_register( L, "housekeep_sort",			lua_cdp_housekeep_sort			);
	}