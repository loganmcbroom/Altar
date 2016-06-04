#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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
