#include "AltarThread.h"

#include <vector>
#include <sstream>
#include <fstream>

#include "lua.hpp"
#include "lua_cdp_functions/lua_cdp_functions.h"
#include "defines.h"

using namespace std;

//Custom lua junk
static int lua_string_index( lua_State * L )
	{											// string | index
	int index = lua_tointeger( L, 2 );
	lua_pop( L, 1 );
	lua_pushpairs( L, { {"housekeep", 1}, {"chans 1", 2}, {to_string(index).c_str(), 4} } );
	return cdp( L, { inChannel, index } );
	}
static int lua_f_index( lua_State * L )
	{											// f table | index
	lua_rawgeti( L, 1, lua_tointeger( L, 2 ) ); // f table | index | file string
	if( lua_isnil( L, 3 ) ) 
		{
		AltarThread * T = static_cast<AltarThread *>( Thread::getCurrentThread() );
		if( lua_tointeger( L, 2 ) == 0 ) 
			T->log( "You accessed f[0], in lua indices start at 1" );
		else if( lua_tointeger( L, 2 ) < 0 ) 
			T->log( "You accessed f[x] with negative x" );
		else T->log( string("You accessed f[x] at index " )
					+ lua_tostring( L, 2 ) + " which is beyond the number of supplied files" );
		//lua_settop( L, 0 );
		//lua_pushnil( L );
		return 0;
		}
	return 1;
	}
static int lua_f_newindex( lua_State * L )
	{
	return luaL_error( L, "You tried to assign something to the input file array (f), which is PROHIBITED bozo" );
	}
static int lua_print( lua_State * L ) 
	{
    int nargs = lua_gettop( L );
	AltarThread * T = static_cast<AltarThread *>( Thread::getCurrentThread() );
    for( int i=1; i <= nargs; ++i ) 
		{
        if( lua_isstring( L, i ) )	T->log( lua_tostring( L, i ) );
        else						T->log( "You tried to print a non-string in lua");
		}
    return 0;
	}
static const struct luaL_Reg printlib [] = //I don't understand why we need this but it works
	{
	{"print", lua_print},
	{NULL, NULL} /* end of array */
	};

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

	//redefine Lua's print function to our logging function
	lua_getglobal( L, "_G" );
	luaL_register( L, NULL, printlib );
	lua_pop( L, 1 );

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

