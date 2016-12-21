#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AltarButton.h"
#include "AltarClipList.h"
#include "AltarThreadList.h"
#include "AltarLogger.h"
#include "Defines.h"

class MainContentComponent  : public AudioAppComponent
							, public ChangeListener
							, public Button::Listener
							, public FileDragAndDropTarget
							, public DragAndDropContainer
{
public:
    MainContentComponent();
    ~MainContentComponent();

    void prepareToPlay( int samplesPerBlockExpected, double sampleRate ) override;
    void getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) override;
    void releaseResources() override;
    void paint (Graphics& g) override;
    void resized() override;
	void changeListenerCallback( ChangeBroadcaster* source ) override;
	void buttonClicked( Button* button ) override;

private:

	void importFile( File file );
	void openButtonClicked();
	void procButtonClicked();

	void filesDropped( const StringArray & files, int x, int y ) override;
	bool isInterestedInFileDrag(const StringArray &files)		{ return true; }
	void fileDragEnter(const StringArray &files, int x, int y)	{ openButton.setButtonText( "1" ); }
	void fileDragExit(const StringArray &files)					{ openButton.setButtonText( "0" ); }

	Font fontWingdings;
	Font fontWebdings;
	Font fontSymbol;
	Font fontRoboto;
	AltarButton openButton;
	AltarButton procButton;
	TextEditor command;
	
	AudioFormatManager formatManager;
	AudioTransportSource transportSource;

	AltarClipList inClips, outClips;
	AltarThreadList threads;

	AltarLogger log;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( MainContentComponent )
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
