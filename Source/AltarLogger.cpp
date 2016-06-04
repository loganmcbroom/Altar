#include "AltarLogger.h"


AltarLogger::AltarLogger()
	: TextEditor( )
	{
	setReadOnly( true );
	setCaretVisible( false );
	setMultiLine( true, true );
	}

AltarLogger::~AltarLogger() 
	{
	}

void AltarLogger::logMessage( const String &message )
	{
	//insertTextAtCaret( Time::getCurrentTime().formatted( "(%I:%M:%S) " ) );
	insertTextAtCaret( message + "\n" );

	//Make sure we don't go too crazy with this thing... A long program could output a ridiculous amount of text.
	//If it gets too long cut out over half the text so we don't have to do it often
	int textDiff = getText().length() - 65536;
	if( textDiff >= 0 ) setText( getText().substring( textDiff + 65536 / 2, false ) );
	}

void AltarLogger::paint( Graphics & g )
	{
	TextEditor::paint( g );
	}