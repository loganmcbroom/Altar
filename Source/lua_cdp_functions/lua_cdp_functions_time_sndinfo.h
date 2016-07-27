#pragma once

#include "lua_cdp_utilities.h"

INFO_PROC_FUNC( sndinfo, chandiff, 0, 2, 1 )
INFO_PROC_FUNC( sndinfo, diff, 0, 4, 2 )
INFO_PROC_FUNC( sndinfo, findhole, 0, 1, 1 )
INFO_PROC_FUNC( sndinfo, len, 0, 0, 1 )
int lua_cdp_sndinfo_lens( lua_State * L )
	{
	lua_pushpairs( L, { {"sndinfo", 1}, {"lens", 2} } );
	return cdp( L );
	}
INFO_PROC_FUNC( sndinfo, loudchan, 0, 0, 1 )
NONLINEAR_PROC_FUNC_TYPE( sndinfo, maxi, 0, 0, TXT_TYPE )
INFO_PROC_FUNC( sndinfo, maxsamp, 0, 1, 1 )
INFO_PROC_FUNC( sndinfo, maxsamp2, 2, 0, 1 )
INFO_PROC_FUNC( peakfind, peakfind, 2, 1, 1 )
INFO_PROC_FUNC( sndinfo, prntsnd, 3, 0, 1 )
INFO_PROC_FUNC( sndinfo, props, 0, 0, 1 )
int lua_cdp_sndinfo_sigstart( lua_State * L )
	{
	lua_pushpairs( L, { {"sndinfo", 1}, {"sigstart", 2} } );
	return cdp( L );
	}
INFO_PROC_FUNC( sndinfo, smptime, 1, 1, 1 )
int lua_cdp_sndinfo_sumlen( lua_State * L )
	{
	const char * s = lua_tostring( L, 1 );
	if( s == nullptr ) return luaL_error( L, "You fucked up sndinfo sumlen somehow" );
	if( s[0] == '-' ) 
		{
		lua_pushvalue( L, 1 );
		lua_remove( L, 1 );
		}
		lua_pushpairs( L, { {"sndinfo", 1}, {"sumlen", 2} } );
		return cdp( L );
	}
INFO_PROC_FUNC( sndinfo, timediff, 0, 0, 2 )
INFO_PROC_FUNC( sndinfo, timesmp, 1, 1, 1 )
LUA_ERROR_FUNC( sndinfo_units, "Do you really need this? I really don't want to map a 25 mode function." );
INFO_PROC_FUNC( sndinfo, zcross, 2, 0, 1 )


void register_lua_cdp_functions_sndinfo( lua_State * L )
	{
	lua_register( L, "sndinfo_chandiff",	lua_cdp_sndinfo_chandiff	);
	lua_register( L, "sndinfo_diff",		lua_cdp_sndinfo_diff		);
	lua_register( L, "sndinfo_findhole",	lua_cdp_sndinfo_findhole	);
	lua_register( L, "sndinfo_len",			lua_cdp_sndinfo_len			);
	lua_register( L, "sndinfo_lens",		lua_cdp_sndinfo_lens		);
	lua_register( L, "sndinfo_loudchan",	lua_cdp_sndinfo_loudchan	);
	lua_register( L, "sndinfo_maxi",		lua_cdp_sndinfo_maxi		);
	lua_register( L, "sndinfo_maxsamp",		lua_cdp_sndinfo_maxsamp		);
	lua_register( L, "sndinfo_maxsamp2",	lua_cdp_sndinfo_maxsamp2	);
	lua_register( L, "sndinfo_peakfind",	lua_cdp_peakfind_peakfind	);
	lua_register( L, "sndinfo_prntsnd",		lua_cdp_sndinfo_prntsnd		);
	lua_register( L, "sndinfo_props",		lua_cdp_sndinfo_props		);
	lua_register( L, "sndinfo_sigstart",	lua_cdp_sndinfo_sigstart	);
	lua_register( L, "sndinfo_smptime",		lua_cdp_sndinfo_smptime		);
	lua_register( L, "sndinfo_sumlen",		lua_cdp_sndinfo_sumlen		);
	lua_register( L, "sndinfo_timediff",	lua_cdp_sndinfo_timediff	);
	lua_register( L, "sndinfo_timesmp",		lua_cdp_sndinfo_timesmp		);
	lua_register( L, "sndinfo_units",		lua_cdp_sndinfo_units		);
	lua_register( L, "sndinfo_zcross",		lua_cdp_sndinfo_zcross		);
	}