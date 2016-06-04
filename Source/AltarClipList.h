#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AltarList.h"
#include "AltarClip.h"


class AltarClipList : public AltarList< AltarClip >
	{
public:
	AltarClipList( AudioFormatManager &_formatManager, AudioTransportSource &_transportSource );
	~AltarClipList();

	size_t getItemHeight() override;
	void erase( AltarClip * child );
	void erase( unsigned int pos );
	void clear();

	void addClipFromFile( File & file, bool isOwner = false );
	
private:
	AudioTransportSource &transportSource;
	AudioFormatManager &formatManager;
	AudioThumbnailCache thumbnailCache;
	};


