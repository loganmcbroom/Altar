#pragma once

#include "lua_cdp_utilities.h"

///Test type outputs on most of this

LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, analenv, 0, 0, ENV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_approx, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, approx, 0, 3, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, approx, 0, 3, TXT_TYPE, 1 ); 
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( brktopi, brktopi, 0, 0, BIN_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_combine, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, combine, 0, 0, TXT_TYPE, 2 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, combine, 0, 0, TXT_TYPE, 2 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 3, repitch, combine, 0, 0, TXT_TYPE, 2 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_combineb, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, combineb, 0, 1, TXT_TYPE, 2 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, combineb, 0, 1, TXT_TYPE, 2 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 3, repitch, combineb, 0, 1, TXT_TYPE, 2 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_cut, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, cut, 1, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, cut, 1, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 3, repitch, cut, 2, 0, BIN_TYPE, 1 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_exag, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, exag, 2, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, exag, 2, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 3, repitch, exag, 2, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 4, repitch, exag, 2, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 5, repitch, exag, 3, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 6, repitch, exag, 3, 0, BIN_TYPE, 1 ); 
	}) 
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, fix, 0, 9, BIN_TYPE, 1 )
int lua_cdp_repitch_generate( lua_State * L )
	{
	lua_pushpairs( L, { {"repitch", 1}, {"generate", 2}, {BIN_TYPE, 3} } );
	return cdp( L );
	}
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_getpitch, {
	case 1: return lua_multi_proc( L, 0, 8, []( lua_State * L )
		{
		lua_pushpairs( L, { {"repitch",1}, {"getpitch 1",2}, {WAV_TYPE, 4}, {FRQ_TYPE, 5} } );
		return cdp( L, { repitchGetpitch, 0 } );
		});
	case 2: return lua_multi_proc( L, 0, 8, []( lua_State * L )
		{
		lua_pushpairs( L, { {"repitch",1}, {"getpitch 2",2}, {WAV_TYPE, 4}, {BRK_TYPE, 5} } );
		return cdp( L, { repitchGetpitch, 0 } );
		});
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_insertsil, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, insertsil, 1, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, insertsil, 1, 0, BIN_TYPE, 1 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_interp, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, interp, 0, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, interp, 0, 0, BIN_TYPE, 1 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_invert, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, invert, 1, 3, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, invert, 1, 3, BIN_TYPE, 1 ); 
	}) 
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, noisetosil, 0, 0, FRQ_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, pchshift, 1, 0, FRQ_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, pchtotext, 0, 0, TXT_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, pitchtosil, 0, 0, FRQ_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_quantise, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, quantise, 1, 1, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, quantise, 1, 1, BIN_TYPE, 1 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_randomise, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, randomise, 2, 1, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, randomise, 2, 1, BIN_TYPE, 1 ); 
	}) 
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_smooth, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, smooth, 1, 2, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, smooth, 1, 2, BIN_TYPE, 1 ); 
	}) 
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, synth, 1, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_repitch_transpose, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, transpose, 1, 3, WAV_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, transpose, 1, 3, WAV_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 3, repitch, transpose, 1, 3, WAV_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 4, repitch, transpose, 0, 3, WAV_TYPE, 2 ); 
	}) 

//bad flags
/*LUA_CDP_MODAL_MULTI( lua_cdp_repitch_transposef, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, transposef, 0, 3, WAV_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, transposef, 0, 3, WAV_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 3, repitch, transposef, 0, 3, WAV_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 4, repitch, transposef, 0, 3, WAV_TYPE, 2 ); 
	}) */

LUA_CDP_MODAL_MULTI( lua_cdp_repitch_vibrato, {
	LINEAR_MULTI_NPROC_TYPE_2( 1, repitch, vibrato, 2, 0, BIN_TYPE, 1 ); 
	LINEAR_MULTI_NPROC_TYPE_2( 2, repitch, vibrato, 2, 0, BIN_TYPE, 1 ); 
	}) 
LINEAR_MULTI_NPROC_TYPE_FUNC_2( repitch, vowels, 6, 0, WAV_TYPE, 1 )


void register_lua_cdp_functions_repitch( lua_State * L )
	{
	lua_register( L, "repitch_analenv",		lua_cdp_repitch_analenv		);
	lua_register( L, "repitch_approx",		lua_cdp_repitch_approx		);
	lua_register( L, "repitch_brktopi",		lua_cdp_brktopi_brktopi		);
	lua_register( L, "repitch_combine",		lua_cdp_repitch_combine		);
	lua_register( L, "repitch_combineb",	lua_cdp_repitch_combineb	);
	lua_register( L, "repitch_cut",			lua_cdp_repitch_cut			);
	lua_register( L, "repitch_exag",		lua_cdp_repitch_exag		);
	lua_register( L, "repitch_fix",			lua_cdp_repitch_fix			);
	lua_register( L, "repitch_generate",	lua_cdp_repitch_generate	);
	lua_register( L, "repitch_getpitch",	lua_cdp_repitch_getpitch	);
	lua_register( L, "repitch_insertsil",	lua_cdp_repitch_insertsil	);
	lua_register( L, "repitch_interp",		lua_cdp_repitch_interp		);
	lua_register( L, "repitch_invert",		lua_cdp_repitch_invert		);
	lua_register( L, "repitch_noisetosil",	lua_cdp_repitch_noisetosil	);
	lua_register( L, "repitch_pchshift",	lua_cdp_repitch_pchshift	);
	lua_register( L, "repitch_pchtotext",	lua_cdp_repitch_pchtotext	);
	lua_register( L, "repitch_pitchtosil",	lua_cdp_repitch_pitchtosil	);
	lua_register( L, "repitch_quantise",	lua_cdp_repitch_quantise	);
	lua_register( L, "repitch_randomise",	lua_cdp_repitch_randomise	);
	lua_register( L, "repitch_smooth",		lua_cdp_repitch_smooth		);
	lua_register( L, "repitch_synth",		lua_cdp_repitch_synth		);
	lua_register( L, "repitch_transpose",	lua_cdp_repitch_transpose	);
	//lua_register( L, "repitch_transposef",	lua_cdp_repitch_transposef	);
	lua_register( L, "repitch_vibrato",		lua_cdp_repitch_vibrato		);
	lua_register( L, "repitch_vowels",		lua_cdp_repitch_vowels		);
	}