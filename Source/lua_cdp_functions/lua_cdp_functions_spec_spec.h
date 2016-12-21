#pragma once

#include "lua_cdp_utilities.h"

//-----------------------------------------------------------------------
// Spec
//-----------------------------------------------------------------------
LINEAR_MULTI_NPROC_TYPE_FUNC_2( spec, bare, 0, 1, WAV_TYPE, 2 );
//clean, superseded by specnu clean
LINEAR_MULTI_NPROC_TYPE_FUNC_2( spec, cut, 2, 0, WAV_TYPE, 1 );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( spec, gain, 1, 0, WAV_TYPE, 1 );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( spec, gate, 1, 0, WAV_TYPE, 1 );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( spec, grab, 1, 0, WAV_TYPE, 1 );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( spec, magnify, 2, 0, WAV_TYPE, 1 );

//-----------------------------------------------------------------------
// SpecNu
//-----------------------------------------------------------------------
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specnu, clean, 2, 0, ANA_TYPE, 2 );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specnu, rand, 0, 2, ANA_TYPE, 1 );
LUA_CDP_MODAL_MULTI( lua_cdp_specnu_remove, {
	case 1: LINEAR_MULTI_PROC_TYPE( "specnu", "remove 1", 4, 0, ANA_TYPE );
	case 2: LINEAR_MULTI_PROC_TYPE( "specnu", "remove 2", 4, 0, ANA_TYPE );
	})
LUA_CDP_MODAL_MULTI( lua_cdp_specnu_slice, {
	case 1: {
		int numFiles = lua_tointeger( L, -2 );
		return lua_multi_proc( L, 2, 0, [numFiles]( lua_State * L )
			{ 
			lua_pushpairs( L, { {"specnu", 1}, {"slice 1", 2}, {ANA_TYPE, 4} } ); 
			return cdp( L, {outTrancate, numFiles} );
			});
		}
	case 2: {
		int numFiles = lua_tointeger( L, -2 );
		return lua_multi_proc( L, 2, 0, [numFiles]( lua_State * L )
			{ 
			lua_pushpairs( L, { {"specnu", 1}, {"slice 2", 2}, {ANA_TYPE, 4} } ); 
			return cdp( L, {outTrancate, numFiles} );
			});
		}
	case 3: {
		int numFiles = lua_tointeger( L, -2 );
		return lua_multi_proc( L, 2, 0, [numFiles]( lua_State * L )
			{ 
			lua_pushpairs( L, { {"specnu", 1}, {"slice 3", 2}, {ANA_TYPE, 4} } ); 
			return cdp( L, {outTrancate, numFiles} );
			});
		}
	case 4: {
		return lua_multi_proc( L, 2, 0, []( lua_State * L )
			{ 
			lua_pushpairs( L, { {"specnu", 1}, {"slice 4", 2}, {WAV_TYPE, 4} } ); 
			return cdp( L, {outUnknownTruncate, 0} );
			});
		}
	case 5: {
		return lua_multi_proc( L, 2, 0, []( lua_State * L )
			{ 
			lua_pushpairs( L, { {"specnu", 1}, {"slice 5", 2}, {ANA_TYPE, 4} } ); 
			return cdp( L, {outUnknownTruncate, 0} );
			});
		}
	}) 
int lua_cdp_specgrids_specgrids( lua_State * L )
	{
	int numFiles = lua_tointeger( L, 1 );
	return lua_multi_proc( L, 2, 0, [numFiles]( lua_State * L )
		{
		lua_pushpairs( L, { {"specgrids", 1}, {"specgrids", 2}, {ANA_TYPE, 4} } );
		return cdp( L, {specNuSpecgrids, numFiles} );
		});
	}

LINEAR_MULTI_NPROC_TYPE_FUNC_2( specnu, squeeze, 2, 0, ANA_TYPE, 1 );
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specnu, subtract, 2, 0, ANA_TYPE, 2 );

