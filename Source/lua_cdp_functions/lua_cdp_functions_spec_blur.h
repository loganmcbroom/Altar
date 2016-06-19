#pragma once

// All processes within the blur.exe module

// cdp_avrg( N, files )
// cdp_blur( blurring, files )
// cdp_chorus( mode, spread, ?spread2, files )
// cdp_drunk( range, starttime, duration, -z, files )
// cdp_noise( noise, files )
// cdp_scatter( keep, -bblocksize, -r, -n, files )
// cdp_selfism( index, files )
// cdp_shuffle( domainImg, grpsize, files )
// cdp_spread( -fN/-pN, -i, -spread, files )
// cdp_suppress( N, files )
// cdp_weave( weavfile, files )

#include "lua_cdp_utilities.h"

LUA_CDP_MULTI( lua_cdp_blur_avrg, 1, 0, 
	{								
	lua_pushpairs( L, 
		{	// inFile | N
		{ "blur",	1 },		
		{ "avrg",	2 },	
		{ "$",		4 }
		});	// blur | avrg | inFile | $ | N
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_blur, 1, 0,
	{
	lua_pushpairs( L,
		{	// infile | blurring
		{ "blur",	1 },
		{ "blur",	2 },	
		{ "$",		4 }
		});	// blur | blur | infile | $ | blurring
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_chorus_1, 2, 0,
	{								// infile | mode | spread 1
	lua_insert( L, 2 );				// infile | spread 1 | mode
	lua_insert( L, 1 );				// mode | infile | spread 1 
	lua_pushto( L, "blur", 1 );		// blur | mode | inFile | spread 1
	lua_pushto( L, "chorus", 2 );	// blur | chorus | mode | inFile | spread 1
	lua_pushto( L, "$", 5 );		// blur | chorus | mode | inFile | $ | spread 1
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_chorus_2, 3, 0,
	{								// infile | mode | spread 1 | spread 2
	lua_insert( L, 2 );				// infile | spread 2 | mode | spread 1
	lua_insert( L, 2 );				// infile | spread 1 | spread 2 | mode
	lua_insert( L, 1 );				// mode | infile | spread 1 | spread2
	lua_pushto( L, "blur", 1 );		// blur | mode | inFile | spread 1 | spread2
	lua_pushto( L, "chorus", 2 );	// blur | chorus | mode | inFile | spread 1 | spread2
	lua_pushto( L, "$", 5 );		// blur | chorus | mode | inFile | $ | spread 1 | spread2
	return cdp( L );
	})

static int lua_cdp_blur_chorus( lua_State * L )
	{
	if( lua_tonumber( L, 1 ) < 5 ) return lua_cdp_blur_chorus_1( L );
	else return lua_cdp_blur_chorus_2( L );
	}

LUA_CDP_MULTI( lua_cdp_blur_drunk, 3, 1,
	{
	lua_pushpairs( L, 
		{				// infile | range | starttime | duration | -z
		{ "blur",	1 },
		{ "drunk",	2 },
		{ "$",		4 }
		});				// blur | drunk| infile | $ | range | starttime | duration | -z
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_noise, 1, 0,
	{
	lua_pushpairs( L, 
		{	// infile | noise
		{ "blur",	1 },
		{ "noise",	2 },
		{ "$",		4 }
		});	// blur | noise | infile | $ | noise
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_scatter, 1, 3,
	{
	lua_pushpairs( L, 
		{	// infile | keep | -bblocksize | -r | -n
		{ "blur",	1 },
		{ "scatter",2 },
		{ "$",		4 }
		});	// blur | scatter | infile | $ | keep | -bblocksize | -r | -n
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_selfism_selfism, 1, 0,
	{
	lua_pushpairs( L, 
		{	// infile | index
		{ "selfsim",1 },
		{ "selfsim",2 },
		{ "$",		4 }
		});	// selfsim | selfsim | infile | $ | index
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_shuffle, 2, 0,
	{
	lua_pushpairs( L, 
		{	// infile | domain image | grpsize
		{ "blur",	1 },
		{ "shuffle",2 },
		{ "$",		4 }
		});	// blur | shuffle | infile | $ | domain image | grpsize
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_spread, 0, 3,
	{
	lua_pushpairs( L, 
		{	// infile | -fN/-pN | -i | -sspread
		{ "blur",	1 },
		{ "spread", 2 },
		{ "$",		4 }
		});	// blur | spread | infile | $ | -fN/-pN | -i | -sspread
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_suppress, 1, 0,
	{
	lua_pushpairs( L, 
		{	// infile | N
		{ "blur",		1 },
		{ "suppress",	2 },
		{ "$",			4 }
		});	// blur | suppress | infile | $ | N
	return cdp( L );
	})

LUA_CDP_MULTI( lua_cdp_blur_weave, 1, 0,
	{
	lua_pushpairs( L, 
		{	// infile | weavfile
		{ "blur",	1 },
		{ "weave",	2 },
		{ "$",		4 }
		});	// blur | weave | infile | $ | weavfile
	return cdp( L );
	})

void registerLuaCdpFunctions_blur( lua_State * L )
	{
	lua_register( L, "cdp_avrg",		lua_cdp_blur_avrg		);
	lua_register( L, "cdp_blur",		lua_cdp_blur_blur		);
	lua_register( L, "cdp_chorus",		lua_cdp_blur_chorus		);
	lua_register( L, "cdp_drunk",		lua_cdp_blur_drunk		);
	lua_register( L, "cdp_noise",		lua_cdp_blur_noise		);
	lua_register( L, "cdp_scatter",		lua_cdp_blur_scatter	);
	lua_register( L, "cdp_selfism",		lua_cdp_selfism_selfism );
	lua_register( L, "cdp_shuffle",		lua_cdp_blur_shuffle	);
	lua_register( L, "cdp_spread",		lua_cdp_blur_spread		);
	lua_register( L, "cdp_suppress",	lua_cdp_blur_suppress	);
	lua_register( L, "cdp_weave",		lua_cdp_blur_weave		);
	}