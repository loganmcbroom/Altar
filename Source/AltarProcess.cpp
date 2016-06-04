#include "AltarProcess.h"

#include <sstream>
#include <fstream>
#include <memory>

#include "lua.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

#include "cdp_lua_functions.h"

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

bool cdp( string command, const string & workingDir, vector<string> &outFiles )
	{
	//Check the arguments for any special tokens and replace them with appropriate strings
	{
	//Lambda function for replacing character tokens with generated files of specified type
	auto tokenReplace = [&]( char c, string fileType, vector<string> & output )
		{
		size_t stringPos = 0;
		while( ( stringPos = command.find( c, stringPos ) ) != string::npos )
			{
			string path = "\"" + workingDir + "/_altartemp_" + to_string( getUID() ) + fileType + "\"";
			command.replace( stringPos, 1, path );
			output.emplace_back( path );
			Logger::writeToLog( path );
			}
		};
	//Token replacements
	tokenReplace( '$', ".wav", outFiles );
	}

	//Make the call to the exe requested and display output
	{
	bool startStatus;
	uint32 endStatus;
	{ //Start it up, block until finished, display output, get the exit code. 
		//We can't run away to lua until ChildProcess comes off the stack or we'll get memory leak problems ( hence extra braces )
		ChildProcess cdpProcess;
		Logger::writeToLog( "[CDP] Running command: " + command );
		startStatus = cdpProcess.start( command );
		Logger::writeToLog( "[CDP] " + cdpProcess.readAllProcessOutput() );
		endStatus = cdpProcess.getExitCode();
	}
	//If it errored on startup or on exiting, bail
	if( ! startStatus || endStatus != 0 ) 
		{
		Logger::writeToLog( "[CDP] Exited with error code " + to_string( endStatus ) );
		return false;
		}
	}
	
	//if we get here the call succeeded. Add the planned files onto the generated files list and return the output files
	generatedFiles.insert( generatedFiles.end(), outFiles.begin(), outFiles.end() );

	return true;
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
	registerCdpLuaFunctions( L );
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