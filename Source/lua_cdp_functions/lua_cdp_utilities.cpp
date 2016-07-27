#include "lua_cdp_utilities.h"

#include "lua.hpp"
#include <vector>

#include "JuceHeader.h"

using namespace std;

//Get the number of channels in the file s
unsigned int getNumChannels( const string & s )
	{
	AudioFormatManager afm;
	afm.registerBasicFormats();
	unique_ptr<AudioFormatReader> r( afm.createReaderFor( File( s.substr( 1, s.size() - 2 ) ) ) );
	return r->numChannels;
	}

//Push s to nth position on the stack
void lua_pushto( lua_State * L, const char * s, int n )
	{
	lua_pushstring( L, s );
	lua_insert( L, n );
	}

void lua_pushpairs( lua_State * L, initializer_list< pair< const char *, int > > pairs )
	{
	for( auto & i : pairs )
		lua_pushto( L, i.first, i.second );
	}

//Utility for allowing multiple audio files to be sent to lua_cdp functions
int lua_multi_proc( lua_State * L, int params, int flags, std::function<int( lua_State* )> f, int groupSize )
	{ // Stack: flags1 | params | flags2 | infile 1 | infile 2 | ...
	//Find total extra parameters
	int extraParams = params;
	
	if( flags > 0 )
		{
		//Get number of opening flags
		/*int openingFlags = 0;
		for( int i = 0; i < flags + 1; ++i )
			{
			const char * s = lua_tostring( L, i + 1 );
			if( s == nullptr ) return luaL_error( L, "Not enough parameters passed to unknown function" );

			if( s[0] != '-' ) //We've passed the end of the flags
				{
				extraParams += i;
				break;
				}
			}*/

		//Get number of end flags
		for( int i = 0; i < flags + 1; ++i )
			{
			const char * s = lua_tostring( L, i + 1 + params );
			if( s == nullptr ) return luaL_error( L, "Not enough parameters passed to unknown function" );

			if( s[0] != '-' ) //We've passed the end of the flags
				{
				extraParams += i;
				break;
				}
			}
		}

	if( ( lua_gettop( L ) - extraParams ) % groupSize != 0 )
		return luaL_error( L, "Number of audio files sent to multi-input process \
wasn't divisible by its group size" );

	int stackSize =  lua_gettop( L );
	//If we are processing multiple times
	if( stackSize > groupSize + extraParams )
		{ // Call f on each input group
		// params | flags | infile 1 | infile 2 | ... 
		vector<string> paramStrings;
		for( int i = 0; i < extraParams; ++i )
			paramStrings.emplace_back( lua_tostring( L, i + 1 ) );
		vector<string> inFiles;
		for( int i = 0; i < stackSize - extraParams; ++i )
			{
			if( ! lua_isstring( L, extraParams + i + 1 ) ) return luaL_error( L, "Too many parameters passed to unknown function" );
			inFiles.emplace_back( lua_tostring( L, extraParams + i + 1 ) );
			}

		lua_settop( L, 0 );
		vector<string> returns;
		for( int i = 0; i < inFiles.size() / groupSize; ++i )
			{
			for( int j = 0; j < groupSize; ++j )
				lua_pushstring( L, inFiles[ groupSize * i + j].c_str() );


			for( auto & j : paramStrings )
				lua_pushstring( L, j.c_str() );
			// infile i | infile i + 1 | ... | extra params
			int returnCount = f( L );
			for( int j = 0; j < returnCount; ++j )
				returns.emplace_back( lua_tostring( L, j + 1 ) );
			lua_settop( L, 0 );
			}
		for( auto & i : returns ) lua_pushstring( L, i.c_str() );
		return returns.size();
		}
	else //If we are processing a single time
		{ // params | flags | infile 1 | infile 2 | ...
		for( int i = 0; i < groupSize; ++i )
			lua_insert( L, 1 );	// infile 1 | infile 2 | ... | params | flags
		return f( L );
		}
	}

int lua_nonlinear_proc( lua_State * L, int params, int flags, 
	const char * module, const char * proc, const char * type )
	{ // params | flags | files

	//Find number of files
	int extraParams = params;
	if( flags > 0 )
		{
		for( int i = 0; i < flags + 1; ++i )
			{
			const char * s = lua_tostring( L, i + 1 + params );
			if( s == nullptr ) return luaL_error( L, "Not enough parameters passed to cdp (unknown function)" );
			if( s[0] != '-' ) //We've passed the end of the flags
				{
				extraParams += i;
				break;
				}
			}
		}
	int numFiles = lua_gettop( L ) - extraParams;
	//push output
	lua_pushto( L, type, 1 );
	//move all files to back
	for( int i = 0; i < numFiles; ++i )
		lua_insert( L, 1 );	
	lua_pushpairs( L, { {module, 1}, {proc, 2} } );
	//call
	return cdp( L );
	}

