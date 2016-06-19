#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MULTI( lua_cdp_pvoc_anal, 0, 2,
	{
	lua_pushpairs( L,
		{ // infile | -cpoints | -ooverlap
		{ "pvoc",	1 },
		{ "anal 1", 2 },
		{ "$",		4 }
		});
	return cdp( L );
	})

///Untested
LUA_CDP_MULTI( lua_cdp_pvoc_extract, 0, 5,
	{
	lua_pushpairs( L,
		{
		{ "pvoc",	 1 },
		{ "extract", 2 }
		});
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_pvoc_synth, 0, 0,
	{								// infile
	lua_pushto( L, "pvoc", 1 );		// pvoc | infile
	lua_pushto( L, "synth", 2 );	// pvoc | synth | infile
	lua_pushstring( L, "$" );		// pvoc | synth | infile | $
	return cdp( L );
	})

void register_lua_cdp_functions_PVOC( lua_State * L )
	{
	lua_register( L, "cdp_anal",	lua_cdp_pvoc_anal );
	lua_register( L, "cdp_extract", lua_cdp_pvoc_extract );
	lua_register( L, "cdp_synth",	lua_cdp_pvoc_synth );
	}