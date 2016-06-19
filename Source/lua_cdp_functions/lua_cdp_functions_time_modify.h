#pragma once

#include "lua_cdp_utilities.h"

//Normalize infile to given level 
LUA_CDP_MULTI( lua_cdp_modify_loudness_3, 0, 1,
	{										
	lua_pushpairs( L, 
		{						// infile | -llevel
		{ "modify", 1	  },	// modify | infile | -llevel
		{ "loudness 3", 2 },	// modify | loudness 3 | infile | -llevel
		{ "$", 4		  }		// modify | loudness 3 | infile | $ | -llevel
		});
		
	//if( lua_gettop( L ) == 4 ) lua_pushstring( L, "-l0.9" );
	return cdp( L );
	})

void register_lua_cdp_functions_modify( lua_State * L )
	{
	lua_register( L, "cdp_normalize", lua_cdp_modify_loudness_3 );
	}