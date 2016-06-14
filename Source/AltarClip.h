#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Defines.h"
#include "AltarButton.h"
#include <algorithm>

class AltarClipList;

class AltarClip : public Button
				, public ChangeListener
				, public Button::Listener
				, public Timer
				, public MouseListener
{
	friend class AltarClipList;
public:
	AltarClip( const File & _file
			 , AudioFormatManager &_formatManager
			 , AudioThumbnailCache &_thumbnailCache
			 , AudioTransportSource &_transportSource
			 , bool isOwner = false
			 , const String & name = String() );

	~AltarClip();

	const File & getFile();
	AudioThumbnail & getThumbnail();

	void playPressed();
	void stopPressed();

	static AltarClip * active;

private:  
	void timerCallback();
	void changeListenerCallback( ChangeBroadcaster* source ) override;
	void paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown) override;
	void buttonClicked( Button *button ) override;
	void resized() override;
	void mouseDrag( const MouseEvent & event ) override;

	AudioTransportSource &transportSource;
	AudioFormatManager &formatManager; 
	
	TemporaryFile audioFile;
	AudioThumbnail thumbnail;
	std::unique_ptr<AudioFormatReaderSource> readerSource;

	AltarButton busButton, saveButton;
	DrawableRectangle currentPosition;

	static Colour backgroundColour;
}; 