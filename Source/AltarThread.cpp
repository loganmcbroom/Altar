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
	, script( _script )
	, L( lua_open() )
	{
	//We don't want to start the thread if something goes wrong
	bool startupError = false;
	auto err = [&]( const char * error )
		{
		log( string("[Lua] ") + string( error ) );
		startupError = true;
		};

	luaL_openlibs( L );

	//Get stuff out of settings file first
	if( luaL_loadfile( L, ( File::getCurrentWorkingDirectory().getFullPathName() + "/Settings.lua" ).toRawUTF8() ) || lua_pcall( L, 0, 0, 0 ) ) 
		err( lua_tostring(L, -1) );
	lua_getglobal( L, "cdpDir" );
	if( ! lua_isstring( L, -1 ) )
		err( lua_tostring(L, -1) );
	
	//Just double check that the settings are solid
	if( File::isAbsolutePath( lua_tostring( L, -1 ) ) )
		{
		File f( lua_tostring( L, -1 ) );
		if( f.exists() && f.isDirectory() ) 
			cdpDir = lua_tostring( L, -1 );
		else err( "The CDP path in Settings.lua wither doesn't exist or isn't a directory" );
		}
	else err( "The CDP directory in Settings.lua is not a valid path" );

	//Clear the stack back out
	lua_settop( L, 0 );
	
	//Create a folder to do all this thread's dealings in
	workingDir = File::getCurrentWorkingDirectory().getChildFile( getThreadName() );
	if( ! workingDir.createDirectory() )
		err( "Couldn't create a working directory for thread" );

	//Load up the lua cdp interface
	register_lua_cdp_functions( L );

	//In case we need local files
	lua_pushstring( L, workingDir.getFullPathName().toRawUTF8() );
	lua_setglobal( L, "dir" );

	for( auto & i : files ) 
		addFile( i );

	repaint();
	//This keeps track of how long the script took
	startTime = Time::getMillisecondCounter();
	//Boot it up!
	if( ! startupError ) startThread();
	}

AltarThread::~AltarThread()
	{
	if( isThreadRunning() )
		stopThread( -1 );

	lua_close( L );
	workingDir.deleteRecursively();
	}

const File & AltarThread::getFile( int index )
	{
	return *inFiles[ index ];
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
	inFiles.emplace_back( new File( workingDir.getNonexistentChildFile( "input", ".wav" ) ) );
	if( ! f.copyFileTo( *inFiles.back().get() ) )
		{
		log( "Couldn't copy the necessary files" );
		signalThreadShouldExit();
		}
	}

void AltarThread::paint( Graphics & g )
	{
	g.fillAll( threadFinished? PALETTE_1 : PALETTE_2 );

	g.setFont( Font( 18 ) );
	g.setColour( Colours::white );
	g.drawText( getThreadName(), getLocalBounds(), Justification::centred );
	}

//We need this for the lua file object metatable
static int lua_f_index( lua_State * L )
	{											// f table | index
	lua_rawgeti( L, 1, lua_tointeger( L, 2 ) ); // f table | index | file string
	if( lua_isnil( L, 3 ) ) 
		{
		if( lua_tointeger( L, 2 ) == 0 ) 
			return luaL_error( L, "You accessed f[0], in lua indices start at 1" );
		else if( lua_tointeger( L, 2 ) < 0 ) 
			return luaL_error( L, "You accessed f[x] with negative x" );
		else return luaL_error( L, "You accessed f[x] at an index beyond the files you supplied" );
		}
	else return 1;
	}
static int lua_f_newindex( lua_State * L )
	{
	return luaL_error( L, "You tried to assign something to the input file array (f), which is PROHIBITED bozo" );
	}

