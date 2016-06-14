#include "AltarThreadList.h"

#include "AltarLogger.h"

AltarThreadList::AltarThreadList()
	{
	}

AltarThreadList::~AltarThreadList()
	{
	}

void AltarThreadList::addThread( const String & script, std::function< void( std::vector< File > & ) > & callback, const std::vector<String> & files )
	{
	addItem( new AltarThread( File( File::getCurrentWorkingDirectory().getFullPathName() + "/" + script ).getFileName() 
			+ Time::getCurrentTime().formatted( " %H:%M:%S" ), 
			script, 
			callback, 
			files ) );
	}

