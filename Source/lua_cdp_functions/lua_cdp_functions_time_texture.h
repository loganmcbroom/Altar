#pragma once

#include "lua_cdp_utilities.h"

#define TEXTURE_MODAL_FUNC( process, params, flags ) \
int lua_cdp_texture_ ## process( lua_State * L ) \
	{ \
	int mode = lua_tonumber( L, 1 ); \
	lua_remove( L, 1 ); \
	if( mode > 5 ) \
		return luaL_error( L, ( "lua_cdp_texture_" + std::string( #process ) + " has no mode " + std::to_string( mode ) ).c_str() ); \
	return lua_nonlinear_proc( L, params, flags, [&]( lua_State * L, int groupSize ) \
		{ \
		lua_pushpairs( L, { {"texture", 1}, { (std::string(#process) +  " " + to_string( mode )).c_str(), 2}, {WAV_TYPE, 3 + groupSize} } );\
		return cdp( L ); \
		} ); \
	}

TEXTURE_MODAL_FUNC( simple,		13, 5	)
TEXTURE_MODAL_FUNC( grouped,	24, 7	)
TEXTURE_MODAL_FUNC( decorated,	21, 10	)
TEXTURE_MODAL_FUNC( predecor,	21, 10	)
TEXTURE_MODAL_FUNC( postdecor,	21, 10	)
TEXTURE_MODAL_FUNC( motifs,		18, 7	)
TEXTURE_MODAL_FUNC( motifsin,	18, 7	)
TEXTURE_MODAL_FUNC( ornate,		16, 9	)
TEXTURE_MODAL_FUNC( preornate,	16, 9	)
TEXTURE_MODAL_FUNC( postornate,	16, 9	)
TEXTURE_MODAL_FUNC( timed,		11, 5	)
TEXTURE_MODAL_FUNC( tgrouped,	22, 7	)
TEXTURE_MODAL_FUNC( tmotifs,	16, 7	)
TEXTURE_MODAL_FUNC( tmotifsin,	16, 7	)


void register_lua_cdp_functions_texture( lua_State * L )
	{
	lua_register( L, "texture_simple",		lua_cdp_texture_simple		);
	lua_register( L, "texture_grouped",		lua_cdp_texture_grouped		);
	lua_register( L, "texture_decorated",	lua_cdp_texture_decorated	);
	lua_register( L, "texture_predecor",	lua_cdp_texture_predecor	);
	lua_register( L, "texture_postdecor",	lua_cdp_texture_postdecor	);
	lua_register( L, "texture_motifs",		lua_cdp_texture_motifs		);
	lua_register( L, "texture_motifsin",	lua_cdp_texture_motifsin	);
	lua_register( L, "texture_ornate",		lua_cdp_texture_ornate		);
	lua_register( L, "texture_preornate",	lua_cdp_texture_preornate	);
	lua_register( L, "texture_postornate",	lua_cdp_texture_postornate	);
	lua_register( L, "texture_timed",		lua_cdp_texture_timed		);
	lua_register( L, "texture_tgrouped",	lua_cdp_texture_tgrouped	);
	lua_register( L, "texture_tmotifs",		lua_cdp_texture_tmotifs		);
	lua_register( L, "texture_tmotifsin",	lua_cdp_texture_tmotifsin	);
	}