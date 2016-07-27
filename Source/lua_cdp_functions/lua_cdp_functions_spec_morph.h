#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_morph_bridge, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "morph", "bridge 1", 0, 6, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "morph", "bridge 2", 0, 6, WAV_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "morph", "bridge 3", 0, 6, WAV_TYPE, 2 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "morph", "bridge 4", 0, 6, WAV_TYPE, 2 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "morph", "bridge 5", 0, 6, WAV_TYPE, 2 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "morph", "bridge 6", 0, 6, WAV_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( morph, glide, 1, 0, WAV_TYPE, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_morph_morph, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "morph", "morph 1", 6, 1, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "morph", "morph 2", 6, 1, WAV_TYPE, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_newmorph_newmorph, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 1", 5, 3, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 2", 5, 3, WAV_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 3", 5, 3, WAV_TYPE, 2 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 4", 5, 3, WAV_TYPE, 2 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 5", 5, 3, WAV_TYPE, 2 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 6", 5, 3, WAV_TYPE, 2 );
	case 7: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph 7", 2, 3, WAV_TYPE, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_newmorph_newmorph2, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph2 1", 1, 0, TXT_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph2 2", 4, 1, WAV_TYPE, 2 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "newmorph", "newmorph2 3", 4, 1, WAV_TYPE, 2 );
	})


void register_lua_cdp_functions_morph( lua_State * L )
	{
	lua_register( L, "morph_bridge",	lua_cdp_morph_bridge		);
	lua_register( L, "morph_glide",		lua_cdp_morph_glide			);
	lua_register( L, "morph_morph",		lua_cdp_morph_morph			);
	lua_register( L, "morph_newmorph",	lua_cdp_newmorph_newmorph	);
	lua_register( L, "morph_newmorph2",	lua_cdp_newmorph_newmorph2	);
	}