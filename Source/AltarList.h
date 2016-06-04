#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "AltarButton.h"
#include "AltarLNF.h"

template < typename T >
class AltarList  : public Component
				 , public ScrollBar::Listener
				 , public Button::Listener
	{
public:
	AltarList();
	~AltarList();

	virtual size_t getItemHeight() = 0;
	
	size_t getNumItems() { return items.size(); };
	void addItem( T * item );
	int getIndex( T * item );
	void erase( int index );
	void erase( T * item );
	void clear();
	T & getItem( int index );

protected:

private:
	void paint( Graphics &g ) override;
	void resized() override;
	void positionItems( bool scrollVisible );
	void scrollBarMoved( ScrollBar * scrollBarThatHasMoved, double newRangeStart ) override;
	void mouseWheelMove(const MouseEvent & event, const MouseWheelDetails & wheel ) override;
	void buttonClicked( Button * b ) override;
	
	std::vector< std::pair< std::unique_ptr<T>, std::unique_ptr<AltarButton> > > items;

	ScrollBar scroll;
	AltarLookAndFeel altarlnf;

	//This is here for giving clearButton a sick X
	Font fontWebDings;
	AltarButton clearButton;
	};