#include "AltarThread.h"

#include <vector>
#include <sstream>
#include <fstream>

#include "lua.hpp"
#include "lua_cdp_functions/lua_cdp_functions.h"
#include "defines.h"

using namespace std;

CriticalSection AltarThread::mutex;

AltarThread::AltarThread( const String & name, const String & _script, 
						std::function< void( std::vector< File > & ) > & _callback, 
						const std::vector< String > & files )
	: Thread( name )
	, callback( _callback )
	, inFiles()
	, generatedFiles()
	, script( _script )
	, L( lua_open() )
	{
	luaL_openlibs( L );
	//Get stuff out of settings file first
	if( luaL_loadfile( L, ( File::getCurrentWorkingDirectory().getFullPathName() + "/Settings.lua" ).toRawUTF8() ) || lua_pcall( L, 0, 0, 0 ) ) 
		log( string("[Lua] ") + string( lua_tostring(L, -1) ) );
	lua_getglobal( L, "cdpDir" );
	lua_getglobal( L, "workingDir" );
	if( ! lua_isstring( L, -2 ) || ! lua_isstring( L, -1 ) )
		log( string("[Lua] ") + string( lua_tostring(L, -1) ) );
	cdpDir = lua_tostring( L, -2 );
	workingDir = lua_tostring( L, -1 );
	lua_settop( L, 0 );

	register_lua_cdp_functions( L );

	for( auto & i : files ) 
		addFile( i );
	startTime = Time::getMillisecondCounter();
	startThread();
	}

AltarThread::~AltarThread()
	{
	lua_close( L );
	for( auto & i : generatedFiles )
		{
		if( ! File( i.substr( 1, i.size() - 2 ) ).deleteFile() ) log( "Couldn't delete file " + i );
		}
	}

const File & AltarThread::getFile( int index )
	{
	return inFiles[ index ]->getFile();
	}

size_t AltarThread::getNumFiles()
	{
	return inFiles.size();
	}

//=================================================================================================

void AltarThread::log( const String & s )
	{
	MessageManagerLock mml;
	Logger::writeToLog( "{Thread: " + getThreadName() + "} " + s );
	}

void AltarThread::addFile( const File & f )
	{
	inFiles.emplace_back( new TemporaryFile( f ) );
	f.copyFileTo( inFiles.back()->getFile() );
	}

void AltarThread::paint( Graphics & g )
	{
	g.fillAll( isThreadRunning()? PALETTE_2 : PALETTE_1 );

	g.setFont( Font( 18 ) );
	g.setColour( Colours::white );
	g.drawText( getThreadName(), getLocalBounds(), Justification::centred );
	}

void AltarThread::run()
	{
	log( "[PROCESSING START]" );
	auto luaerr = [&]( lua_State * L )
		{
		log( string("[Lua] ") + string( lua_tostring(L, -1) ) );
		};

	//Make sure the script supplied exists
	if( ! File( File::getCurrentWorkingDirectory().getFullPathName() + "/" + script ).exists() )
		{
		log( "Script specified either does not exist or cannot be accessed: " 
			+ (File::getCurrentWorkingDirectory().getFullPathName() + "/" + script).toStdString() );
		return;
		}
	
	//Get the current stack top so we can get the correct number of outputs later
	int top = lua_gettop(L);
	//Load the supplied script
	
	if( luaL_loadfile( L, script.getCharPointer() ) ) 
		luaerr( L );
	//Push the filenames from inClips onto the lua stack
	for( int i = 0; i < inFiles.size(); ++i )
		{
		lua_pushstring( L, ( "\"" + inFiles[i]->getFile().getFullPathName() + "\"" ).getCharPointer() );
		}
	//Make the call
	if( lua_pcall( L, inFiles.size(), LUA_MULTRET, 0 ) )
		{
		luaerr( L );
		lua_settop( L, top );
		}

	//See I told you we would need it.
	int numResults = lua_gettop( L ) - top;
	//Pull all the files returned from lua into a container
	vector< File > outFiles;
	
	for( int i = 0; i < numResults; ++i )
		{
		string s = lua_tostring( L, -(1 + i) );

		//Everything coming out should have quotes on it but juce doesn't like that so we'll pull them
		outFiles.emplace_back( s.substr( 1, s.size() - 2 ) );
		}
	//Close it up, ship it out
	{
	const ScopedLock lock( mutex );
	MessageManagerLock mml;
	callback( outFiles );
	repaint();
	}
	log( "[PROCESSING END] Time elapsed: " 
		+ Time( Time::getMillisecondCounter() - startTime ).formatted( "%M:%S:" ) + 
		to_string( ( Time::getMillisecondCounter() - startTime ) % 1000 ) + " \n\n" );
	}

