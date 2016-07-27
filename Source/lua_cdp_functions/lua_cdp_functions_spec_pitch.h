#pragma once

#include "lua_cdp_utilities.h"

//-----------------------------------------------------------------------
// Pitch
//-----------------------------------------------------------------------

LUA_CDP_MODAL_MULTI( lua_cdp_pitch_altharms, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "pitch", "altharms 1", 0, 1, WAV_TYPE, 2 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "pitch", "altharms 2", 0, 1, WAV_TYPE, 2 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( pitch, chord, 1, 3, WAV_TYPE, 1 )

//bad flags here
//LINEAR_MULTI_NPROC_TYPE_FUNC_2( pitch, chordf, 1, 6, WAV_TYPE, 1 ) 
//LUA_CDP_MODAL_MULTI( lua_cdp_pitch_octmove, {
//	case 1: LINEAR_MULTI_NPROC_TYPE( "pitch", "octmove 1", 1, 1, WAV_TYPE, 2 );
//	case 2: LINEAR_MULTI_NPROC_TYPE( "pitch", "octmove 2", 1, 1, WAV_TYPE, 2 );
//	case 3: LINEAR_MULTI_NPROC_TYPE( "pitch", "octmove 3", 2, 1, WAV_TYPE, 2 );
//	})

LUA_CDP_MODAL_MULTI( lua_cdp_pitch_pick, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "pitch", "pick 1", 1, 1, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "pitch", "pick 2", 1, 1, WAV_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "pitch", "pick 3", 1, 1, WAV_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "pitch", "pick 4", 2, 1, WAV_TYPE, 1 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "pitch", "pick 5", 2, 1, WAV_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_pitch_transp, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "pitch", "transp 1", 1, 1, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "pitch", "transp 2", 1, 1, WAV_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "pitch", "transp 3", 1, 1, WAV_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "pitch", "transp 4", 2, 1, WAV_TYPE, 1 );
	case 5: LINEAR_MULTI_NPROC_TYPE( "pitch", "transp 5", 2, 1, WAV_TYPE, 1 );
	case 6: LINEAR_MULTI_NPROC_TYPE( "pitch", "transp 6", 3, 1, WAV_TYPE, 1 );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_pitch_tune, {
	case 1: LINEAR_MULTI_NPROC_TYPE( "pitch", "tune 1", 1, 4, WAV_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "pitch", "tune 2", 1, 4, WAV_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( tunevary, tunevary, 1, 4, WAV_TYPE, 1 )

//-----------------------------------------------------------------------
// PitchInfo
//-----------------------------------------------------------------------

LINEAR_MULTI_NPROC_TYPE_FUNC_2( pitchinfo, convert, 0, 1, TXT_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( pitchinfo, hear, 0, 1, WAV_TYPE, 1 )
INFO_PROC_FUNC( pitchinfo, info, 0, 0, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_pitchinfo_see, {
	case 1: LINEAR_MULTI_PROC( "pitchinfo", "see 1", 1, 0 );
	case 2: LINEAR_MULTI_PROC( "pitchinfo", "see 2", 0, 0 );
	})
INFO_PROC_FUNC( pitchinfo, zeros, 0, 0, 1 )


void register_lua_cdp_functions_pitch( lua_State * L )
	{
	lua_register( L, "pitch_altharms",	lua_cdp_pitch_altharms		);
	lua_register( L, "pitch_chord",		lua_cdp_pitch_chord			);
	//lua_register( L, "pitch_chordf",		lua_cdp_pitch_chordf		);
	//lua_register( L, "pitch_octmove",		lua_cdp_pitch_octmove		);
	lua_register( L, "pitch_pick",		lua_cdp_pitch_pick			);
	lua_register( L, "pitch_transp",		lua_cdp_pitch_transp		);
	lua_register( L, "pitch_tune",		lua_cdp_pitch_tune			);
	lua_register( L, "pitch_tunevary",	lua_cdp_tunevary_tunevary	);

	lua_register( L, "pitch_convert",	lua_cdp_pitchinfo_convert	);
	lua_register( L, "pitch_hear",	lua_cdp_pitchinfo_hear	);
	lua_register( L, "pitch_info",	lua_cdp_pitchinfo_info	);
	lua_register( L, "pitch_see",	lua_cdp_pitchinfo_see	);
	lua_register( L, "pitch_zeros",	lua_cdp_pitchinfo_zeros	);
	}