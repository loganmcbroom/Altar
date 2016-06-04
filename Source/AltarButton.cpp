#include "AltarButton.h"

Font * AltarButton::wingdings = nullptr;
Font * AltarButton::webdings  = nullptr;

AltarButton::AltarButton( const String & _text, const Font * _font, size_t _fontHeight )
	: Button( _text )
	, font(_font)
	{
	setButtonText(_text);
	if( _fontHeight != 0 )
		{
		fontHeight = _fontHeight;
		}
	else
		fontHeight = font->getHeight();
	}


void AltarButton::paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown)
	{
	g.fillAll( isEnabled()? 
		( isMouseOverButton ? PALETTE_2 : PALETTE_1 ) : 
		Colour::fromHSV( 0, 0, .5, 1 ) );

	if( font == nullptr ) return;
	Font &f = Font( *font );
	f.setHeight( fontHeight );
	if( isButtonDown ) f.setHeight( f.getHeight() * 0.9 );
	g.setFont( f );

	g.setColour( TEXT_COLOUR );
	g.drawText( getButtonText(),
		Rectangle<int>( 0, 0, getWidth(), getHeight()), Justification::centred );

	if( isEnabled() ) setMouseCursor( MouseCursor::PointingHandCursor );
}

void AltarButton::setFont( Font *f )
	{
	font = f;
	}