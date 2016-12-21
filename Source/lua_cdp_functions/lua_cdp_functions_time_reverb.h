#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_NPROC_TYPE_FUNC_2( reverb, fastconv, 1, 0, WAV_TYPE, 2 )
int lua_cdp_reverb_reverb( lua_State * L ) 
	{ 
	return lua_multi_proc( L, 6, 1, []( lua_State * L ) 
		{ \
		lua_pushpairs( L, { {"reverb", 1}, {WAV_TYPE, 3} } ); \
		return cdp( L ); \
		}, 1 ); \
	}
//LINEAR_MULTI_NPROC_TYPE_FUNC_2( reverb, roomresp, 6, 1, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( reverb, roomverb, 7, 0, WAV_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( reverb, tapdelay, 4, 1, WAV_TYPE, 1 )




void register_lua_cdp_functions_reverb( lua_State * L )
	{
	lua_register( L, "reverb_fastconv",	lua_cdp_reverb_fastconv );
	lua_register( L, "reverb_reverb",	lua_cdp_reverb_reverb );
	//lua_register( L, "reverb_roomresp",	lua_cdp_reverb_roomresp );
	lua_register( L, "reverb_roomverb",	lua_cdp_reverb_roomverb );
	lua_register( L, "reverb_tapdelay",	lua_cdp_reverb_tapdelay );
	}