std::string AltarThread::getFreeFilename( const std::string & extension )
	{
	return "\"" + workingDir.getFullPathName().toStdString() 
				+ "\\" + to_string( currentUID++ ) + "_altar" + extension + "\"";
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
	g.drawText( getThreadName().substring( 5 ), getLocalBounds(), Justification::centred );
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
#ifdef RELEASE
	if( ! File( File::getCurrentWorkingDirectory().getFullPathName() + "/" + script ).exists() )
		{
		log( "Script specified either does not exist or cannot be accessed: " 
			+ (File::getCurrentWorkingDirectory().getFullPathName() + "/" + script).toStdString() );
		return;
		}
#endif
	
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

	//Adding __index to the string metatable for retrieving a channel
	//lua_get

	//Load the supplied script
#ifdef DEBUG
	if( luaL_loadfile( L, "C:\\Users\\Logan\\Desktop\\Altar\\Altar.lua" ) )
#else
	if( luaL_loadfile( L, script.getCharPointer() ) )
#endif 
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
			log( "[PROCESSING FAILED] Time elapsed: " 
				+ Time( Time::getMillisecondCounter() - startTime ).formatted( "%M:%S:" ) + 
				to_string( ( Time::getMillisecondCounter() - startTime ) % 1000 ) );
			const ScopedLock lock( mutex );
			MessageManagerLock mml;
			threadFinished = true;
			repaint();
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
	
	for( int i = 1; i <= numResults; ++i )
		{
		if( ! lua_isstring( L, i ) )
			{
			log( "Discarding non string output" );
			continue;
			}
		string s = lua_tostring( L, i );
		struct stat buffer;
		if( stat( s.substr( 1, s.size() - 2 ).c_str(), &buffer ) != 0 ) //If the file doesn't exist
			{
			log( "Discarding nonexistent output " + s );
			continue;
			}

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
void AltarThread::setUpProcess( string & command, cdpInfo_t info )
	{
	processList.emplace_back( cdpDir + "/" + command, info );
	}
vector<string> AltarThread::process()
	{
	struct Child 
		{
		ChildProcess process;
		bool startStatus;
		string output;
		vector<string> generatedFileNames;
		};
	{
	vector<Child> children( processList.size() );

	for( int i = 0; i < processList.size(); ++i )
		{
		//improved tokenreplace, generates file names for placeholder character ('$')
		size_t stringPos = 0;
		while( ( stringPos = processList[i].first.find( '$', stringPos ) ) != string::npos )
			{ //We have to add _altar to deal with wacko multi out procs
			size_t extensionSize = processList[i].first.find( ' ', stringPos ) - ( stringPos + 1 );
			string extension = processList[i].first.substr( stringPos + 1, extensionSize );
			string path = getFreeFilename( extension );
			children[i].generatedFileNames.emplace_back( path );
			processList[i].first.replace( stringPos, 1 + extensionSize, path );
			}
		}
	
	//Start running each process
	for( int i = 0; i < processList.size(); ++i )
		{
		children[i].startStatus = children[i].process.start( processList[i].first );
		}
	//Wait for everything to finish and escape if needed
	for( int i = 0; i < processList.size(); ++i )
		{
		while( children[i].process.isRunning() )
			{
			//We can't simply block because the gui thread might ask this thread to exit
			Thread::wait( 30 );
			if( threadShouldExit() ) 
				{
				for( auto &i : children )
					i.process.kill();
				goto killSwitch; //Using goto to force ChildProcess off the stack, avoids memory leak
				}
			}
		}
	vector<string> output;
	for( int i = 0; i < children.size(); ++i ) 
		{
		children[i].output = children[i].process.readAllProcessOutput().toStdString();
		if( ! children[i].startStatus || children[i].process.getExitCode() != 0 ) //If either startup or processing went wrong, error out
			{
			log( "[CDP] Error running command " + get<0>(processList[i]) + "\n[CDP] " + children[i].output );
			}
		else
			{
			//This is handled outside the output lookup because we need access to the output string
			if( get<1>( processList[i] ).first == cmdInfo ) 
				log( "[CDP] " + get<0>( processList[i] ) + " gave info: " + children[i].output );
			//Do lookup for outfile names. Most cdp processes output a single given file but some
			//	output multiple with related names. We use this to handle those cases.	
			else outFileTypeLookup( output, children[i].generatedFileNames, processList[i].first, processList[i].second );
			}
		}
	return output;
	}
	killSwitch: luaL_error( L, "Escaping processes for thread close" );
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
		case cmdInfo: { break; } //This is handled in cdp

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
		case sfeditCutmany:
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
		case repitchGetpitch: {
			output.emplace_back( genFileNames[1] );
			break;
			}
		case housekeepCopy: {
			for( int i = 0; i < info.second; ++i )
				{
				string s = genFileNames[0];
				string index = to_string( i + 1 );
				s.insert( s.size() - 5, "_" + string( 3 - index.length(), '0') + index ); //Won't work for binary files
				output.emplace_back( s );
				}
			break;
			}
		case modifyShudder: {
			string s = genFileNames[0];
			output.emplace_back( s.replace( s.size() - 6, 1, "0" ) );
			break;
			}
		case specNuSpecgrids: {
			for( int i = 0; i < info.second; ++i )
				{
				string s = genFileNames[0];
				s.insert( s.size() - 5, to_string( i ) ); //Won't work for binary files
				output.emplace_back( s );
				}
			break;
			}

		default: log( "You really shouldn't be seeing this error... A specific output type wasn't handled." );
		}
	}
