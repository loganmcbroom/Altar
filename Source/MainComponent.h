//Add spectral support
//make c functions for modules
//Launch AltarProcess as another thread

//Parallel processing
//okay we could have a cdpPar type of function that just starts the process and returns without waiting
//We could return an index into a list of running processes kept like generatedFiles
//Have a function that takes an index and waits for that program to finish
//and a function that waits for everything to finish
//sounds doable

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AltarButton.h"
#include "AltarClipList.h"
#include "AltarProcess.h"
#include "AltarLogger.h"
#include "Defines.h"

class MainContentComponent  : public AudioAppComponent
							, public ChangeListener
							, public Button::Listener
							, public FileDragAndDropTarget
{
public:
    MainContentComponent();
    ~MainContentComponent();

    void prepareToPlay( int samplesPerBlockExpected, double sampleRate ) override;
    void getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) override;
    void releaseResources() override;

    //==============================================================================
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
	bool thinking = false;
	
	AudioFormatManager formatManager;
	AudioTransportSource transportSource;

	AltarClipList inClips, outClips;

	AltarLogger log;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( MainContentComponent )
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
