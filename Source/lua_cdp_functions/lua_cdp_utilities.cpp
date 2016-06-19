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
int lua_multi_proc( lua_State * L, int numDefiniteParams, 
							int numOptionalParams, std::function< int( lua_State * ) > f )
	{
	//Find total extra parameters
	int extraParams = numDefiniteParams;
	for( int i = 0; i < numOptionalParams + 1; ++i )
		{
		const char * s = lua_tostring( L, i + 1 + numDefiniteParams );
		if( s[0] != '-' ) //We've passed the end of the optional params
			{
			extraParams += i;
			break;
			}
		}

	int stackSize =  lua_gettop( L );
	if( stackSize > 1 + extraParams )
		{ // Call f on each channel
		// def params | optional params | infile 1 | infile 2 | ... 
		vector<string> params;
		for( int i = 0; i < extraParams; ++i )
			params.emplace_back( lua_tostring( L, i + 1 ) );
		vector<string> inFiles;
		for( int i = 0; i < stackSize - extraParams; ++i )
			inFiles.emplace_back( lua_tostring( L, extraParams + i + 1 ) );

		lua_settop( L, 0 );
		vector<string> returns;
		for( auto & i : inFiles )
			{
			lua_pushstring( L, i.c_str() );
			for( auto & j : params )
				lua_pushstring( L, j.c_str() );
			// infile i | extra params
			int returnCount = f( L );
			for( int j = 0; j < returnCount; ++j )
				returns.emplace_back( lua_tostring( L, j + 1 ) );
			lua_settop( L, 0 );
			}
		for( auto & i : returns ) lua_pushstring( L, i.c_str() );
		return returns.size();
		}
	else // infile
		return f( L );
	}