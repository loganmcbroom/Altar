#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AltarLogger.h"
#include "lua_cdp_functions/lua_cdp_utilities.h"

struct lua_State;

class AltarThread : public Thread
				  , public Component
	{
public:
	AltarThread( const String & name, const String & _script, 
				std::function< void( std::vector< File > & ) > & _callback,
				const std::vector< String > & files = std::vector< String >() );
	~AltarThread();

	const File & getFile( int index );
	size_t getNumFiles();

	bool cdp( std::string & command, cdpInfo_t info, std::vector<std::string> &outFiles );

///private:
	void log( const String & s );
	void addFile( const File & f );

	void paint( Graphics & g ) override;
	void run() override;
	void outFileTypeLookup( std::vector<std::string> & output, const std::vector<std::string> genFiles, 
							const std::string & command, cdpInfo_t info );

	std::function< void( std::vector< File > & ) > callback;
	std::vector< std::unique_ptr<File> > inFiles;
	const String script;
	lua_State * L;
	int64 startTime;
	int currentUID = 0;
	std::string cdpDir;
	File workingDir;
	bool threadFinished = false;

	static CriticalSection mutex;
	};