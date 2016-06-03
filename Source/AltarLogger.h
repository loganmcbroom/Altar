#pragma once 

#include "../JuceLibraryCode/JuceHeader.h"

class AltarLogger : public Logger
				  , public TextEditor
{
public:
	AltarLogger();
	~AltarLogger();
	void logMessage( const String &message ) override;
	void paint( Graphics &g ) override;
};