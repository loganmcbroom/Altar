#include "lua_cdp_utilities.h"

#include "lua.hpp"
#include <vector>

#include "JuceHeader.h"
#include "..\AltarThread.h"

using namespace std;

//Get the number of channels in the file s
unsigned int getNumChannels( const char * file )
	{
	string s( file );
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

//This function is refered to as the LTMP (Linear Transformation Multi-Processor) system
//It's a utility for allowing multiple audio files to be sent to lua_cdp functions
//It also handles tables being sent as parameters and does a lot of error checking
int lua_multi_proc( lua_State * L, int params, int flags, std::function<int( lua_State* )> f, int groupSize )
	{ // Stack: flags1 | params | flags2 | infile 1 | infile 2 | ...
	//Check to make sure enough stuff was sent

	if( lua_gettop( L ) <= params ) return luaL_error( L, "Too few arguments sent to a CDP function" );

	//Find total extra parameters
	int numReturns = 0;
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
			if( s == nullptr ) return luaL_error( L, "Not enough parameters, or no files passed to function" );

			if( s[0] != '-' ) //We've passed the end of the flags
				{
				extraParams += i;
				break;
				}
			}
		}

	int stackSize = lua_gettop( L );
	if( ( stackSize - extraParams ) % groupSize != 0 )
		return luaL_error( L, "Number of audio files sent to multi-input process \
wasn't divisible by its group size" );
	int numGroups = (stackSize - extraParams) / groupSize;
	
	//==============================================================================================
	//If we are processing multiple times
	//if( stackSize > groupSize + extraParams )
		{ // Call f on each input group
		//This is the only appropriate time to set this flag afaik, lets multi threading procs work
		AltarThread * T = static_cast<AltarThread *>( Thread::getCurrentThread() );
		T->allProcessesSetUp = false;

		//We need to find out how many outputs we need based on several bits of info
		//We'll make extra outputs to fill if there are too many table parameters or too many input groups
		//This segment figures that out
		int numProcs = numGroups;
		{	
		for( int i = 1; i <= extraParams; ++i )
			{
			if( lua_istable( L, i ) )
				{
				size_t tableLength = lua_objlen( L, i );
				if( tableLength > numProcs ) numProcs = tableLength;
				}
			}
		}

		//This deals with the fact that we can take strings or tables from lua
		vector< pair< string, vector< string > > > params;
		for( int i = 1; i <= extraParams; ++i )
			{
			if( lua_isstring( L, i ) ) 
				{
				params.emplace_back( lua_tostring( L, i ), vector<string>() );
				}
			else if( lua_istable( L, i ) ) 
				{
				int numValues = lua_objlen( L, i );
				if( numValues == 0 ) return luaL_error( L, "Empty table passed as parameter to cdp" );
				vector<string> table;
				table.reserve( numValues );
				for( int j = 0; j < numValues; ++j ) 
					{
					//Copy values from the table into our vector, which represents the table
					//Loop if there are more audio groups than values in the table
					lua_rawgeti( L, i, j + 1 );
					if( ! lua_isstring( L, -1 ) ) return luaL_error( L, "Unusable value in LTMP table" );
					table.emplace_back( lua_tostring( L, -1 ) );
					lua_pop( L, 1 );
					} 
				params.emplace_back( "", table );
				}
			else return luaL_error( L, "Unusable parameter passed to the Lua API" );
			}

		vector<string> inFiles;
		for( int i = 0; i < stackSize - extraParams; ++i )
			{
			if( ! lua_isstring( L, extraParams + i + 1 ) ) return luaL_error( L, "Too many parameters passed to unknown function" );
			inFiles.emplace_back( lua_tostring( L, extraParams + i + 1 ) );
			}

		lua_settop( L, 0 );
		vector<string> returns;
		for( int i = 0; i < numProcs; ++i ) //Run the process as many times as is needed
			{
			for( int j = 0; j < groupSize; ++j ) //Mod to loop if needed
				lua_pushstring( L, inFiles[ ( groupSize * i + j ) % inFiles.size() ].c_str() );
			for( auto & j : params )
				{ //If it's a string just push it, if it's a table push the appropriate value
				if( j.second.empty() ) lua_pushstring( L, j.first.c_str() );
				else lua_pushstring( L, j.second[i % j.second.size()].c_str() ); //Mod to loop if needed
				}
			// infile i | infile i + 1 | ... | extra params
			if( i == numProcs - 1 ) T->allProcessesSetUp = true; //Sorry, I'm too lazy to make this better
			int returnCount = f( L ); //Main Call
			for( int j = 0; j < returnCount; ++j )
				{
				returns.emplace_back( lua_tostring( L, j + 1 ) );
				}
			lua_settop( L, 0 );
			}
		for( auto & i : returns ) lua_pushstring( L, i.c_str() );
		numReturns = returns.size();
		}
	/*else //If we are processing a single time
		{ // params | flags | infile 1 | infile 2 | ...
		//If the files aren't a string to begin with there is nothing to do
		for( int i = 0; i < groupSize; ++i )
			if( ! lua_isstring( L, stackSize - 1 ) ) return 0;
		//If we're using table args we only want the first entry of each table
		for( int i = 1; i <= extraParams; ++i ) 
			if( lua_istable( L, i ) )
				{
				lua_rawgeti( L, i, 1 );
				lua_replace( L, i );
				}
		//Flip the audio files back to the
		for( int i = 0; i < groupSize; ++i )
			lua_insert( L, 1 );	// infile 1 | infile 2 | ... | params | flags
		numReturns = f( L );
		}*/
	return numReturns;
	}


