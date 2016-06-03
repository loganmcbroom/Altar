#include "AltarClip.h"

#include "AltarClipList.h"
#include <Windows.h>

Colour AltarClip::backgroundColour = Colour::fromHSV( 0, 0, .23, 1 );

AltarClip * AltarClip::active = nullptr;


AltarClip::AltarClip( File &_file
			, AudioFormatManager &_formatManager
			, AudioThumbnailCache &_thumbnailCache
			, AudioTransportSource &_transportSource
			, bool isOwner
			) 
	: Button( _file.getFullPathName() )
	, transportSource( _transportSource )
	, formatManager( _formatManager )
	//, audioFile( File::getCurrentWorkingDirectory().getFullPathName() + String( "/_altartemp_" ) + _file.getFileName()  )
	, audioFile( _file )
	, thumbnail( 512, _formatManager, _thumbnailCache )
	, busButton  ( "4", AltarButton::webdings  ) 
	, saveButton ( "<", AltarButton::wingdings )
	, printButton( "f", AltarButton::webdings  ) //unused
	, eraseButton( "r", AltarButton::webdings  )
	{
	_file.copyFileTo( audioFile.getFile() );
	if( isOwner ) 
		{
		if( ! _file.deleteFile() )
			Logger::writeToLog( String( "Couldn't delete file: " ) + _file.getFileName() );
		}

	thumbnail.addChangeListener( this );
	thumbnail.setSource( new FileInputSource( audioFile.getFile() ) );

	AudioFormatReader *reader = formatManager.createReaderFor( audioFile.getFile() );
	if( reader != nullptr )
		{
		std::unique_ptr<AudioFormatReaderSource> newSource( new AudioFormatReaderSource( reader, true ) );
		readerSource.swap( newSource );
		}
	//else throw;

	addAndMakeVisible( busButton   );
	addAndMakeVisible( saveButton  );
	//addAndMakeVisible( printButton );
	addAndMakeVisible( eraseButton );

	saveButton.addListener( this );
	busButton .addListener( this );

	setRadioGroupId( CLIP_GROUP_ID );
	//setClickingTogglesState( true );

	currentPosition.setFill (Colours::white.withAlpha (0.85f));
    addAndMakeVisible (currentPosition);
	}


AltarClip::~AltarClip()
	{
	if( this == active ) stopPressed();
	}

void AltarClip::resized()
	{
	size_t s = getHeight() / 2;
	busButton.setBounds  ( 0, 0, s, s );
	saveButton.setBounds ( 0, s, s, s );
	printButton.setBounds( s, 0, s, s );
	eraseButton.setBounds( s, s, s, s );
	}

const File &AltarClip::getFile() { return audioFile.getFile(); }

AudioThumbnail &AltarClip::getThumbnail() { return thumbnail; }

void AltarClip::paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown)
	{
	g.fillAll
		(
		getToggleState()?
			backgroundColour.withBrightness( .32 ) :
			( isMouseOverButton? backgroundColour.withBrightness( .27 ) : backgroundColour )
		);

	g.setColour( PALETTE_1 );
	juce::Rectangle<int> rect( getLocalBounds().withLeft( getHeight() ) );
	thumbnail.drawChannels( g, rect, 0, thumbnail.getTotalLength(), 1.0f );

	g.setColour( Colours::white );
	g.drawText( audioFile.getTargetFile().getFileName(), 
				juce::Rectangle<int>( getWidth() / 5.0 ,0, getWidth() * ( 4.0 / 5.0 ), getHeight() ).reduced( 3 ), 
				Justification::topRight, true );
	//g.drawText( String( static_cast<AltarClipList *>( getParentComponent() )->getIndex( this ) ),
	//				juce::Rectangle<int>( getHeight(), 0, getWidth() / 5.0, getHeight() ).reduced( 3 ),
	//				Justification::topLeft );
	}

void AltarClip::setButtonPlay()
	{
	busButton.setButtonText( "4" );
	busButton.font = AltarButton::webdings;
	}

void AltarClip::setButtonStop()
	{
	busButton.setButtonText( "n" );
	busButton.font = AltarButton::wingdings;
	}

void AltarClip::changeListenerCallback( ChangeBroadcaster* source )
	{
	if( source == &transportSource ) stopPressed();
	else if( source == &thumbnail ) repaint();
	}

void AltarClip::playPressed()
	{
	if( active != nullptr ) active->stopPressed();

	setToggleState( true, NotificationType::dontSendNotification );
	startTimer( 33 );
	active = this;
	
	setButtonStop();

	transportSource.setSource( readerSource.get(), 0, nullptr, readerSource->getAudioFormatReader()->sampleRate );
	transportSource.start();
	transportSource.addChangeListener( this );
	}

void AltarClip::stopPressed()
	{
	stopTimer();
	transportSource.setSource( nullptr );
	setToggleState( false, NotificationType::dontSendNotification );
	setButtonPlay();
	transportSource.removeChangeListener( this );
	active = nullptr;
	transportSource.stop();
	}

void AltarClip::buttonClicked( Button *button )
	{
	if( button == &busButton )
		{
		if( ! getToggleState() ) playPressed();
		else stopPressed();
		}

	else if( button == &saveButton )
		{
		File workingDirectory = audioFile.getFile().getParentDirectory();
		FileChooser chooser( "Save file as", workingDirectory, ".wav" );

		if( chooser.browseForFileToSave( true ) )
			{
			File choice = chooser.getResult();
			audioFile.getFile().copyFileTo( choice );
			}
		}
	}

void AltarClip::timerCallback()
	{
	currentPosition.setRectangle( juce::Rectangle<float>( 
		( transportSource.getCurrentPosition() *  float( getWidth() - getHeight() ) )
		/ ( readerSource->getTotalLength() / readerSource->getAudioFormatReader()->sampleRate ) + getHeight(), 
		0, getToggleState()? 2:0, getHeight() ) );
	}