void AltarThread::run()
	{
	auto luaerr = [&]( lua_State * L )
		{
		log( string("[Lua] Error: ") + string( lua_tostring(L, -1) ) );
		};

	if( threadShouldExit() )
		{
		log( "Exiting thread early due to startup error" );
		return;
		}

	//Make sure the script supplied exists
	if( ! File( File::getCurrentWorkingDirectory().getFullPathName() + "/" + script ).exists() )
		{
		log( "Script specified either does not exist or cannot be accessed: " 
			+ (File::getCurrentWorkingDirectory().getFullPathName() + "/" + script).toStdString() );
		return;
		}
	
	//Just in case I screwed up clear the stack
	lua_settop( L, 0 );
	
	//Create global with all the input file paths and metatable to stop bad array access
	lua_createtable( L, inFiles.size(), 0 ); // f table
	//Push the inFiles into the indices of the table
	for( int i = 0; i < inFiles.size(); ++i )
		{
		lua_pushstring( L, ( "\"" + inFiles[i]->getFullPathName() + "\"" ).toRawUTF8() ); // f table | file
		lua_rawseti( L, -2, 1 + i ); // f table
		}
	//Create the metatable, custom index method to make sure the script doesn't access nil files
	lua_createtable( L, 0, 2 );				// f table | f metatable
	lua_pushcfunction( L, lua_f_index );	// f table | f metatable | index func
	lua_setfield( L, -2, "__index" );		// f table | f metatable
	lua_pushcfunction( L, lua_f_newindex );	// f table | f metatable | newindex func
	lua_setfield( L, -2, "__newindex" );	// f table | f metatable
	lua_setmetatable( L, -2 );				// f table
	lua_setglobal( L, "f" );				//
	//Load the supplied script
	if( luaL_loadfile( L, script.getCharPointer() ) ) 
		{
		luaerr( L );
		return;
		}
	log( "[PROCESSING START]" );
	//Make the call
	if( lua_pcall( L, 0, LUA_MULTRET, 0 ) )
		{
		//We can't do this stuff if the failure is due to the user exiting the thread early
		if( ! threadShouldExit() ) 
			{
			luaerr( L );
			log( "[PROCESSING FAILED]" );
			}
		return;
		}
	log( "[PROCESSING END] Time elapsed: " 
		+ Time( Time::getMillisecondCounter() - startTime ).formatted( "%M:%S:" ) + 
		to_string( ( Time::getMillisecondCounter() - startTime ) % 1000 ) );

	//See I told you we would need it.
	int numResults = lua_gettop( L );
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
	vector<File> copiedOutFiles;
	for( auto & i : outFiles )
		{
		copiedOutFiles.push_back( File( workingDir.getParentDirectory().getFullPathName() + "/" + i.getFileName() ) );
		i.copyFileTo( copiedOutFiles.back() );
		}

	const ScopedLock lock( mutex );
	MessageManagerLock mml;
	callback( copiedOutFiles );
	threadFinished = true;
	repaint();
	}
	}

bool AltarThread::cdp( string & command, cdpInfo_t info, vector<string> & outFiles )
	{
	string fullCommand = cdpDir + "/" + command;
	
	//Function for replacing character tokens with generated files of specified type
	vector<string> generatedFileNames;
	auto tokenReplace = [&]( char c, string fileType )
		{
		size_t stringPos = 0;
		while( ( stringPos = fullCommand.find( c, stringPos ) ) != string::npos )
			{ //We have to add _altar to deal with wacko multi out procs
			string path = "\"" + workingDir.getFullPathName().toStdString() + "\\" + to_string( currentUID++ ) + "_altar" + fileType + "\"";
			fullCommand.replace( stringPos, 1, path );
			
			generatedFileNames.emplace_back( path );
			}
		};
	//Check the arguments for any special tokens and replace them with appropriate strings
	tokenReplace( '<', ".wav" );
	tokenReplace( '>', ".txt" );
	tokenReplace( '$', ".mmx" );
	tokenReplace( '|', "" );
	tokenReplace( '%', ".for" );
	tokenReplace( '^', ".env" );
	
	
	//Make the call to the exe requested and display output
	String output;
	{
		//We can't run away to lua until ChildProcess comes off the stack or we'll get memory leak problems ( hence extra braces )
		ChildProcess cdpProcess;
		
		bool startStatus = cdpProcess.start( fullCommand );
		while( cdpProcess.isRunning() )
			{
			//We can't simply block because the gui thread might ask this thread to exit
			Thread::wait( 30 );
			if( threadShouldExit() ) 
				{
				cdpProcess.kill();
				return false; 
				}
			}

		output = cdpProcess.readAllProcessOutput();

		bool endStatus = cdpProcess.getExitCode();
		if( ! startStatus || endStatus != 0 ) //If either startup or processing went wrong, error out
			{
			log( "[CDP] Error running command " + fullCommand + "\n[CDP] " + output  );
			return false;
			}
	}

	//This is handled outside the output lookup because we need access to the output string
	if( info.first == cmdInfo) log( "[CDP] " + fullCommand + " gave info: " + output );
	//Do lookup for outfile names. Most cdp processes output a single given file but some
	//	output multiple with related names. We use this to handle those cases.	
	outFileTypeLookup( outFiles, generatedFileNames, command, info );
	return true;
	}

