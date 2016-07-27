#pragma once

#include "lua_cdp_utilities.h"

LINEAR_MULTI_PROC_FUNC( lua_cdp_flutter_flutter, "flutter", "flutter", 4, 1 );
LUA_CDP_MODAL_MULTI( lua_cdp_fracture_fracture,{
	case 1: LINEAR_MULTI_PROC( "fracture", "fracture 1", 6, 12 );
	case 2: LINEAR_MULTI_PROC( "fracture", "fracture 2", 10, 19 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_frame_shift,{
	case 1: LINEAR_MULTI_PROC( "frame", "shift 1", 2, 1 );
	case 2: LINEAR_MULTI_PROC( "frame", "shift 2", 3, 1 );
	case 3: LINEAR_MULTI_PROC( "frame", "shift 3", 1, 0 );
	case 4: LINEAR_MULTI_PROC( "frame", "shift 4", 1, 0 );
	case 5: LINEAR_MULTI_PROC( "frame", "shift 5", 0, 1 );
	case 6: LINEAR_MULTI_PROC( "frame", "shift 6", 2, 0 );
	case 7: LINEAR_MULTI_PROC( "frame", "shift 7", 2, 0 );
	case 8: LINEAR_MULTI_PROC( "frame", "shift 8", 0, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_mchanpan_mchanpan,{
	case 1: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 1", 2, 1 );
	case 2: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 2", 2, 2 );
	case 3: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 3", 6, 1 );
	case 4: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 4", 5, 0 );
	case 5: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 5", 3, 1 );
	case 6: 
		{
		int numFiles = lua_gettop( L ) - 6;
		for( int i = 0; i < numFiles; ++i ) lua_insert( L, 1 );
		lua_pushpairs( L, { {"mchanpan", 1}, {"mchanpan 6", 2}, {WAV_TYPE, 3 + numFiles } });
		return cdp( L );
		}
	case 7: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 7", 2, 0 );
	case 8: return luaL_error( L, "lua_cdp_mchanpan_mchanpan mode 8 is only available in the Sound Loom GUI" );
	case 9: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 9", 4, 1 );
	case 10: LINEAR_MULTI_PROC( "mchanpan", "mchanpan 10", 1, 5 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_mchanrev_mchanrev, "mchanrev", "mchanrev", 7, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_mchiter_iter,{
	case 1: LINEAR_MULTI_PROC( "mchiter", "iter 1", 2, 7 );
	case 2: LINEAR_MULTI_PROC( "mchiter", "iter 2", 2, 7 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_mchshred_shred, {
	case 1: LINEAR_MULTI_PROC( "mchshred", "shred 1", 4, 0 );
	case 2: LINEAR_MULTI_PROC( "mchshred", "shred 2", 3, 0 );
	})
LUA_CDP_UNSUPPORTED( lua_cdp_mchstereo_mchstereo )
LUA_CDP_MODAL_MULTI( lua_cdp_mchzig_zag, {
	case 1: LINEAR_MULTI_PROC( "mchzig", "zag 1", 5, 0 );
	case 2: LINEAR_MULTI_PROC( "mchzig", "zag 2", 2, 2 );
	})
LINEAR_MULTI_PROC_FUNC( lua_cdp_multimix_create , "mton", "mton", 1, 0 );
LINEAR_MULTI_PROC_FUNC( lua_cdp_newmix_multichan, "newmix", "multichan", 0, 3 )
LUA_CDP_UNSUPPORTED( lua_cdp_panorama_panorama )
LUA_CDP_MODAL_MULTI( lua_cdp_strans_multi,{
	case 1: LINEAR_MULTI_PROC( "strans", "multi 1", 1, 1 );
	case 2: LINEAR_MULTI_PROC( "strans", "multi 2", 1, 1 );
	case 3: LINEAR_MULTI_PROC( "strans", "multi 3", 2, 1 );
	case 4: LINEAR_MULTI_PROC( "strans", "multi 4", 2, 0 );
	})

//====================================================================
// Tangent Group
//====================================================================
LUA_CDP_MODAL_MULTI( lua_cdp_tangent_onefile, {
	case 1: LINEAR_MULTI_PROC_TYPE( "tangent", "onefile 1", 4, 5, "^" );
	case 2: LINEAR_MULTI_PROC_TYPE( "tangent", "onefile 2", 4, 4, "^" );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_tangent_twofiles, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "tangent", "twofiles 1", 5, 5, "^", 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "tangent", "twofiles 2", 5, 4, "^", 2 );
	})
LUA_CDP_UNSUPPORTED( lua_cdp_tangent_sequence )
LUA_CDP_MODAL_MULTI( lua_cdp_tangent_list, {
	case 1: LINEAR_MULTI_PROC_TYPE( "tangent", "list 1", 3, 5, MMX_TYPE );
	case 2: LINEAR_MULTI_PROC_TYPE( "tangent", "list 2", 3, 4, MMX_TYPE );
	})

LUA_CDP_UNSUPPORTED( lua_cdp_texmchan_texmchan )

//====================================================================
// Transit Group
//====================================================================
LUA_CDP_UNSUPPORTED( lua_cdp_transit_simple )
LUA_CDP_UNSUPPORTED( lua_cdp_transit_filtered )
LUA_CDP_UNSUPPORTED( lua_cdp_transit_doppler )
LUA_CDP_UNSUPPORTED( lua_cdp_transit_doplfilt )
LUA_CDP_UNSUPPORTED( lua_cdp_transit_sequence )
LUA_CDP_UNSUPPORTED( lua_cdp_transit_list )

//====================================================================
// Multi-Channel Toolkit (Pls no flags before params)
//====================================================================
LUA_CDP_UNSUPPORTED( lua_cdp_abfpan )
LUA_CDP_UNSUPPORTED( lua_cdp_abfpan2 )
LUA_CDP_UNSUPPORTED( lua_cdp_channelx )
static int lua_cdp_chorder( lua_State * L ) { 
	return lua_multi_proc( L, 1, 0, []( lua_State * L ) 
		{ 
		lua_pushpairs( L, { {"chorder", 1}, {WAV_TYPE, 3} } ); 
		return cdp( L ); 
		}); 
	}
LUA_CDP_UNSUPPORTED_CONST( lua_cdp_chxformat )
LUA_CDP_UNSUPPORTED( lua_cdp_multichannel_copysfx )
LUA_CDP_UNSUPPORTED( lua_cdp_multichannel_fmdcode )
static int lua_cdp_interlx( lua_State * L )
	{									// infile 1 | infile 2 | ... 
	lua_pushto( L, "interlx", 1 );		// interlx | infile 1 | infile 2 | ...
	lua_pushto( L, WAV_TYPE, 2 );			// interlx | $ | infile 1 | infile 2 | ...
	return cdp( L );
	}
LUA_CDP_UNSUPPORTED( lua_cdp_njoin )
LUA_CDP_UNSUPPORTED( lua_cdp_nmix )
LUA_CDP_UNSUPPORTED( lua_cdp_paplay )
LUA_CDP_UNSUPPORTED( lua_cdp_rmsinfo )
LUA_CDP_UNSUPPORTED( lua_cdp_sfprops )

void register_lua_cdp_functions_multichannel( lua_State * L )
	{
	lua_register( L, "multichannel_flutter",	lua_cdp_flutter_flutter );
	lua_register( L, "multichannel_fracture", lua_cdp_fracture_fracture );
	lua_register( L, "multichannel_shift",	lua_cdp_frame_shift );
	lua_register( L, "multichannel_pan",		lua_cdp_mchanpan_mchanpan );
	lua_register( L, "multichannel_rev",		lua_cdp_mchanrev_mchanrev );
	lua_register( L, "multichannel_iter",		lua_cdp_mchiter_iter );
	lua_register( L, "multichannel_shred",	lua_cdp_mchshred_shred );
	lua_register( L, "multichannel_zag",		lua_cdp_mchzig_zag );
	lua_register( L, "multichannel_create",	lua_cdp_multimix_create );
	lua_register( L, "multichannel_newmix",	lua_cdp_newmix_multichan );
	lua_register( L, "multichannel_strans",	lua_cdp_strans_multi );

	lua_register( L, "multichannel_onefile",	lua_cdp_tangent_onefile );
	lua_register( L, "multichannel_twofiles",	lua_cdp_tangent_twofiles );
	lua_register( L, "multichannel_list",		lua_cdp_tangent_list );

	lua_register( L, "multichannel_texmchan",	lua_cdp_texmchan_texmchan );

	lua_register( L, "multichannel_chorder",	lua_cdp_chorder );
	lua_register( L, "multichannel_interlx",	lua_cdp_interlx );
	}