//==============================================================================================


//For processes taking arbitrary input.
//Can multi proc, just use tables of files as input groups.
int lua_nonlinear_proc( lua_State * L, int numParams, int flags, std::function<int( lua_State*, int )> f )
	{ // params | flags | inputs
	//Tell the thread to not start running the processes until we're done adding them
	AltarThread * T = static_cast<AltarThread *>( Thread::getCurrentThread() );
	T->allProcessesSetUp = false;


	//Find number of inputs
	int extraParams = numParams;
	if( flags > 0 )
		{
		for( int i = 0; i < flags + 1; ++i )
			{
			if( lua_istable( L, i + 1 + numParams ) ) 
				{ 
				extraParams += i; 
				break;
				}
			const char * s = lua_tostring( L, i + 1 + numParams );
			if( s == nullptr ) return luaL_error( L, "Not enough parameters passed to cdp (unknown function)" );
			if( s[0] != '-' ) //We've passed the end of the flags
				{
				extraParams += i;
				break;
				}
			}
		}
	int numInputs = lua_gettop( L ) - extraParams;

	//Capture all parameters as c++ data structure
	vector< pair< string, vector< string > > > params;
	for( int i = 1; i <= extraParams; ++i )
			{
			if( lua_isstring( L, i ) ) 
				{
				params.emplace_back( lua_tostring( L, i ), vector<string>() );
				}
			else if( lua_istable( L, i ) ) 
				{
				int numValues = lua_objlen( L, i );
				if( numValues == 0 ) return luaL_error( L, "Empty table passed as parameter to cdp" );
				vector<string> table;
				table.reserve( numValues );
				for( int j = 0; j < numValues; ++j ) 
					{
					//Copy values from the table into our vector, which represents the table
					//Loop if there are more audio groups than values in the table
					lua_rawgeti( L, i, j + 1 );
					if( ! lua_isstring( L, -1 ) ) return luaL_error( L, "Unusable value in LTMP table" );
					table.emplace_back( lua_tostring( L, -1 ) );
					lua_pop( L, 1 );
					} 
				params.emplace_back( "", table );
				}
			else return luaL_error( L, "Unusable parameter passed to the Lua API" );
			}

	
	//Capture all inputs as c++ data structure
	vector< vector< string > > inputTables;
	if( lua_istable( L, -1 ) ) //Capturing inputs from multiple tables
		{
		inputTables.resize( numInputs );
		for( int i = 1; i <= numInputs; ++i )
			{
			int length = lua_objlen( L, extraParams + i );
			inputTables[i-1].resize( length );
			for( int j = 1; j <= length; ++j )
				{
				lua_rawgeti( L, extraParams + i, j );
				if( ! lua_isstring( L, -1 ) ) return luaL_error( L, "Unusable value in LTMP table" );
				inputTables[i-1][j-1] = lua_tostring( L, -1 );
				lua_pop( L, 1 );
				}
			}
		}
	else // Capturing single input group as string
		{
		inputTables.resize( 1 );
		inputTables[0].resize( numInputs );
		for( int i = 0; i < numInputs; ++i )
			{
			if( ! lua_isstring( L, extraParams + i + 1 ) ) return luaL_error( L, "Too many parameters passed to unknown function" );
			inputTables[0][i] = lua_tostring( L, extraParams + i + 1 );
			}
		}

	// Get the number of output groups we're generating
	// max of the input group and the length of each parameter table
	int numProcs = inputTables.size();
	{	
	for( int i = 1; i <= extraParams; ++i )
		{
		if( lua_istable( L, i ) )
			{
			size_t tableLength = lua_objlen( L, i );
			if( tableLength > numProcs ) numProcs = tableLength;
			}
		}
	}

	//All input is gathered into data structures. At this point we clear the stack and set up all processes.
	lua_settop( L, 0 );
	vector<string> returns;

	//Set up the process on each input group, telling the thread we're ready before the final call (sorry about this)
	for( int i = 0; i < numProcs; ++i ) 
		{
		//Push the inputs
		for( int j = 0; j < inputTables[i % inputTables.size()].size(); ++j )
			{
			lua_pushstring( L, inputTables[i % inputTables.size()][j].c_str() );
			}

		//Push the parameters
		for( auto & j : params )
			{ //If it's a string just push it, if it's a table push the appropriate value
			if( j.second.empty() ) lua_pushstring( L, j.first.c_str() );
			else lua_pushstring( L, j.second[i % j.second.size()].c_str() ); //Mod to loop if needed
			}

		if( i == numProcs - 1 ) T->allProcessesSetUp = true; //Sorry, I'm too lazy to make this better
		int returnCount = f( L, inputTables[i % inputTables.size()].size() ); //Main Call
		for( int j = 0; j < returnCount; ++j )
			{
			returns.emplace_back( lua_tostring( L, j + 1 ) );
			}
		lua_settop( L, 0 );
		}

	//Pull the only thing we need back into lua
	for( auto & i : returns ) lua_pushstring( L, i.c_str() );
	return returns.size();
	}

