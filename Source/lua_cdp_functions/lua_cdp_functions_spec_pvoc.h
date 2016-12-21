#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_pvoc_anal, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, pvoc, anal, 0, 2, ANA_TYPE, 1 );
	LINEAR_MULTI_NPROC_TYPE_2( 2, pvoc, anal, 0, 2, BIN_TYPE, 1 );
	LINEAR_MULTI_NPROC_TYPE_2( 3, pvoc, anal, 0, 2, BIN_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( pvoc, extract, 0, 5, WAV_TYPE, 1 ) ///Untested
/*LUA_CDP_MULTI( lua_cdp_pvoc_synth, 0, 0,{	
	lua_pushpairs( L, { {"pvoc", 1}, {"anal 1", 2}, {ANA_TYPE, 4} });							
	lua_pushto( L, "pvoc", 1 );		
	lua_pushto( L, "synth", 2 );	
	lua_pushstring( L, ANA_TYPE );
	return cdp( L );
	})*/
LINEAR_MULTI_NPROC_TYPE_FUNC_2( pvoc, synth, 0, 0, WAV_TYPE, 1 )

void register_lua_cdp_functions_PVOC( lua_State * L )
	{
	lua_register( L, "pvoc_anal",		lua_cdp_pvoc_anal );
	lua_register( L, "pvoc_extract",	lua_cdp_pvoc_extract );
	lua_register( L, "pvoc_synth",		lua_cdp_pvoc_synth );
	}