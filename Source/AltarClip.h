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
{
	friend class AltarClipList;
public:
	AltarClip( File &_file
			 , AudioFormatManager &_formatManager
			 , AudioThumbnailCache &_thumbnailCache
			 , AudioTransportSource &_transportSource
			 , bool isOwner = false );

	~AltarClip();

	const File & getFile();
	AudioThumbnail & getThumbnail();

	void playPressed();
	void stopPressed();

	static AltarClip * active;

private:  

	AudioTransportSource &transportSource;
	AudioFormatManager &formatManager; 
	
	TemporaryFile audioFile;
	AudioThumbnail thumbnail;
	std::unique_ptr<AudioFormatReaderSource> readerSource;

	AltarButton busButton, saveButton;
	DrawableRectangle currentPosition;

	static Colour backgroundColour;
	
	void timerCallback();
	void changeListenerCallback( ChangeBroadcaster* source ) override;
	void paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown) override;
	void buttonClicked( Button *button ) override;
	void resized() override;
}; 