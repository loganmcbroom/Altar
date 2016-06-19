#include "lua_cdp_functions.h"

#include <vector>
#include <string>

#include "lua_cdp_utilities.h"
#include "../AltarThread.h"

using namespace std;

//Lua function used for calling arbitrary cdp modules
int cdp( lua_State * L, const std::string & info )
	{
	string exe, command;

	//Lambda function for getting and checking strings from the lua stack
	auto getLuaString = [ &L ]( int index, const char * error )
		{
		const char * s = lua_tostring( L, index );
		if( s == nullptr ) luaL_error( L, error );
		return string( s );
		};

	//Assemble the command. Note the lack of file path / ".exe" for the exe, it's added in the thread cdp method.
	command = getLuaString( 1, "Module name sent to cdp is not a valid string" )+ string( ".exe" );
	int argCount = lua_gettop( L ) - 1;
	//+2 accounting for lua indices starting at one and the first stack entry being the module name
	for( int i = 0; i < argCount; ++i )
		command += " " + getLuaString( i + 2, "Unknown argument passed to cdp is not a valid string" );
		

	lua_settop( L, 0 );
	vector<string> outFiles;
	if( ! static_cast<AltarThread *>( Thread::getCurrentThread() )->cdp( command, info, outFiles ) ) 
		luaL_error( L, "Exiting lua: error from CDP" );

	for( int i = 0; i < outFiles.size(); ++i )
		lua_pushstring( L, outFiles[i].c_str() );

	return outFiles.size();
	}

//Utility so cdp() can be registered with lua
static int lua_cdp( lua_State * L )
	{
	return cdp( L );
	}

#include "lua_cdp_functions_time_housekeep.h"
#include "lua_cdp_functions_time_modify.h"
#include "lua_cdp_functions_time_multichannel.h"

#include "lua_cdp_functions_spec_blur.h"
#include "lua_cdp_functions_spec_pvoc.h"

void register_lua_cdp_functions( lua_State * L )
	{
	//Main call
	lua_register( L, "cdp", lua_cdp );

//Time Domain
	//Distort
	//Envel
	//Envnu
	//Extend
	//Filter
	//Grain
	register_lua_cdp_functions_housekeep( L ); ///Incomplete
	register_lua_cdp_functions_modify( L ); ///Barely started, using a specific mode thing
	register_lua_cdp_functions_multichannel( L ); ///Barely started
	//M-C Toolkit
	//PSOW
	//Reverb
	//SndInfo
	//SFEdit
	//Submix
	//Synth
	//SysUtils
	//Tangent
	//Texture
	//Transit

//Spectral
	registerLuaCdpFunctions_blur( L );
	//Combine
	//Focus
	//Formants
	//Hilite
	//Morph
	//Oneform
	//Pitch
	//Pitchinfo
	register_lua_cdp_functions_PVOC( L ); //Extract untested
	//Repitch
	//Spec
	//Specnu
	//Specinfo
	//Strange
	//Stretch
	}