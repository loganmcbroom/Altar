#pragma once

#include "AltarList.h"
#include "AltarThread.h"

class AltarThreadList : public AltarList< AltarThread >
	{
public:
	AltarThreadList();
	~AltarThreadList();

	int getItemHeight() override { return 50; }

	void addThread( const String & script, 
					std::function< void( std::vector< File > & ) > & callback,
					const std::vector< String > & files );

private:
	};