#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Defines.h"

class AltarButton : public Button
{
public:
	AltarButton( const String & _text = "", const Font * _font = nullptr, size_t _fontHeight = 0 );

	void paintButton( Graphics &g, bool isMouseOverButton, bool isButtonDown) override;

	void setFont( Font *f );

	const Font * font;
	size_t fontHeight;

	static Font * wingdings;
	static Font * webdings;
};

