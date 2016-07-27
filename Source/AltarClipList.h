#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AltarList.h"
#include "AltarClip.h"


class AltarClipList : public AltarList< AltarClip >
					, public DragAndDropTarget
	{
public:
	AltarClipList( AudioFormatManager &_formatManager, AudioTransportSource &_transportSource );
	~AltarClipList();

	int getItemHeight() override;
	void erase( AltarClip * child );
	void erase( unsigned int pos );
	void clear();

	void addClipFromFile( const File & file, bool isOwner = false );
	void insertClipFromFile( const File & file, size_t index, const String & name = String(), bool isOwner = false );

private:
	bool isInterestedInDragSource( const SourceDetails & dragSourceDetails ) override;
	///void itemDragEnter	( const SourceDetails &dragSourceDetails ) override;
	///void itemDragMove	( const SourceDetails &dragSourceDetails ) override;
	///void itemDragExit	( const SourceDetails &dragSourceDetails ) override;
	void itemDropped	( const SourceDetails &dragSourceDetails ) override;
	///bool shouldDrawDragImageWhenOver() override;


	AudioTransportSource &transportSource;
	AudioFormatManager &formatManager;
	AudioThumbnailCache thumbnailCache;
	};


