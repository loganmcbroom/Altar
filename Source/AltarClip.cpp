#include "AltarClip.h"

#include "AltarClipList.h"
#include <Windows.h>

Colour AltarClip::backgroundColour = Colour::fromHSV( 0, 0, .23, 1 );

AltarClip * AltarClip::active = nullptr;


AltarClip::AltarClip( const File & _file
			, AudioFormatManager &_formatManager
			, AudioThumbnailCache &_thumbnailCache
			, AudioTransportSource &_transportSource
			, bool isOwner
			, const String & name
			) 
	: Button( name == String()? _file.getFileName() : name )
	, transportSource( _transportSource )
	, formatManager( _formatManager )
	, audioFile( _file )
	, thumbnail( 512, _formatManager, _thumbnailCache )
	, busButton  ( "4", AltarButton::webdings, 18 ) 
	, saveButton ( "<", AltarButton::wingdings, 18 )
	{
	_file.copyFileTo( audioFile.getFile() );
	if( isOwner ) 
		{
		if( ! _file.deleteFile() )
			Logger::writeToLog( String( "Couldn't delete file: " ) + _file.getFileName() );
		}

	thumbnail.addChangeListener( this );
	thumbnail.setSource( new FileInputSource( audioFile.getFile() ) );

	AudioFormatReader * reader = formatManager.createReaderFor( audioFile.getFile() );
	if( reader != nullptr )
		{
		std::unique_ptr<AudioFormatReaderSource> newSource( new AudioFormatReaderSource( reader, true ) );
		readerSource.swap( newSource );
		}

	addAndMakeVisible( busButton   );
	addAndMakeVisible( saveButton  );

	saveButton.addListener( this );
	busButton .addListener( this );

	setRadioGroupId( CLIP_GROUP_ID );

	currentPosition.setFill( Colours::white.withAlpha( 0.85f ) );
    addAndMakeVisible( currentPosition );
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
	}

void AltarClip::mouseDrag( const MouseEvent & event )
	{
	DragAndDropContainer * dragC = DragAndDropContainer::findParentDragContainerFor( this );
	if (! dragC->isDragAndDropActive() ) 
		{
		dragC->startDragging( "Clip" , this );
		}
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
	juce::Rectangle<int> rect( getLocalBounds().withLeft( getHeight() / 2 ) );
	thumbnail.drawChannels( g, rect.reduced( 2 ), 0, thumbnail.getTotalLength(), 1.0f );

	g.setColour( Colours::white );
	g.drawText( getName(), 
				juce::Rectangle<int>( getWidth() / 5.0 ,0, getWidth() * ( 4.0 / 5.0 ), getHeight() ).reduced( 3 ), 
				Justification::topRight, true );
	//g.drawText( String( static_cast<AltarClipList *>( getParentComponent() )->getIndex( this ) ),
	//				juce::Rectangle<int>( getHeight(), 0, getWidth() / 5.0, getHeight() ).reduced( 3 ),
	//				Justification::topLeft );
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
	
	busButton.setButtonText( "n" );
	busButton.font = AltarButton::wingdings;

	transportSource.setSource( readerSource.get(), 0, nullptr, readerSource->getAudioFormatReader()->sampleRate );
	transportSource.start();
	transportSource.addChangeListener( this );
	}

void AltarClip::stopPressed()
	{
	stopTimer();
	transportSource.setSource( nullptr );
	setToggleState( false, NotificationType::dontSendNotification );
	busButton.setButtonText( "4" );
	busButton.font = AltarButton::webdings;
	transportSource.removeChangeListener( this );
	active = nullptr;
	transportSource.stop();
	currentPosition.setRectangle( juce::Rectangle< float >(0,0,0,0) );
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
		setName( chooser.getResult().getFileName() );
		repaint();
		}
	}

void AltarClip::timerCallback()
	{
	currentPosition.setRectangle( juce::Rectangle<float>( 
		( transportSource.getCurrentPosition() * float( getWidth() - getHeight() / 2 ) )
		/ ( readerSource->getTotalLength() / readerSource->getAudioFormatReader()->sampleRate ) + getHeight() / 2, 
		0, getToggleState()? 2:0, getHeight() ) );
	}
