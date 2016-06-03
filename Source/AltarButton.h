#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Defines.h"

class AltarButton : public Button
{
public:
	AltarButton( const String & _text = "", const Font * _font = nullptr );

	void paintButton( Graphics &g, bool isMouseOverButton, bool isButtonDown) override;

	void setFont( Font *f );

	const Font * font;

	static Font * wingdings;
	static Font * webdings;
};

/*class AltarBusButton : public AltarButton
	{
public:
	AltarButton( AudioTransportSource &_ts )
		: AltarButton( "n", "n", AltarButton::wingdings )
		, transportSource( _ts )
		{
		}

	void clicked() override
		{
		if( transportSource.isPlaying() )
			{
			transportSource.stop();
			transportSource.setPosition( 0.0 );

			setButtonText( "4" );
			hoverText = "4";
			font = AltarButton::webdings;
			}
		else
			{ //start it
			transportSource.setSource( readerSource, 0, nullptr, readerSource->getAudioFormatReader()->sampleRate );
			transportSource.start();

			setButtonText( "n" );
			hoverText = "n";
			busButton.font = AltarButton::wingdings;
			}
		}

private:
	AudioTransportSource &transportSource;
	};*/

