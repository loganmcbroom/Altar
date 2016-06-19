#pragma once

#include <functional>
#include "lua.hpp"
#include "lua_cdp_functions.h"

//Get the number of channels in the file s
unsigned int getNumChannels( const std::string & s );

//Push s to nth position on the stack
void inline lua_pushto( lua_State * L, const char * s, int n );
void lua_pushpairs( lua_State * L, std::initializer_list< std::pair< const char *, int > > pairs );

//Used by the macro below to define functions which can process any number of input files
int lua_multi_proc( lua_State * L, int numDefiniteParams, 
							int numOptionalParams, std::function< int( lua_State * ) > f );

#define LUA_CDP_MULTI( name, defParams, optionalParams, func ) int name( lua_State * L ) \
	{ return lua_multi_proc( L, defParams, optionalParams, []( lua_State * L ){ func } ); }

