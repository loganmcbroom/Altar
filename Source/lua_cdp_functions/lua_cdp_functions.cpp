#include "lua_cdp_functions.h"

#include <vector>
#include <string>
#include <fstream>

#include "../AltarThread.h"
#include "lua_cdp_utilities.h"

using namespace std;

//Lua function used for calling arbitrary cdp modules
int cdp( lua_State * L,  cdpInfo_t info )
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
	command = getLuaString( 1, "Module name sent to cdp is not a valid string" ) + string( ".exe" );
	int argCount = lua_gettop( L ) - 1;
	//+2 accounting for lua indices starting at one and the first stack entry being the module name
	for( int i = 0; i < argCount; ++i )
		command += " " + getLuaString( i + 2, "Unknown argument passed to cdp is not a valid string" );
		
	lua_settop( L, 0 );
	vector<string> outFiles;

	if( ! static_cast<AltarThread *>( Thread::getCurrentThread() )->cdp( command, info, outFiles ) ) 
		return luaL_error( L, "Exiting lua: error from CDP" );

	for( auto i : outFiles )
		{
		std::ifstream testFile( i.substr( 1, i.size() - 2 ) );
		if( ! testFile.good() )
			return luaL_error( L, ( "Something went wrong! The file " 
				+ i + " should have been created but it wasn't." ).c_str() );
		lua_pushstring( L, i.c_str() );
		}
	return outFiles.size();
	}

#include "lua_cdp_functions_time_distort.h"
#include "lua_cdp_functions_time_envel.h"
#include "lua_cdp_functions_time_extend.h"
#include "lua_cdp_functions_time_filter.h"
#include "lua_cdp_functions_time_grain.h"
#include "lua_cdp_functions_time_housekeep.h"
#include "lua_cdp_functions_time_modify.h"
#include "lua_cdp_functions_time_multichannel.h"
#include "lua_cdp_functions_time_psow.h"
#include "lua_cdp_functions_time_reverb.h"
#include "lua_cdp_functions_time_sfedit.h"
#include "lua_cdp_functions_time_sndinfo.h"
#include "lua_cdp_functions_time_submix.h"
#include "lua_cdp_functions_time_synth.h"
#include "lua_cdp_functions_time_sysutils.h"
#include "lua_cdp_functions_time_texture.h"

#include "lua_cdp_functions_spec_blur.h"
#include "lua_cdp_functions_spec_combine.h"
#include "lua_cdp_functions_spec_focus.h"
#include "lua_cdp_functions_spec_formants.h"
#include "lua_cdp_functions_spec_hilite.h"
#include "lua_cdp_functions_spec_morph.h"
#include "lua_cdp_functions_spec_oneform.h"
#include "lua_cdp_functions_spec_pitch.h"
#include "lua_cdp_functions_spec_pvoc.h"
#include "lua_cdp_functions_spec_repitch.h"
#include "lua_cdp_functions_spec_spec.h"
#include "lua_cdp_functions_spec_strange.h"
#include "lua_cdp_functions_spec_stretch.h"

void register_lua_cdp_functions( lua_State * L )
	{
//Time Domain
	register_lua_cdp_functions_distort		( L );	//Untested
	register_lua_cdp_functions_envel		( L );	//Untested										
	register_lua_cdp_functions_extend		( L );	//Untested
	register_lua_cdp_functions_filter		( L );	//Untested
	register_lua_cdp_functions_grain		( L );	//Untested
	register_lua_cdp_functions_housekeep	( L );	//Untested
	register_lua_cdp_functions_modify		( L );	//Untested
	register_lua_cdp_functions_multichannel	( L );	///Incomplete, inverted flags
	register_lua_cdp_functions_psow			( L );	//Untested
	register_lua_cdp_functions_reverb		( L );	///Incomplete, inverted flags
	register_lua_cdp_functions_sndinfo		( L );	//Untested
	register_lua_cdp_functions_sfedit		( L );	//Untested
	register_lua_cdp_functions_submix		( L );	//Untested
	register_lua_cdp_functions_synth		( L );	//Untested
	register_lua_cdp_functions_sysutils		( L );	///Incomplete, inverted flags
	register_lua_cdp_functions_texture		( L );	//Untested

//Spectral Domain
	register_lua_cdp_functions_blur			( L );	//Untested
	register_lua_cdp_functions_combine		( L );	//Untested
	register_lua_cdp_functions_focus		( L );	//Untested
	register_lua_cdp_functions_formants		( L );	//Untested
	register_lua_cdp_functions_hilite		( L );	//Untested
	register_lua_cdp_functions_morph		( L );	//Untested
	register_lua_cdp_functions_oneform		( L );	//Untested
	register_lua_cdp_functions_pitch		( L );	///Incomplete, bad flags
	register_lua_cdp_functions_PVOC			( L );	//Extract untested
	register_lua_cdp_functions_repitch		( L );	//Extra untested, type outputs might not work on anything
	register_lua_cdp_functions_spec			( L );	///Incomplete, bad flags
	register_lua_cdp_functions_strange		( L );	///Incomplete, bad flags
	register_lua_cdp_functions_stretch		( L );	//Untested
	}