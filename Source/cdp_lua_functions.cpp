#include "cdp_lua_functions.h"

#include <vector>
#include <string>

#include "lua.hpp"

#include "AltarThread.h"

using namespace std;

//Same as cdp() but doesn't block
//unimplemented, sorry bozo
static int cdpPar( lua_State * L )
	{
	return 0;
	}

//Lua function used for calling arbitrary cdp modules
static int lua_cdp( lua_State * L )
	{
	string fullCommand;

	//Lambda function for getting and checking strings from the lua stack
	auto getLuaString = [ &L ]( int index, const char * error )
		{
		const char * s = lua_tostring( L, index );
		if( s == nullptr ) luaL_error( L, error );
		return string( s );
		};

	//Get the module name and cdp directory, form the complete exe string and copy to fullCommand
	{
	string exe = getLuaString( 1, "Module name sent to cdp is not a valid string" );
	lua_getglobal( L, "cdpDir" );
	fullCommand = getLuaString( -1, "cdpDir given in lua script is not a valid string" ) + exe + string( ".exe" );
	lua_pop( L, 1 );
	}

	//Get remaining arguments from the lua stack
	{
	int argCount = lua_gettop( L ) - 1;
	for( int i = 0; i < argCount; ++i )
		{
		//+2 accounting for lua indices starting at one and the first stack entry being the module name
		fullCommand += " " + getLuaString( i + 2, "Unknown argument passed to cdp is not a valid string" );
		}
	}
	
	//Get the directory to put files in. 
	//We could generate files in the OS temp dir but if something breaks we need access
	lua_getglobal( L, "workingDir" );
	string workingDir = getLuaString( -1, "workingDir given in lua script is not a valid string" );
	lua_pop( L, 1 );

	vector<string> outFiles;
	if( ! static_cast<AltarThread *>( Thread::getCurrentThread() )->cdp( fullCommand, workingDir, outFiles ) ) 
	
		luaL_error( L, "Exiting lua: error from CDP" );

	for( int i = 0; i < outFiles.size(); ++i )
		{
		lua_pushstring( L, outFiles[i].c_str() );
		}

	return outFiles.size();
	}

//Normalize infile to given level
static int lua_cdp_normalize( lua_State * L )
	{
	//Normalize is in the modify module
	lua_pushstring( L, "modify" );
	lua_insert( L, 1 );
	//loudness 3 = normalize
	lua_pushstring( L, "loudness 3" );
	lua_insert( L, 2 );
	//Push in a token for output file
	lua_pushstring( L, "$" );

	//Stack: "modify" | "loudness 3" | infile | volume? | "$"

	//If no volume was sent there are now 4 elements on the stack, set the volume to .9
	if( lua_gettop( L ) == 4 ) lua_pushstring( L, "-l0.9" );
	else
		{ //volume was sent, change it from number to string
		double volume = lua_tonumber( L, 4 );
		string volumeString = "-l" + to_string( volume );
		lua_pushstring( L, volumeString.c_str() );
		lua_insert( L, -2 );
		}

	return lua_cdp( L );
	}


void registerCdpLuaFunctions( lua_State * L )
	{
	lua_register( L, "cdp", lua_cdp );
	lua_register( L, "cdp_normalize", lua_cdp_normalize );
	}