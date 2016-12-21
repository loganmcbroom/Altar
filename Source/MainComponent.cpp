#include "MainComponent.h"

#include <fstream>

//Constructor
MainContentComponent::MainContentComponent()
	: fontWingdings	( "Wingdings", FONT_SIZE, Font::bold  )
	, fontWebdings	( "Webdings" , FONT_SIZE, Font::bold  )
	, fontSymbol	( "Symbol"	 , FONT_SIZE, Font::plain )
	, fontRoboto	( "Roboto"   , 18,		  Font::plain )
	, openButton( "0", &fontWingdings )
	, procButton( "P", &fontSymbol )
	, command( "command" )
	, formatManager()
	, inClips( formatManager, transportSource )
	, outClips( formatManager, transportSource )
	{
	AltarButton::wingdings = &fontWingdings;
	AltarButton::webdings = &fontWebdings;

	addAndMakeVisible( log );
	Logger::setCurrentLogger( &log );

	addAndMakeVisible( &openButton );
	addAndMakeVisible( &procButton );
	addAndMakeVisible( &inClips    );
	addAndMakeVisible( &threads	   );
	addAndMakeVisible( &outClips   );
	addAndMakeVisible( &command    );

	openButton.addListener( this );
	procButton.addListener( this );

	command.setMultiLine( true, false );
	command.setReturnKeyStartsNewLine( true );
	command.setFont( fontRoboto );
	command.setText( "Altar.lua" );

	setSize( 1000, 700 );

	formatManager.registerBasicFormats();

	setAudioChannels(0, 2);

	if( ! File::getCurrentWorkingDirectory().getChildFile( "Settings.lua" ).exists() )
		{
		FileChooser chooser( "Select your _cdprogs directory (it should be in cdprX/_cdp)" );
		if( ! chooser.browseForDirectory() 
		 || ! chooser.getResult().exists()
		 || ! chooser.getResult().getChildFile( "modify.exe" ).exists() )
			Logger::writeToLog( "Things won't work until you pick the correct _cdprogs directory" );
		else
			{
			std::ofstream settingsFile( "Settings.lua" ); 
			settingsFile << "cdpDir = \"" << chooser.getResult().getFullPathName().replace( "\\", "/" ) << "\"";
			}
		}
	}

//Destructor
MainContentComponent::~MainContentComponent()
	{
    shutdownAudio();
	Logger::setCurrentLogger( nullptr );
	}


//Called when the audio device is started or when its settings are changed
void MainContentComponent::prepareToPlay( int samplesPerBlockExpected, double sampleRate )
	{
	transportSource.prepareToPlay( samplesPerBlockExpected, sampleRate );
	}

//This function is handed an audio buffer to fill as is needed for output
void MainContentComponent::getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill )
	{
	if( AltarClip::active == nullptr )
		{
		bufferToFill.clearActiveBufferRegion();
		return;
		}

	transportSource.getNextAudioBlock(bufferToFill);
	}

//Called when the audio device stops or when it is restarted
void MainContentComponent::releaseResources()
	{
	transportSource.releaseResources();
	}

#define LOG_HEIGHT  ( UNIT * 5 + MARGIN * 4 )

//Paint
void MainContentComponent::paint( Graphics& g )
	{
    g.fillAll (BACKGROUND_COLOUR);

	g.setColour( Colours::white );
	g.drawLine( getWidth() / 3, UNIT + MARGIN * 2,
				getWidth() / 3, getHeight() - MARGIN - ( LOG_HEIGHT + MARGIN ), 2 );		
	g.drawLine( getWidth() * 2 / 3, UNIT + MARGIN * 2,
				getWidth() * 2 / 3, getHeight() - MARGIN - ( LOG_HEIGHT + MARGIN ), 2 );		

	}

//Resized
void MainContentComponent::resized()
	{
	openButton.setBounds(MARGIN,			MARGIN,	UNIT, UNIT);
	procButton.setBounds(MARGIN * 2 + UNIT, MARGIN, UNIT, UNIT);

	

	inClips.setBounds( 
		MARGIN, 
		MARGIN * 2 + UNIT, 
		getWidth() / 3 - 2 * MARGIN, 
		getHeight() - ( UNIT + MARGIN * 3 ) - ( LOG_HEIGHT + MARGIN ) );
	threads.setBounds( 
		getWidth() / 3 + MARGIN, 
		MARGIN * 2 + UNIT, 
		getWidth() / 3 - 2 * MARGIN, 
		getHeight() - ( UNIT + MARGIN * 3 ) - ( LOG_HEIGHT + MARGIN ) );
	outClips.setBounds( 
		( getWidth() / 3 ) * 2 + MARGIN, 
		MARGIN * 2 + UNIT, 
		getWidth() / 3 - 2 * MARGIN, 
		getHeight() - ( UNIT + MARGIN * 3 ) - ( LOG_HEIGHT + MARGIN ) );


	command.setBounds( MARGIN * 3 + UNIT * 2, MARGIN, getWidth() - ( MARGIN * 4 + UNIT * 2 ), UNIT );

	Rectangle<int> errorRect( 
		MARGIN, getHeight() - ( LOG_HEIGHT + MARGIN ), 
		getWidth() - MARGIN * 2, LOG_HEIGHT );

	log.setBounds( errorRect );
	}

///What is this for?
void MainContentComponent::changeListenerCallback( ChangeBroadcaster* source )
	{
	}

//Called when a button is pressed and delegates functionality to specific functions
void MainContentComponent::buttonClicked( Button* button )
	{
		 if( button == &openButton	) { openButtonClicked(); }
	else if( button == &procButton	) { procButtonClicked(); }
	}

//Adds given file to the inFiles cliplist
void MainContentComponent::importFile( File file )
	{
	inClips.addClipFromFile( file );
	procButton.setEnabled( true );
	}

//Opens a file
void MainContentComponent::openButtonClicked()
	{
	FileChooser chooser( "Select a Wave file to play", File::nonexistent, "*.wav" ); 

	if( chooser.browseForFileToOpen() )
		importFile( chooser.getResult() );
	}

//Processes input files with the supplied lua script
void MainContentComponent::procButtonClicked() 
	{
	std::function< void( std::vector< File > & ) > retrieveFiles = [&]( std::vector< File > & files )
		{
		for( auto & i : files )
			{
			outClips.addClipFromFile( i, true );
			}
		};

	std::vector<String> inFiles;
	inFiles.reserve( inClips.getNumItems() );
	for( int i = 0; i < inClips.getNumItems(); ++i )
		{
		inFiles.emplace_back( inClips.getItem( i )->getFile().getFullPathName().toStdString() );
		}
		
	threads.addThread( command.getText(), retrieveFiles, inFiles );
	}

//Called when files were dropped only the program from
void MainContentComponent::filesDropped( const StringArray & files, int x, int y )
	{
	for ( auto &&file : files )
		{ 
		importFile( File( file ) );
		}
	fileDragExit(files);
	}
