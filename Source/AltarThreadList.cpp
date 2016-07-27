#include "AltarThreadList.h"

#include <string>

#include "AltarLogger.h"

AltarThreadList::AltarThreadList()
	{
	}

AltarThreadList::~AltarThreadList()
	{
	}

void AltarThreadList::addThread( const String & script, std::function< void( std::vector< File > & ) > & callback, const std::vector<String> & files )
	{
	addItem( new AltarThread( File( File::getCurrentWorkingDirectory().getFullPathName() + "/" + script ).getFileNameWithoutExtension() 
			+ std::to_string( Time::currentTimeMillis() ), 
			script, 
			callback, 
			files ) );
	}

