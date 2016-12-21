#pragma once

#include "lua_cdp_utilities.h"

LUA_ERROR_FUNC( sysutils_alias, "You don't need sysutils alias probably cmon" );
LUA_ERROR_FUNC( sysutils_cdpconv, "sysutils cdpconv isn't supported because it can destroy files" );
LUA_ERROR_FUNC( sysutils_columns, "sysutils columns... little much for me." );
//copysfx, inverse flags
LUA_ERROR_FUNC( sysutils_dirsf, "sysutils dirsf isn't supported because it's too dank" );
int lua_cdp_sysutils_listaudevs( lua_State * L )
	{
	lua_pushstring( L, "listaudevs" );
	return cdp( L );
	}
LUA_ERROR_FUNC( sysutils_paplay, "You don't need sysutils paplay probably cmon" );
LUA_ERROR_FUNC( sysutils_pvplay, "You don't need sysutils pvplay probably cmon" );
int lua_cdp_sysutils_recsf( lua_State * L )
	{
	//check if there is a dur parameter passed
	if( ! lua_isnumber( L, -1 ) ) return luaL_error( L, "You must send a duration to recsf" );
	lua_pushpairs( L, { {"recsf", 1}, {"-i", 2}, {WAV_TYPE, -2} } );
	return cdp( L );
	}


void register_lua_cdp_functions_sysutils( lua_State * L )
	{
	lua_register( L, "sysutils_alias",		lua_cdp_sysutils_alias		);
	lua_register( L, "sysutils_cdpconv",	lua_cdp_sysutils_cdpconv	);
	lua_register( L, "sysutils_columns",	lua_cdp_sysutils_columns	);
	//lua_register( L, "sysutils_copysfx",		lua_cdp_sysutils_copysfx	);
	lua_register( L, "sysutils_dirsf",		lua_cdp_sysutils_dirsf		);
	lua_register( L, "sysutils_listaudevs",	lua_cdp_sysutils_listaudevs	);
	lua_register( L, "sysutils_paplay",		lua_cdp_sysutils_paplay		);
	lua_register( L, "sysutils_pvplay",		lua_cdp_sysutils_pvplay		);
	lua_register( L, "sysutils_recsf",		lua_cdp_sysutils_recsf		);
	}