//This handles all the stupid different ways the CDP outputs files
void AltarThread::outFileTypeLookup( vector<string> & output, const vector<string> genFileNames, 
										const string & command, cdpInfo_t info )
	{
	auto getInputName = [&]()
		{
		int pathEndQuote = command.find_last_of( '\"' );
		int pathStartQuote = command.find_last_of( '\"', pathEndQuote - 1 );
		return command.substr( pathStartQuote, pathEndQuote - pathStartQuote + 1 );
		};

	switch( info.first )
		{
		case normal: { //This is for any process with a set number of outputs
			for( auto & i : genFileNames ) output.emplace_back( i );
			break;
			}

		case outAppend: { //This is for processes appending integers to the supplied file name
			output.emplace_back( genFileNames[0] );
			for( int i = 1; i < info.second; ++i )
				{
				string s = genFileNames[0];
				s.insert( s.size() - 5, to_string( i ) ); //Won't work for binary files
				output.emplace_back( s );
				}
			break;
			}
		case outAppendP3S1:	{
			for( int i = 0; i < info.second; ++i )
				{
				string s = genFileNames[0];
				string index = to_string( i + 1 );
				s.insert( s.size() - 5, string( 3 - index.length(), '0') + index ); //Won't work for binary files
				output.emplace_back( s );
				}
			break;
			}
		case outAppendP3S1Unknown:	{
			//while we are still finding files, keep adding those files
			int i = 1;
			auto nextFileExists = [&]( int i )
				{
				string nonquotes = genFileNames[0].substr( 1, genFileNames[0].size() - 2 );
				string index = to_string( i );
				ifstream nextFile( nonquotes.insert( nonquotes.size() - 4, string( 3 - index.length(), '0') + index ) );
				return nextFile.good();
				};
			while( nextFileExists( i ) )
				{
				string s = genFileNames[0];
				string index = to_string( i );
				output.emplace_back( s.insert( s.size() - 5, string( 3 - index.length(), '0') + index ) );
				++i;
				}
			break;
			}
		case outTrancate: {
			output.emplace_back( genFileNames[0] );
			for( int i = 1; i < info.second; ++i )
				{
				string s = genFileNames[0];
				s.erase( s.size() - 6, 1 );
				s.insert( s.size() - 5, to_string( i ) ); //Won't work for binary files
				output.emplace_back( s );
				}
			break;
			}
		case outUnknownAppend: {
			//while we are still finding files, keep adding those files
			int i = 0;
			auto nextFileExists = [&]( int i )
				{
				string nonquotes = genFileNames[0].substr( 1, genFileNames[0].size() - 2 );
				ifstream nextFile( nonquotes.insert( nonquotes.size() - 4, to_string( i ) ) );
				return nextFile.good();
				};
			while( nextFileExists( i ) )
				{
				string s = genFileNames[0];
				output.emplace_back( s.insert( s.size() - 5, to_string( i ) ) );
				++i;
				}
			break;
			}
		case outUnknownAppend1: {
			//while we are still finding files, keep adding those files
			int i = 1;
			auto nextFileExists = [&]( int i )
				{
				string nonquotes = genFileNames[0].substr( 1, genFileNames[0].size() - 2 );
				ifstream nextFile( nonquotes.insert( nonquotes.size() - 4, to_string( i ) ) );
				return nextFile.good();
				};
			while( nextFileExists( i ) )
				{
				string s = genFileNames[0];
				output.emplace_back( s.insert( s.size() - 5, to_string( i ) ) );
				++i;
				}
			break;
			}
		case outUnknownTruncate: {
			//while we are still finding files, keep adding those files
			output.emplace_back( genFileNames[0] );
			int i = 1;
			auto nextFileExists = [&]( int i )
				{
				string nonquotes = genFileNames[0].substr( 1, genFileNames[0].size() - 2 );
				ifstream nextFile( nonquotes.insert( nonquotes.size() - 4, to_string( i ) ) );
				return nextFile.good();
				};
			while( nextFileExists( i ) )
				{
				string s = genFileNames[0];
				s.erase( s.size() - 6, 1 );
				output.emplace_back( s.insert( s.size() - 5, to_string( i ) ) );
				++i;
				}
			break;
			}

		case inChannel: { //This is for processes appending _cx where x is an integer to the infile
			const string path = getInputName();
			for( int i = 0; i < info.second; ++i )
				{
				string channel = path;
				output.emplace_back( channel.insert( path.size() - 5, "_c" + to_string( i + 1 ) ) );
				}
			break;
			}
		case inChannelSingle: { //This is for processes appending _cx where x is an integer to the infile... Once
			string path = getInputName();
			output.emplace_back( path.insert( path.size() - 5, "_c" + to_string( info.second ) ) );
			break;
			}
		case inTruncate: { //This is for processes appending integers and removing one character from the infile
			const string path = getInputName().erase( 6, 1 ); //erase does the truncation
			for( int i = 0; i < info.second; ++i )
				{
				string s = path;
				output.emplace_back( s.insert( path.size() - 5, to_string( i + 1 ) ) );
				}
			break;
			}

		//Custom ( aren't they all? )
		case synthSpectra: {
			string a = genFileNames[0];
			string b = genFileNames[0];
			a.insert( a.size() - 5, "0" ); 
			b.insert( b.size() - 5, "1" ); 
			output.emplace_back( a );
			output.emplace_back( b );
			break;
			}

		default: log( "You really shouldn't be seeing this error... A specific output type wasn't handled." );
		}
	}
