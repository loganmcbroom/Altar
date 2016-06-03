/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Defines.h"

Component* createMainContentComponent();

//==============================================================================
class AltarApplication  : public JUCEApplication
{
public:
    //==============================================================================
    AltarApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  
			: DocumentWindow (name, Colours::lightgrey, DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (createMainContentComponent(), true);
            setResizable (true, true);
			setResizeLimits( 700, 500, INT_MAX, INT_MAX );
			

            centreWithSize (getWidth(), getHeight());
            setVisible (true);

			//setIcon(  );
        }

		bool keyPressed( const KeyPress &key ) override
			{

			if( key == KeyPress::F11Key )
				{
				Desktop &d = Desktop::getInstance();
				if( d.getKioskModeComponent() == nullptr )
					d.setKioskModeComponent( this, true );
				else
					d.setKioskModeComponent( nullptr, true );
				return true;
				}

			return false;
			}	

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (AltarApplication)
