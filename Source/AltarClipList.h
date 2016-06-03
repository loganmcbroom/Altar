#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AltarClip.h"

#include <algorithm>
#include <cassert>

#define MAX_CLIPS 128
#define CLEAR_HEIGHT 25

class AltarLookAndFeel : public LookAndFeel_V3
	{
public:
	AltarLookAndFeel()
		{
		}
 
	void drawScrollbar (Graphics &g, ScrollBar &scrollbar, 
						int x, int y, int width, int height, 
						bool isScrollbarVertical, int thumbStartPosition, 
						int thumbSize, bool isMouseOver, bool isMouseDown) override
		{
		g.setColour( Colour::fromHSV( 0, 0, .27, 1 ) );
		g.fillRoundedRectangle( x + 2, thumbStartPosition, width - 4, thumbSize, 3 );
		}

	};



class AltarClipList : public Component
					, public ScrollBar::Listener
					, public Button::Listener
	{
public:
	AltarClipList( const String &name
				 , AudioFormatManager &_formatManager
			     , AudioTransportSource &_transportSource )
		: Component( name )
		, transportSource( _transportSource )
		, formatManager( _formatManager )
		, thumbnailCache( MAX_CLIPS )
		, scroll( true )
		, clearButton( "r", nullptr )
		{
		altarlnf.setColour( 0, Colours::white );

		addAndMakeVisible( &scroll );
		scroll.setLookAndFeel( &altarlnf );
		scroll.addListener( this );
		scroll.setRangeLimits( 0, 1, NotificationType::dontSendNotification );
		scroll.setCurrentRange( 0, 1, NotificationType::dontSendNotification );

		addAndMakeVisible( &clearButton );
		clearButton.addListener( this );
		}	

	~AltarClipList()
		{
		transportSource.setSource( nullptr );
		}

	void scrollBarMoved( ScrollBar *scrollBarThatHasMoved, double newRangeStart ) override
		{
		resetClips( true );
		}

	void buttonClicked( Button *b ) override
		{
		if( b == &clearButton )
			{
			clear();
			}
		else
			{
			AltarClip *clip = static_cast< AltarClip *>( b->getParentComponent() );
			if( AltarClip::active == clip ) clip->stopPressed();
			erase( clip );
			}
		}

	void resetClips( bool scrollVisible )
		{
		for( int i = 0; i < clips.size(); ++i )
			{
			juce::Rectangle<int> rect( 0, i * getClipHeight() - scroll.getCurrentRangeStart() + CLEAR_HEIGHT, 
								getWidth() - (scrollVisible? 8 : 0), getClipHeight() );
			clips[i]->setBounds( rect.reduced( 2 ) );
			}
		}


	size_t getClipHeight()
		{
		return 50;
		}

	void mouseWheelMove(const MouseEvent & event, const MouseWheelDetails & wheel ) override
		{
		scroll.setCurrentRangeStart( scroll.getCurrentRangeStart() - wheel.deltaY * getClipHeight() * 4 );
		}


	void paint( Graphics &g )
		{
		g.fillAll( Colour::fromHSV( 0, 0, .18, 1 ) );
		}

	void resized()
		{ 
		bool scrollVisible = float( getClipHeight() ) * float( clips.size() ) > getHeight();
		scroll.setCurrentRange( scroll.getCurrentRangeStart(), getHeight(), NotificationType::dontSendNotification );

		resetClips( scrollVisible );

		scroll.setBounds( getWidth() - 8, CLEAR_HEIGHT, 8, getHeight() );

		clearButton.setBounds( juce::Rectangle<int>( 0, 0, getWidth(), CLEAR_HEIGHT ) );
		}

	void addClipFromFile( File &file, bool isOwner = false )
		{
		for( auto &&i : clips )
			{
			if( i->audioFile.getTargetFile() == file )
				{
				Logger::writeToLog( "File is already on list" );
				return;
				}
			}

		clips.emplace_back( new AltarClip( file, formatManager, thumbnailCache, transportSource, isOwner ) );
		addAndMakeVisible( clips.back().get() );
		clips.back()->eraseButton.addListener( this );
		scroll.setRangeLimits( 0, float( getClipHeight() ) * float( clips.size() ) + CLEAR_HEIGHT, NotificationType::dontSendNotification );
		resized();
		clearButton.toFront( false );
		}

	int getIndex( AltarClip *clip )
		{
		for( int i = 0; i < clips.size(); ++i )
			{
			if( clips[i].get() == clip )
				{
				return i;
				}
			}
		return -1;
		}

	void erase( AltarClip *child )
		{
		int i = getIndex( child );
		if( i == -1 ) Logger::writeToLog( "Couldn't find clip in cliplist" );
		else erase( i );
		}

	void erase( unsigned int pos )
		{	
		auto *clip = clips[pos].get();
		thumbnailCache.removeThumb( clip->getThumbnail().getHashCode() );
		clips.erase( clips.begin() + pos ); //removes
		scroll.setRangeLimits( 0, float( getClipHeight() ) * float( clips.size() ), NotificationType::dontSendNotification );
		resized();
		}

	void clear()
		{
		clips.clear();
		thumbnailCache.clear();
		}

	AltarClip &getClip( unsigned int pos )
		{
		return *clips[ pos ];
		}

	AudioTransportSource &transportSource;
	AudioFormatManager &formatManager;

	AudioThumbnailCache thumbnailCache;
	std::vector< std::unique_ptr< AltarClip > > clips;
	ScrollBar scroll;
	AltarButton clearButton;
	AltarLookAndFeel altarlnf;
	};