//-----------------------------------------------------------------------
// SpecInfo
//-----------------------------------------------------------------------
INFO_PROC_FUNC( specinfo, channel, 1, 0, 1 )
INFO_PROC_FUNC( specinfo, frequency, 1, 0, 1 )
LUA_CDP_MODAL_MULTI( lua_cdp_get_partials_harmonic, {
	case 1: LINEAR_MULTI_INFO_PROC( "get_partials", "harmonic 1", 2, 1 );
	case 2: LINEAR_MULTI_INFO_PROC( "get_partials", "harmonic 2", 2, 1 );
	case 3: LINEAR_MULTI_INFO_PROC( "get_partials", "harmonic 3", 3, 1 );
	case 4: LINEAR_MULTI_INFO_PROC( "get_partials", "harmonic 4", 3, 1 );
	})
LINEAR_MULTI_PROC_FUNC_2( specinfo, level, 0, 0 )
LUA_CDP_MODAL_MULTI( lua_cdp_peak_extract , {
	case 1: LINEAR_MULTI_NPROC_TYPE( "peak", "extract 1", 5, 5, TXT_TYPE, 1 );
	case 2: LINEAR_MULTI_NPROC_TYPE( "peak", "extract 2", 5, 6, TXT_TYPE, 1 );
	case 3: LINEAR_MULTI_NPROC_TYPE( "peak", "extract 3", 5, 6, TXT_TYPE, 1 );
	case 4: LINEAR_MULTI_NPROC_TYPE( "peak", "extract 4", 5, 6, TXT_TYPE, 1 );
	})
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specinfo, octvu, 1, 1, TXT_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specinfo, peak, 0, 4, TXT_TYPE, 1 )
LINEAR_MULTI_NPROC_TYPE_FUNC_2( specinfo, print, 1, 1, TXT_TYPE, 1 )

///Bad flags
//LUA_CDP_MODAL_MULTI( lua_cdp_specinfo_report, {
//	case 1: LINEAR_MULTI_NPROC_TYPE( "peak", "report 1", 5, 5, TXT_TYPE, 1 );
//	case 2: LINEAR_MULTI_NPROC_TYPE( "peak", "report 2", 5, 6, TXT_TYPE, 1 );
//	case 3: LINEAR_MULTI_NPROC_TYPE( "peak", "report 3", 5, 6, TXT_TYPE, 1 );
//	case 4: LINEAR_MULTI_NPROC_TYPE( "peak", "report 4", 5, 6, TXT_TYPE, 1 );
//	})

INFO_PROC_FUNC( specinfo, windowcnt, 0, 0, 1 )

void register_lua_cdp_functions_spec( lua_State * L )
	{
	lua_register( L, "spec_bare",			lua_cdp_spec_bare				);
	lua_register( L, "spec_cut",			lua_cdp_spec_cut				);
	lua_register( L, "spec_gain",			lua_cdp_spec_gain				);
	lua_register( L, "spec_gate",			lua_cdp_spec_gate				);
	lua_register( L, "spec_grab",			lua_cdp_spec_grab				);
	lua_register( L, "spec_magnify",		lua_cdp_spec_magnify			);

	lua_register( L, "specnu_clean",		lua_cdp_specnu_clean			);
	lua_register( L, "specnu_rand",			lua_cdp_specnu_rand				);
	lua_register( L, "specnu_remove",		lua_cdp_specnu_remove			);
	lua_register( L, "specnu_slice",		lua_cdp_specnu_slice			);
	lua_register( L, "specnu_specgrids",	lua_cdp_specgrids_specgrids		);
	lua_register( L, "specnu_squeeze",		lua_cdp_specnu_squeeze			);
	lua_register( L, "specnu_subtract",		lua_cdp_specnu_subtract			);

	lua_register( L, "specinfo_channel",	lua_cdp_specinfo_channel		);
	lua_register( L, "specinfo_frequency",	lua_cdp_specinfo_frequency		);
	lua_register( L, "specinfo_harmonic",	lua_cdp_get_partials_harmonic	);
	lua_register( L, "specinfo_level",		lua_cdp_specinfo_level			);
	lua_register( L, "specinfo_extract",	lua_cdp_peak_extract			);
	lua_register( L, "specinfo_octvu",		lua_cdp_specinfo_octvu			);
	lua_register( L, "specinfo_peak",		lua_cdp_specinfo_peak			);
	lua_register( L, "specinfo_print",		lua_cdp_specinfo_print			);
	//lua_register( L, "specinfo_report",	lua_cdp_specinfo_report			);
	lua_register( L, "specinfo_windowcnt",	lua_cdp_specinfo_windowcnt		);


	}