#pragma once

#include "lua_cdp_utilities.h"

LUA_CDP_MODAL_MULTI( lua_cdp_synth_chord, {
	case 1: 
		{
		lua_pushpairs( L, { {"synth", 1}, {"chord 1", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 2:
		{
		lua_pushpairs( L, { {"synth", 1}, {"chord 2", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	})
LUA_CDP_MODAL_MULTI( lua_cdp_synth_clicks, {
	case 1: 
		{
		lua_pushpairs( L, { {"synth", 1}, {"clicks 1", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 2:
		{
		lua_pushpairs( L, { {"synth", 1}, {"clicks 2", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	})
LUA_CDP_MODAL_MULTI( lua_cdp_synth_synthesis, {
	case 1: 
		{
		lua_pushpairs( L, { {"synth", 1}, {"synthesis 1", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 2:
		{
		lua_pushpairs( L, { {"synth", 1}, {"synthesis 2", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 3:
		{
		lua_pushpairs( L, { {"synth", 1}, {"synthesis 3", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	})
int lua_cdp_synth_noise( lua_State * L )
	{
	lua_pushpairs( L, { {"synth", 1}, {"noise", 2}, {WAV_TYPE, 3} } );
	return cdp( L );
	}
int lua_cdp_synth_silence( lua_State * L )
	{
	lua_pushpairs( L, { {"synth", 1}, {"silence", 2}, {WAV_TYPE, 3} } );
	return cdp( L );
	}
int lua_cdp_synth_spectra( lua_State * L )
	{
	lua_pushpairs( L, { {"synth", 1}, {"spectra", 2}, {WAV_TYPE, 3} } );
	return cdp( L, {synthSpectra, 0} );
	}
LUA_CDP_MODAL_MULTI( lua_cdp_synth_wave, {
	case 1: 
		{
		lua_pushpairs( L, { {"synth", 1}, {"wave 1", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 2:
		{
		lua_pushpairs( L, { {"synth", 1}, {"wave 2", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 3:
		{
		lua_pushpairs( L, { {"synth", 1}, {"wave 3", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	case 4:
		{
		lua_pushpairs( L, { {"synth", 1}, {"wave 4", 2}, {WAV_TYPE, 3} } );
		return cdp( L );
		}
	})


void register_lua_cdp_functions_synth( lua_State * L )
	{
	lua_register( L, "synth_chord",		lua_cdp_synth_chord		);
	lua_register( L, "synth_clicks",	lua_cdp_synth_clicks	);
	lua_register( L, "synth_synthesis",	lua_cdp_synth_synthesis	);
	lua_register( L, "synth_noise",		lua_cdp_synth_noise		);
	lua_register( L, "synth_silence",	lua_cdp_synth_silence	);
	lua_register( L, "synth_spectra",	lua_cdp_synth_spectra	);
	lua_register( L, "synth_wave",		lua_cdp_synth_wave		);
	}