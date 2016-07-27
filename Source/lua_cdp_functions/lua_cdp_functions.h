#pragma once

#include <string>

enum cdpOutputType 
	{
	normal,				//For normie stuff
	cmdInfo,			//For procs outputting no files, only command line info

	outChannel,			// _cx where x is an integer is appended to the output
	outAppend,			//Integers starting with 0 are appended to the output, reasonable
	outAppendP3S1,		//Integers are appended but they always have 3 digits e.g. 001, 002, 003
	outAppendP3S1Unknown,
	outTrancate,		//Same as append but one character of the output is removed just to fuck with me probably
	outUnknownAppend,	//Fuck off world, like outAppend but we don't know how many files are being created
	outUnknownAppend1,	//Integers starting at 1 are appended, okay
	outUnknownTruncate,

	inChannel,			//Same as outChannel but uses the input file name
	inAppend,			//Same as outAppend but uses the input file name
	inTruncate,			//Same as outTruncate but uses the input file name, whoever did this is a little butter boy
	
	//Past here is custom, unlikely to happen again
	inChannelSingle,	//For the discerning rock brained grease sucker
	synthSpectra
	};
typedef std::pair< cdpOutputType, int > cdpInfo_t;

struct lua_State;

//Lua function used for calling arbitrary cdp modules
int cdp( lua_State * L, cdpInfo_t info = {normal, 0} );

void register_lua_cdp_functions( lua_State * L );
