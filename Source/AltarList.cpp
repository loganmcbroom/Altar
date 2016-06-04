#include "AltarList.h"

#define CLEAR_HEIGHT 25
#define ERASE_WIDTH 25

//Constructor
template <typename T>
AltarList<T>::AltarList()
	: scroll( true )
	, fontWebDings( "WebDings", FONT_SIZE, Font::bold  )
	, clearButton( "r", &fontWebDings, CLEAR_HEIGHT * .67 )
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

//Destructor
template <class T>
AltarList<T>::~AltarList()
	{
	}

//
template<typename T>
void AltarList<T>::addItem( T * item )
	{
	items.emplace_back( item, new AltarButton( "r", &fontWebDings, ERASE_WIDTH / 2.0 ) );
	addAndMakeVisible( items.back().first.get() );
	addAndMakeVisible( items.back().second.get() );
	items.back().second->addListener( this );

	scroll.setRangeLimits( 0, float( getItemHeight() ) * float( items.size() ) + CLEAR_HEIGHT, NotificationType::dontSendNotification );
	resized();

	clearButton.toFront( false );
	}

//
template<typename T>
int AltarList<T>::getIndex( T * clip )
	{
	for( int i = 0; i < getNumItems(); ++i )
		{
		if( items[i].first.get() == clip )
			{
			return i;
			}
		}
	return -1;
	}

//
template<typename T>
void AltarList<T>::erase( int index )
	{
	items.erase( items.begin() + index );
	scroll.setRangeLimits( 0, float( getItemHeight() ) * float( items.size() ) + CLEAR_HEIGHT, NotificationType::dontSendNotification );
	resized();
	}

//
template<typename T>
void AltarList<T>::erase( T * item )
	{
	erase( getIndex( item ) );
	}

//
template<typename T>
void AltarList<T>::clear()
	{
	items.clear();
	}

//
template<typename T>
T & AltarList<T>::getItem( int index )
	{
	return * items[index].first; 
	}


// Private ======================================================================

// Paint
template <class T>
void AltarList<T>::paint( Graphics &g )
	{
	g.fillAll( Colour::fromHSV( 0, 0, .18, 1 ) );
	}

// Resized
template <class T>
void AltarList<T>::resized()
	{ 
	bool scrollVisible = float( getItemHeight() ) * float( getNumItems() ) > getHeight();
	scroll.setCurrentRange( scroll.getCurrentRangeStart(), getHeight(), NotificationType::dontSendNotification );

	positionItems( scrollVisible );

	scroll.setBounds( getWidth() - 8, CLEAR_HEIGHT, 8, getHeight() );

	clearButton.setBounds( juce::Rectangle<int>( 0, 0, getWidth(), CLEAR_HEIGHT ) );
	}

// Repositions all the items based on relevant info
template <class T>
void AltarList<T>::positionItems( bool scrollVisible )
	{
	for( int i = 0; i < items.size(); ++i )
		{
		juce::Rectangle<int> rect( 0, i * getItemHeight() - scroll.getCurrentRangeStart() + CLEAR_HEIGHT, 
							getWidth() - (scrollVisible? 8 : 0), getItemHeight() );
		items[i].first-> setBounds( rect.withLeft ( ERASE_WIDTH ).reduced( 2 ) );
		items[i].second->setBounds( rect.withRight( ERASE_WIDTH ).reduced( 2 ) );
		}
	}

// Callback for the scroll object having changed
template<typename T>
void AltarList<T>::scrollBarMoved( ScrollBar * scrollBarThatHasMoved, double newRangeStart )
	{
	positionItems( true );
	}

// Callback for scrolling with mouse
template<typename T>
void AltarList<T>::mouseWheelMove( const MouseEvent & event, const MouseWheelDetails & wheel )
	{
	scroll.setCurrentRangeStart( scroll.getCurrentRangeStart() - wheel.deltaY * getItemHeight() * 4 );
	}

//
template<typename T>
void AltarList<T>::buttonClicked( Button * b )
	{
	if( b == &clearButton )
		{
		clear();
		}
	else //One of the erase buttons was pressed
		{
		for( int i = 0; i < getNumItems(); ++i )
			{
			if( items[i].second.get() == b )
				{
				erase( i );
				return;
				}
			}
		}
	}

//Instantiate templates
#include "AltarClip.h"
template class AltarList< AltarClip >;
