#pragma once

#include <vector>

//const StringArray commands = 
//	{ 
	//				Envelope
//	"stretch",			// 1 - 
//	"", 
//	"three"
	//				Filter
	//				Pitch
	//				Time
	//				Extend
	//				Grain
	//				PSOW
	//				Texture
	//				Rhythm
	//				Distort
//	 };

std::vector<std::string> altarProcess( const std::vector<std::string> &inputs, const std::string &program );
bool cdp( std::string command, const std::string & workingDir, std::vector<std::string> &outFiles );

/*	Lua Interface

Token replacement:
	$ -> generated .wav file name

//Call an arbitrary CDP module. 
cdp( module, arg1, arg2, ... )

*/