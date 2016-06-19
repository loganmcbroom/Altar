#pragma once

#include "lua_cdp_utilities.h"

// cdp_bakup( file, ... )
// cdp_batchexpand( mode, batchfile, file, ..., datafile, ic, oc, pc )
// cdp_bundle( mode, file, ..., outtextfile )
// cdp_chanphase( channel, files )
/// cdp_chans(
/// cdp_copy(
// cdp_deglitch( glitch, sil, thresh, splice, window, -s, files )
/// cdp_disk(
// cdp_endclicks( gate, splicelen, -b, -e, files )
/// cdp_extract(
/// cdp_??? the gate thing
// cdp_gate( mode, gatelevel, files )
// cdp_remove( -a, files )
/// cdp_respec(
/// cdp_sort(


static int lua_cdp_housekeep_bakup( lua_State * L )
	{
	lua_pushpairs( L,
		{
		{ "housekeep",	1 },
		{ "bakup",		2 }
		});
	lua_pushstring( L, "$" );
	return cdp( L );
	}

static int lua_cdp_housekeep_batchexpand( lua_State * L )
	{
	lua_pushpairs( L,
		{
		{ "housekeep",	 1 },
		{ "batchexpand", 2 }
		});
	return cdp( L );
	}

static int lua_cdp_housekeep_bundle( lua_State * L )
	{
	lua_pushpairs( L,
		{
		{ "housekeep",	1 },
		{ "bundle",		2 }
		});
	return cdp( L );
	}

LUA_CDP_MULTI( lua_cdp_chanphase_chanphase, 1, 0,
	{
	lua_pushpairs( L,
		{
		{ "chanphase", 1 },
		{ "chanphase", 2 },
		{ "$", 4 }
		});
	return cdp( L );
	})

///other chans
LUA_CDP_MULTI( lua_cdp_housekeep_chans_2, 0, 0,
	{									
	int numChannels = getNumChannels( lua_tostring( L, 1 ) );
	lua_pushpairs( L, 
		{					// infile
		{ "housekeep", 1 },	// housekeep | infile
		{ "chans 2", 2  }	// housekeep | chans 2 | infile
		});	
	cdp( L, "housekeep_chans_2 " + to_string( numChannels ) );
	return numChannels;
	})

static int lua_cdp_housekeep_chans( lua_State * L )
	{
	}

///copy

LUA_CDP_MULTI( lua_cdp_housekeep_deglitch, 5, 1,
	{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "deglitch", 2 },
		{ "$", 4 }
		});
	return cdp( L );
	})

///disk

LUA_CDP_MULTI( lua_cdp_housekeep_endclicks, 2, 2,
	{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "endclicks", 2 },
		{ "$", 4 }
		});
	return cdp( L );
	})

///extract

///Test to see what the deal with zzerocount is
LUA_CDP_MULTI( lua_cdp_housekeep_gate, 1, 0,
	{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "gate", 2 },
		{ "$", 4 }
		});
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_gate_gate, 2, 0,
	{					// file | mode | gatelevel
	lua_insert( L, 2 ); // file | gatelevel | mode
	lua_insert( L, 1 );	// mode | file | gatelevel 
	lua_pushpairs( L,
		{	
		{ "gate", 1 },
		{ "gate", 2 },
		{ "$", 5 }
		});
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_housekeep_remove, 0, 1,
	{
	lua_pushpairs( L,
		{
		{ "housekeep", 1 },
		{ "remove", 2 }
		});
	return cdp( L );
	})

///respec

///sort

void register_lua_cdp_functions_housekeep( lua_State * L )
	{
	lua_register( L, "cdp_bakup",		lua_cdp_housekeep_bakup );
	lua_register( L, "cdp_batchexpand",	lua_cdp_housekeep_batchexpand );
	lua_register( L, "cdp_bundle",		lua_cdp_housekeep_bundle );
	lua_register( L, "cdp_chanphase",	lua_cdp_chanphase_chanphase );
	///lua_register( L, "cdp_chans", lua_cdp_housekeep_chans );
	///lua_register( L, "cdp_copy", lua_cdp_housekeep_chans );
	lua_register( L, "cdp_deglitch",	lua_cdp_housekeep_deglitch );
	///lua_register( L, "cdp_disk",		lua_cdp_housekeep_deglitch );
	lua_register( L, "cdp_endclicks",	lua_cdp_housekeep_endclicks );
	///lua_register( L, "cdp_extract",	lua_cdp_housekeep_endclicks );
	///lua_register( L, "cdp_", lua_cdp_housekeep_gate ); figure out a name
	lua_register( L, "cdp_gate",		lua_cdp_gate_gate );
	lua_register( L, "cdp_remove",		lua_cdp_housekeep_remove );
	///lua_register( L, "cdp_respec",		lua_cdp_housekeep_remove );
	///lua_register( L, "cdp_sort",		lua_cdp_housekeep_remove );

	///remove
	lua_register( L, "cdp_chans2",		lua_cdp_housekeep_chans_2 );
	
	}