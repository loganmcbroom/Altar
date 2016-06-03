#pragma once

#include <Windows.h>
//#include "../JuceLibraryCode/JuceHeader.h"

HANDLE hChildProcess = NULL;
HANDLE hStdIn = NULL;
BOOL bRunThread = TRUE;

DWORD WINAPI GetAndSendInputThread(LPVOID lpvThreadParam)
{
	auto winErr = []( const String & loc )
		{  
		//Logger::writeToLog( String("Error at ") + loc + String( ": " ) + String( GetLastError() ) );
		return 0;
		};

    CHAR read_buff[256];
    DWORD nBytesRead,nBytesWrote;
    HANDLE hPipeWrite = (HANDLE)lpvThreadParam;

    // Get input from our console and send it to child through the pipe.
    while (bRunThread)
    {
        if(!ReadConsole(hStdIn,read_buff,1,&nBytesRead,NULL))
        winErr("ReadConsole");

        read_buff[nBytesRead] = '\0'; // Follow input with a NULL.

        if (!WriteFile(hPipeWrite,read_buff,nBytesRead,&nBytesWrote,NULL))
        {
        if (GetLastError() == ERROR_NO_DATA)
            break; // Pipe was closed (normal exit path).
        else
        winErr("WriteFile");
        }
    }

    return 1;
}

//Runs a command line process described by line. Logs output and error streams from child.
bool windowsCall( const char * line )
	{
	auto winErr = []( const String & loc )
		{  
		Logger::writeToLog( String("Error at ") + loc + String( ": " ) + String( GetLastError() ) );
		return false;
		};

	HANDLE hOutputReadTmp,hOutputRead,hOutputWrite;
    HANDLE hInputWriteTmp,hInputRead,hInputWrite;
    HANDLE hErrorWrite;
    HANDLE hThread;
    DWORD ThreadId;
	SECURITY_ATTRIBUTES sa;

	sa.nLength= sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

	if ( ! CreatePipe( &hOutputReadTmp, &hOutputWrite, &sa, 0 ) )
		winErr( "CreatePipe" );


	if ( ! DuplicateHandle( GetCurrentProcess(), hOutputWrite,
                            GetCurrentProcess(), &hErrorWrite, 0,
                           TRUE,DUPLICATE_SAME_ACCESS))
         winErr( "DuplicateHandle" );

	if (!CreatePipe(&hInputRead,&hInputWriteTmp,&sa,0))
         winErr("CreatePipe");

	if (!DuplicateHandle(GetCurrentProcess(),hOutputReadTmp,
                           GetCurrentProcess(),
                           &hOutputRead, // Address of new handle.
                           0,FALSE, // Make it uninheritable.
                           DUPLICATE_SAME_ACCESS))
         winErr("DupliateHandle");

	if ( ! DuplicateHandle( GetCurrentProcess(), hInputWriteTmp,
                           GetCurrentProcess(),
                           &hInputWrite, // Address of new handle.
                           0,FALSE, // Make it uninheritable.
                           DUPLICATE_SAME_ACCESS))
		winErr("DupliateHandle");


	if ( ! CloseHandle( hOutputReadTmp ) ) winErr( "CloseHandle" ); 
	if ( ! CloseHandle( hInputWriteTmp ) ) winErr( "CloseHandle" );

	if ( ( hStdIn = GetStdHandle( STD_INPUT_HANDLE ) ) == INVALID_HANDLE_VALUE )
         winErr( "GetStdHandle" );


	{ //PrepAndLaunchRedirectedChild
	PROCESS_INFORMATION pi; //This is what we get as an [out] parameter
	STARTUPINFO si; //This is an [in] parameter

	ZeroMemory( &si, sizeof( STARTUPINFO ) );
	si.cb = sizeof( STARTUPINFO );
	si.dwFlags = STARTF_USESTDHANDLES;
	//si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = hOutputWrite;
	si.hStdInput  = hInputRead;
	si.hStdError  = hErrorWrite;

	if( ! CreateProcess( NULL, const_cast<char *>( line ), NULL, NULL, true, 
		CREATE_NEW_CONSOLE, NULL, NULL, //set working dir, probably useful
		&si, &pi ) ) 
		winErr( "CreateProcess" );

	hChildProcess = pi.hProcess;
		
	if( ! CloseHandle( pi.hThread ) ) winErr( "CloseHandle" );
	}

	//=======================================
	if( ! CloseHandle( hOutputWrite ) ) winErr( "CloseHandle" );
	if( ! CloseHandle( hInputRead   ) ) winErr( "CloseHandle" );
	if( ! CloseHandle( hErrorWrite  ) ) winErr( "CloseHandle" );

	hThread = CreateThread(NULL,0,GetAndSendInputThread,
                              (LPVOID)hInputWrite,0,&ThreadId);
    if( hThread == NULL ) winErr("CreateThread");

	{//ReadandHandleOutput
	CHAR lpBuffer[256];
	DWORD nBytesRead;
	DWORD nCharsWritten;
	String output;

	while( true )
		{
		if ( ! ReadFile( hOutputRead, lpBuffer, sizeof( lpBuffer ), &nBytesRead, NULL ) || ! nBytesRead )
			{
			if( GetLastError() == ERROR_BROKEN_PIPE ) break; // pipe done - normal exit path.
			else winErr( "ReadFile" ); // Something bad happened.
			}

			
			// Display the character read on the screen.
			//if ( ! WriteConsole( GetStdHandle( STD_OUTPUT_HANDLE ), lpBuffer, nBytesRead, &nCharsWritten, NULL ) )
				//winErr("WriteConsole");
			output.append( String( lpBuffer, nBytesRead ), nBytesRead );
		}
	Logger::writeToLog( output );
	}
	



	if ( ! CloseHandle( hStdIn ) ) winErr( "CloseHandle" );

	bRunThread = FALSE;

	if( WaitForSingleObject( hThread, INFINITE ) == WAIT_FAILED ) winErr( "WaitForSingleObject" );

	if ( ! CloseHandle( hOutputRead  ) ) winErr("CloseHandle");
    if ( ! CloseHandle( hInputWrite  ) ) winErr("CloseHandle");

	return true;
	}