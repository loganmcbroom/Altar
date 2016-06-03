#include "MainComponent.h"

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
	, inClips( "inClips", formatManager, transportSource )
	, outClips( "outClips", formatManager, transportSource )
	{
	AltarButton::wingdings = &fontWingdings;
	AltarButton::webdings = &fontWebdings;

	inClips.clearButton.setFont( &fontWebdings );
	outClips.clearButton.setFont( &fontWebdings );

	addAndMakeVisible( log );
	Logger::setCurrentLogger( &log );
	Logger::writeToLog( "Logger Active" );

	addAndMakeVisible( &openButton );
	addAndMakeVisible( &procButton );
	addAndMakeVisible( &inClips    );
	addAndMakeVisible( &outClips   );
	addAndMakeVisible( &command    );

	openButton.addListener( this );
	procButton.addListener( this );

	command.setMultiLine( true, false );
	command.setReturnKeyStartsNewLine( true );
	command.setFont( fontRoboto );

	#ifdef DEBUG
	command.setText( "Debug/Data/Altar.lua" );
	#else
	command.setText( "Altar.lua" );
	#endif

	setSize( 1000, 700 );

	formatManager.registerBasicFormats();


	setAudioChannels(0, 2);
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

//Paint
void MainContentComponent::paint( Graphics& g )
	{
    g.fillAll (BACKGROUND_COLOUR);

	g.setColour( Colours::white );
	g.drawLine( getWidth() / 2, UNIT + MARGIN * 2,
				getWidth() / 2, getHeight() - MARGIN - ( UNIT * 2 + MARGIN * 2 ) );			

	}

//Resized
void MainContentComponent::resized()
	{
	openButton.setBounds(MARGIN,			MARGIN,	UNIT, UNIT);
	procButton.setBounds(MARGIN * 2 + UNIT, MARGIN, UNIT, UNIT);

	inClips.setBounds( 
		MARGIN, 
		MARGIN * 2 + UNIT, 
		getWidth() / 2 - 2 * MARGIN, 
		getHeight() - ( UNIT + MARGIN * 3 ) - ( UNIT * 4 + MARGIN * 4 ) );
	outClips.setBounds( 
		getWidth() / 2 + MARGIN, 
		MARGIN * 2 + UNIT, 
		getWidth() / 2 - 2 * MARGIN, 
		getHeight() - ( UNIT + MARGIN * 3 ) - ( UNIT * 4 + MARGIN * 4 ) );

	command.setBounds( MARGIN * 3 + UNIT * 2, MARGIN, getWidth() - ( MARGIN * 4 + UNIT * 2 ), UNIT );

	Rectangle<int> errorRect( 
		MARGIN, getHeight() - ( UNIT * 4 + MARGIN * 4 ), 
		getWidth() - MARGIN * 2, UNIT * 4 + MARGIN *3 );

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
	if( AltarClip::active != nullptr ) AltarClip::active->stopPressed();
	openButton.setEnabled( false );
	procButton.setEnabled( false );
	thinking = true;

	std::vector<std::string> files;
	files.reserve( inClips.clips.size() );
	for( auto &&i : inClips.clips )
		{
		files.emplace_back( i->getFile().getFullPathName().toStdString() );
		}
		
	//Process that shit
	Logger::writeToLog( "\n\n\n[PROCESSING]" );
	std::vector<std::string> processed = altarProcess( files, command.getText().toStdString() );
	Logger::writeToLog( "[PROCESSING COMPLETE]" );

	for( int i=0; i < processed.size(); ++i )
		{
		outClips.addClipFromFile( File( String( processed[i] ) ), true );
		}

	thinking = false;
	openButton.setEnabled( true );
	procButton.setEnabled( true );
	setMouseCursor( MouseCursor::NormalCursor );
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
