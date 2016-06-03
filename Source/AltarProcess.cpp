#include "AltarProcess.h"

#include <sstream>
#include <fstream>
#include <memory>

#include "lua.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

unsigned int getUID()
	{
	static unsigned int currentUID = 0;
	return currentUID++;
	}

vector<string> generatedFiles;

//Called whenever lua goes bad
void luaerr( lua_State *L )
	{
	Logger::writeToLog( String("[Lua] ") + String( lua_tostring(L, -1) ) );
	}

//Deletes everything listed in generated files and clears it
void clearGenerateFiles()
	{
	for( auto &&i : generatedFiles )
		{
		if( ! File( i.substr( 1, i.size() - 2 ) ).deleteFile() )
			Logger::writeToLog( "Couldn't delete file" + i );
		}
	generatedFiles.clear();
	}

//Same as cdp() but doesn't block
//unimplemented, sorry bozo
static int cdpPar( lua_State * L )
	{
	return 0;
	}

//Lua function used for calling arbitrary cdp modules
static int cdp( lua_State * L )
	{
	vector<string> plannedFiles; 
	string fullCommand;
	int numPlannedFiles = 0;

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

	//Check the arguments for any special tokens and replace them with appropriate strings
	{
	//Get the directory to put files in. We could generate files in the OS temp dir but if something breaks we need access
	lua_getglobal( L, "workingDir" );
	string workingDir = getLuaString( -1, "workingDir given in lua script is not a valid string" );
	lua_pop( L, 1 );

	//Lambda function for replacing character tokens with generated files of specified type
	auto tokenReplace = [&]( char c, string fileType )
		{
		size_t stringPos = 0;
		while( ( stringPos = fullCommand.find( c, stringPos ) ) != string::npos )
			{
			string path = "\"" + workingDir + "/_altartemp_" + to_string( getUID() ) + fileType + "\"";
			fullCommand.replace( stringPos, 1, path );
			plannedFiles.emplace_back( path );
			++numPlannedFiles;
			}
		};
	//Token replacements
	tokenReplace( '$', ".wav" );
	}

	//Make the call to the exe requested and display output
	{
	bool startStatus, endStatus;
	{ //Start it up, block until finished, display output, get the exit code. 
		//We can't run away to lua until ChildProcess comes off the stack or we'll get memory leak problems ( hence extra braces )
		ChildProcess cdpProcess;
		startStatus = cdpProcess.start( fullCommand );
		Logger::writeToLog( "[CDP] " + cdpProcess.readAllProcessOutput() );
		endStatus = cdpProcess.getExitCode();
	}

	//If it errored on startup or on exiting, bail all the way out
	if( ! startStatus )  return luaL_error( L, "[CDP] Error starting the CDP process" );
	if( endStatus != 0 ) return luaL_error( L, ( string( "[CDP] Process exited with error code " ) + to_string( endStatus ) ).c_str() );
	}
	
	//if we get here the call succeeded. Add the planned files onto the generated files list and return the output files
	{
	generatedFiles.insert( generatedFiles.end(), plannedFiles.begin(), plannedFiles.end() );
	for( int i = 0; i < numPlannedFiles; ++i )
		{
		Logger::writeToLog( plannedFiles[i] );
		lua_pushstring( L, plannedFiles[i].c_str() );
		}
	}

	return numPlannedFiles;
	}
	
vector<string> altarProcess( const vector<string> &inputs, const string &luaFile )
	{
	//Make sure the script supplied exists
	if( ! File( File::getCurrentWorkingDirectory().getFullPathName() + "/" + luaFile ).exists() )
		{
		Logger::writeToLog( "Script specified either does not exist or cannot be accessed: " 
			+ File::getCurrentWorkingDirectory().getFullPathName() + "/" + luaFile );
		return vector<string>();
		}

	//Pull up a fresh lua state
	lua_State * L = lua_open();
	luaL_openlibs( L );

	//Register all those fine lua functions you made I'm sure
	lua_register( L, "cdp", cdp );
	//Get the current stack top so we can get the correct number of outputs later
	int top = lua_gettop(L);
	//Load the supplied script
	
	if( luaL_loadfile( L, luaFile.c_str() ) ) 
		luaerr( L );
	//Push the filenames from inClips onto the lua stack
	for( int i = 0; i < inputs.size(); ++i )
		{
		lua_pushstring( L, ( "\"" + inputs[i] + "\"" ).c_str() );
		}
	//Make the call
	if( lua_pcall( L, inputs.size(), LUA_MULTRET, 0 ) )
		{
		luaerr( L );
		clearGenerateFiles();
		return vector<string>();
		}

	//See I told you we would need it.
	int numResults = lua_gettop( L ) - top;
	//Pull all the files returned from lua into a container
	vector< string > outFiles;
	for( int i = 0; i < numResults; ++i )
		{
		string s = lua_tostring( L, -(1 + i) );
		if( s == "" )///Ughhh too tired to think about checking the returns for validity, do we even need to?
			{
			}
		//Everything coming out should have quotes on it but juce doesn't like that so we'll pull them
		outFiles.emplace_back( s.substr( 1, s.size() - 2 ) );
		Logger::writeToLog( s.substr( 1, s.size() - 2 ) );
		//We don't know what will be returned so every file has been added to generated files.
		//We'll remove the ones we want and then delete everything else
		generatedFiles.erase( find( generatedFiles.begin(), generatedFiles.end(), s ) );
		}
	//Like I said, delete everything we generated that wasn't returned
	clearGenerateFiles();

	//Close it up, ship it out
	lua_close( L );
	return outFiles;
	}