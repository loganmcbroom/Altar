#include "AltarClipList.h"

#include <algorithm>
#include <cassert>

#define MAX_CLIPS 128

using namespace std;

//Constructor
AltarClipList::AltarClipList( AudioFormatManager &_formatManager, AudioTransportSource &_transportSource )
	: transportSource( _transportSource )
	, formatManager( _formatManager )
	, thumbnailCache( MAX_CLIPS )
	{
	}

//Destructor
AltarClipList::~AltarClipList()
	{
	for( int i = 0; i < getNumItems(); ++i )
		{
		getItem( i ).getThumbnail().setSource( nullptr );
		}
	}

//Just how big is each clip?
size_t AltarClipList::getItemHeight()
	{
	return 50;
	}

//Erase given item from the list
void AltarClipList::erase( AltarClip * item )
	{
	AltarClipList::erase( getIndex( item ) );
	}

//Erase the item at the given index from the list
void AltarClipList::erase( unsigned int index )
	{	
	thumbnailCache.removeThumb( getItem( index).getThumbnail().getHashCode() );
	AltarList<AltarClip>::erase( index );
	}

//Erase all items
void AltarClipList::clear()
	{
	AltarList<AltarClip>::clear();
	thumbnailCache.clear();
	}

//
void AltarClipList::addClipFromFile( File &file, bool isOwner )
	{
	for( int i = 0; i < getNumItems(); ++i )
		{
		if( getItem( i ).audioFile.getTargetFile() == file )
			{
			Logger::writeToLog( "File is already on list" );
			return;
			}
		}
	addItem( new AltarClip( file, formatManager, thumbnailCache, transportSource, isOwner ) );
	}


