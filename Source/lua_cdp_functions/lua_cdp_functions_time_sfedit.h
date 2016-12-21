#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_cantor_set, {
	case 1: LINEAR_MULTI_PROC( "cantor", "set 1", 5, 1 );
	case 2: LINEAR_MULTI_PROC( "cantor", "set 2", 5, 1 );
	case 3: LINEAR_MULTI_PROC( "cantor", "set 3", 5, 0 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( constrict, constrict, 1, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_cut, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "cut 1", 2, 1 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "cut 2", 2, 1 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "cut 3", 2, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_cutend, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "cutend 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "cutend 2", 1, 1 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "cutend 3", 1, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_cutmany, {
	case 1: return lua_multi_proc( L, 2, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"sfedit", 1}, {"cutmany 1", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {sfeditCutmany, 0} );
		});
	case 2: return lua_multi_proc( L, 2, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"sfedit", 1}, {"cutmany 2", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {sfeditCutmany, 0} );
		});
	case 3: return lua_multi_proc( L, 2, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"sfedit", 1}, {"cutmany 3", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {sfeditCutmany, 0} );
		});
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_excise , {
	case 1: LINEAR_MULTI_PROC( "sfedit", "excise 1", 2, 1 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "excise 2", 2, 1 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "excise 3", 2, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_excises, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "excises 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "excises 2", 1, 1 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "excises 3", 1, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_insert, {
	case 1: LINEAR_MULTI_NPROC( "sfedit", "insert 1", 1, 3, 2 );
	case 2: LINEAR_MULTI_NPROC( "sfedit", "insert 2", 1, 3, 2 );
	case 3: LINEAR_MULTI_NPROC( "sfedit", "insert 3", 1, 3, 2 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_insil, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "insil 1", 2, 3 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "insil 2", 2, 3 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "insil 3", 2, 3 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_isolate_isolate, {
	case 1: return lua_multi_proc( L, 1, 3, []( lua_State * L ){
		lua_pushpairs( L, { {"isolate", 1}, {"isolate 1", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	case 2: return lua_multi_proc( L, 1, 3, []( lua_State * L ){
		lua_pushpairs( L, { {"isolate", 1}, {"isolate 2", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	case 3: return lua_multi_proc( L, 2, 5, []( lua_State * L ){
		lua_pushpairs( L, { {"isolate", 1}, {"isolate 3", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	case 4: return lua_multi_proc( L, 1, 3, []( lua_State * L ){
		lua_pushpairs( L, { {"isolate", 1}, {"isolate 4", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	case 5: return lua_multi_proc( L, 1, 4, []( lua_State * L ){
		lua_pushpairs( L, { {"isolate", 1}, {"isolate 5", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});

	//LINEAR_MULTI_NPROC_TYPE_2( 3, isolate, isolate, 2, 5, WAV_TYPE, 1 );
	//LINEAR_MULTI_NPROC_TYPE_2( 4, isolate, isolate, 1, 3, WAV_TYPE, 1 );
	//LINEAR_MULTI_NPROC_TYPE_2( 5, isolate, isolate, 1, 4, WAV_TYPE, 1 );
	})
NONLINEAR_PROC_FUNC( sfedit, join, 0, 3 )
NONLINEAR_PROC_FUNC( sfedit, joindyn, 1, 3 )
NONLINEAR_PROC_FUNC( sfedit, joinseq, 1, 4 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( manysil, manysil, 2, 0, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_masks, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "masks 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "masks 2", 1, 1 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "masks 3", 1, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( sfedit, noisecut, 4, 1, WAV_TYPE, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_packet_packet, {
	case 1: LINEAR_MULTI_PROC( "packet", "packet 1", 4, 3 );
	case 2: LINEAR_MULTI_PROC( "packet", "packet 2", 4, 3 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_partition_partition, {
	case 1: return lua_multi_proc( L, 2, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"partition", 1}, {"partition 1", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outAppend, lua_tonumber( L, -2 )} );
		});
	case 2: return lua_multi_proc( L, 2, 2, []( lua_State * L )
		{
		lua_pushpairs( L, { {"partition", 1}, {"partition 2", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outAppend, lua_tonumber( L, -2 )} );
		});
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( prefix, silence, 1, 0, WAV_TYPE, 1 )
int lua_cdp_sfedit_randchunks( lua_State * L )
	{
	return lua_multi_proc( L, 2, 3, []( lua_State * L )
		{
		lua_pushpairs( L, { {"sfedit", 1}, {"randchunks", 2} } );
		return cdp( L, {inTruncate, lua_tonumber( L, 4 )} );
		});
	}
LINEAR_MULTI_NPROC_TYPE_FUNC_2( sfedit, replace, 2, 2, WAV_TYPE, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_retime_retime, {
	case 1:  LINEAR_MULTI_PROC( "retime", "retime 1",  2, 0 );
	case 2:  return luaL_error( L, "retime retime 2 is only available in soundloom for some bozo reason" );
	case 3:  LINEAR_MULTI_PROC( "retime", "retime 3",  4, 0 );
	case 4:  LINEAR_MULTI_PROC( "retime", "retime 4",  3, 0 );
	case 5:  LINEAR_MULTI_PROC( "retime", "retime 5",  2, 3 );
	case 6:  LINEAR_MULTI_PROC( "retime", "retime 6",  5, 0 );
	case 7:  LINEAR_MULTI_PROC( "retime", "retime 7",  4, 0 );
	case 8:  LINEAR_MULTI_PROC( "retime", "retime 8",  5, 0 );
	case 9:  LINEAR_MULTI_PROC( "retime", "retime 9",  2, 0 );
	case 10: LINEAR_MULTI_PROC( "retime", "retime 10", 2, 2 );
	case 11: LINEAR_MULTI_INFO_PROC( "retime", "retime 11", 1, 0 );
	case 12: LINEAR_MULTI_INFO_PROC( "retime", "retime 12", 1, 0 );
	case 13: LINEAR_MULTI_PROC( "retime", "retime 13", 1, 0 );
	case 14: LINEAR_MULTI_PROC( "retime", "retime 14", 2, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_shrink_shrink, {
	case 1:  LINEAR_MULTI_PROC( "shrink", "shrink 1",  5, 5 );
	case 2:  LINEAR_MULTI_PROC( "shrink", "shrink 2",  5, 5 );
	case 3:  LINEAR_MULTI_PROC( "shrink", "shrink 3",  5, 5 );
	case 4:  LINEAR_MULTI_PROC( "shrink", "shrink 4",  6, 5 );
	case 5: return lua_multi_proc( L, 5, 10, []( lua_State * L )
		{
		lua_pushpairs( L, { {"shrink", 1}, {"shrink 5", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	case 6: return lua_multi_proc( L, 6, 9, []( lua_State * L )
		{
		lua_pushpairs( L, { {"shrink", 1}, {"shrink 6", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend, 0} );
		});
	})
LUA_CDP_MODAL_MULTI( lua_cdp_silend_silend, {
	case 1: LINEAR_MULTI_PROC( "silend", "silend 1", 1, 0 );
	case 2: LINEAR_MULTI_PROC( "silend", "silend 2", 1, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_sphinx, {
	case 1: NONLINEAR_PROC( sfedit, sphinx 1, 2, 2, WAV_TYPE );
	case 2: NONLINEAR_PROC( sfedit, sphinx 2, 3, 2, WAV_TYPE );
	case 3: NONLINEAR_PROC( sfedit, sphinx 3, 3, 2, WAV_TYPE );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( subtract, subtract, 0, 1, WAV_TYPE, 2 )
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_syllables, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "syllables 1", 3, 1 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "syllables 2", 3, 1 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "syllables 3", 3, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_twixt, {
	case 1: NONLINEAR_PROC( sfedit, twixt 1, 2, 2, WAV_TYPE );
	case 2: NONLINEAR_PROC( sfedit, twixt 2, 3, 2, WAV_TYPE );
	case 3: NONLINEAR_PROC( sfedit, twixt 3, 3, 2, WAV_TYPE );
	case 4: NONLINEAR_PROC( sfedit, twixt 4, 2, 0, WAV_TYPE );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_zcut, {
	case 1: LINEAR_MULTI_PROC( "sfedit", "zcut 1", 2, 0 );
	case 2: LINEAR_MULTI_PROC( "sfedit", "zcut 2", 2, 0 );
	case 3: LINEAR_MULTI_PROC( "sfedit", "zcut 3", 2, 0 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_sfedit_zcuts, {
	case 1: return lua_multi_proc( L, 1, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"sfedit", 1}, {"zcuts 1", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend1, 0} );
		});
	case 2: return lua_multi_proc( L, 1, 0, []( lua_State * L )
		{
		lua_pushpairs( L, { {"sfedit", 1}, {"zcuts 2", 2}, {WAV_TYPE, 4} } );
		return cdp( L, {outUnknownAppend1, 0} );
		});
	})

void register_lua_cdp_functions_sfedit( lua_State * L )
	{
	lua_register( L, "sfedit_set",			lua_cdp_cantor_set			);
	lua_register( L, "sfedit_constrict",	lua_cdp_constrict_constrict );
	lua_register( L, "sfedit_cut",			lua_cdp_sfedit_cut			);
	lua_register( L, "sfedit_cutend",		lua_cdp_sfedit_cutend		);
	lua_register( L, "sfedit_cutmany",		lua_cdp_sfedit_cutmany		);
	lua_register( L, "sfedit_excise",		lua_cdp_sfedit_excise		);
	lua_register( L, "sfedit_excises",		lua_cdp_sfedit_excises		);
	lua_register( L, "sfedit_insert",		lua_cdp_sfedit_insert		);
	lua_register( L, "sfedit_insil",		lua_cdp_sfedit_insil		);
	lua_register( L, "sfedit_isolate",		lua_cdp_isolate_isolate		);
	lua_register( L, "sfedit_join",			lua_cdp_sfedit_join			);
	lua_register( L, "sfedit_joindyn",		lua_cdp_sfedit_joindyn		);
	lua_register( L, "sfedit_joinseq",		lua_cdp_sfedit_joinseq		);
	lua_register( L, "sfedit_manysil",		lua_cdp_manysil_manysil		);
	lua_register( L, "sfedit_masks",		lua_cdp_sfedit_masks		);
	lua_register( L, "sfedit_noisecut",		lua_cdp_sfedit_noisecut		);
	lua_register( L, "sfedit_packet",		lua_cdp_packet_packet		);
	lua_register( L, "sfedit_partition",	lua_cdp_partition_partition );
	lua_register( L, "sfedit_silence",		lua_cdp_prefix_silence		);
	lua_register( L, "sfedit_randchunks",	lua_cdp_sfedit_randchunks	);
	lua_register( L, "sfedit_replace",		lua_cdp_sfedit_replace		);
	lua_register( L, "sfedit_retime",		lua_cdp_retime_retime		);
	lua_register( L, "sfedit_shrink",		lua_cdp_shrink_shrink		);
	lua_register( L, "sfedit_silend",		lua_cdp_silend_silend		);
	lua_register( L, "sfedit_sphinx",		lua_cdp_sfedit_sphinx		);
	lua_register( L, "sfedit_subtract",		lua_cdp_subtract_subtract	);
	lua_register( L, "sfedit_syllables",	lua_cdp_sfedit_syllables	);
	lua_register( L, "sfedit_twixt",		lua_cdp_sfedit_twixt		);
	lua_register( L, "sfedit_zcut",			lua_cdp_sfedit_zcut			);
	lua_register( L, "sfedit_zcuts",		lua_cdp_sfedit_zcuts		);
	}