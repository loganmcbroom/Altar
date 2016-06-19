#pragma once

#include "lua_cdp_utilities.h"

static int lua_cdp_multichannel_interlx( lua_State * L )
	{									// infile 1 | infile 2 | ... 
	lua_pushto( L, "interlx", 1 );		// interlx | infile 1 | infile 2 | ...
	lua_pushto( L, "$", 2 );			// interlx | $ | infile 1 | infile 2 | ...
	return cdp( L );
	}

void register_lua_cdp_functions_multichannel( lua_State * L )
	{
	lua_register( L, "cdp_interlx", lua_cdp_multichannel_interlx );
	}