bool AltarThread::cdp( string & command, const string & info, vector<string> & outFiles )
	{
	string fullCommand = cdpDir + "/" + command;
	//Check the arguments for any special tokens and replace them with appropriate strings
	{
	//Function for replacing character tokens with generated files of specified type
	vector<string> generatedFileNames;
	auto tokenReplace = [&]( char c, string fileType )
		{
		size_t stringPos = 0;
		while( ( stringPos = fullCommand.find( c, stringPos ) ) != string::npos )
			{
			string path = "\"" + workingDir + "/_altar_" + to_string( startTime ) + "_" + to_string( currentUID++ ) + fileType + "\"";
			fullCommand.replace( stringPos, 1, path );
			
			generatedFileNames.emplace_back( path );
			}
		};
	//Token replacements
	tokenReplace( '$', ".wav" );

	//Do lookup for outfile names. Most cdp processes output a single given file but some
	//	output multiple with related names. We use this to handle those cases.
	outFileTypeLookup( outFiles, generatedFileNames, command, info );
	}

	//Make the call to the exe requested and display output
	{ //Start it up, block until finished, display output, get the exit code. 
		//We can't run away to lua until ChildProcess comes off the stack or we'll get memory leak problems ( hence extra braces )
		ChildProcess cdpProcess;
		//log( "[CDP] Running command: " + command );
		bool startStatus = cdpProcess.start( fullCommand );
		String output = cdpProcess.readAllProcessOutput();
		bool endStatus = cdpProcess.getExitCode();
		if( ! startStatus || endStatus != 0 ) 
			{
			log( "[CDP] Error running command " + fullCommand + "\n[CDP] " + output  );
			return false;
			}
	}
	
	//if we get here the call succeeded. Add the planned files onto the generated files list and return the output files
	generatedFiles.insert( generatedFiles.end(), outFiles.begin(), outFiles.end() );

	return true;
	}

void AltarThread::outFileTypeLookup( vector<string> & output, const vector<string> genFileNames, 
										const string & command, const string & info )
	{
	auto getName = []( const string & s ) { return s.substr( 0, s.find( ' ', 0 ) ); };
	auto getData = []( const string & s ) { return stoi( s.substr( s.find( ' ', 0 ) + 1, string::npos ) ); };

	
	if( ! genFileNames.empty() )
		{
		//If the info string is blank cdp will generate the files we made names for
		if( info.empty() ) for( auto & i : genFileNames ) output.emplace_back( i );
		else //The files cdp generates will be based on these generated file names
			{
			if( 0 ) {}
			else log( "Logan McBroom forgot to handle some lua function's info string in outFileTypeLookup: " + getName( info ) );
			}
		}
	else //The files cdp generates will be based on some annoying info like input files
		{
		if( getName( info ) == "housekeep_chans_2" ) 
				{ 
				int numChannels = getData( info ); 

				int pathEndQuote = command.find_last_of( '\"' );
				int pathStartQuote = command.find_last_of( '\"', pathEndQuote - 1 );
				const string path = command.substr( pathStartQuote, string::npos );
				for( int i = 0; i < numChannels; ++i )
					{
					string channel = path;
					output.emplace_back( channel.insert( path.size() - 5, "_c" + to_string( i + 1 ) ) );
					}
				}
		else log( "Logan McBroom forgot to handle some lua function's info string in outFileTypeLookup: " + getName( info ) );
		}
	
	}
