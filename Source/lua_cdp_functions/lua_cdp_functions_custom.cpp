#pragma once

#include "lua_cdp_functions_custom.h"
#include "..\AltarThread.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int lua_cdp_altar_text( lua_State * L )
	{
	//Convert lua stack to c++ structure
	int numStrings = lua_gettop( L );
	vector< string > strings( numStrings );
	for( int i = 1; i <= numStrings ; ++i ) 
		if( ! lua_isstring( L, i ) ) luaL_error( L, "A non-string was received by altar_text" );
	for( int i = 1; i <= numStrings; ++i ) 
		strings[i-1] = lua_tostring( L, i );
		
	lua_settop( L, 0 );

	//Create files
	AltarThread * T = static_cast<AltarThread *>( Thread::getCurrentThread() );
	for( int i = 0; i < numStrings; ++i )
		{
		std::string s = T->getFreeFilename( ".txt" );
		std::replace( s.begin(), s.end(), '\\', '/' );
		std::ofstream file( s.substr( 1, s.size() - 2 ) );
		file << strings[i];
		file.close();
		lua_pushstring( L, s.c_str() );
		}
	return numStrings;
	}

void register_lua_cdp_functions_custom( lua_State * L )
	{
	lua_register( L, "altar_text",		lua_cdp_altar_text		);
	}