#pragma once

#include <functional>
#include <string>
#include <tuple>
#include "lua.hpp"
#include "lua_cdp_functions.h"

//Try to not judge me for this file, writing lua mappings for 800 processes will take its toll on any mind

//Get the number of channels in the file s
unsigned int getNumChannels( const char * file );

//Push s to nth position on the stack
void inline lua_pushto( lua_State * L, const char * s, int n );
void lua_pushpairs( lua_State * L, std::initializer_list< std::pair< const char *, int > > pairs );

//Used by the macro below to define functions which can process any number of input files
int lua_multi_proc( lua_State * L, int params, int flags, std::function< int( lua_State * ) > f, int groupSize = 1 );
int lua_nonlinear_proc( lua_State * L, int params, int flags, std::function<int( lua_State*, int )> f );

#define WAV_TYPE "$.wav"
#define TXT_TYPE "$.txt"
#define MMX_TYPE "$.mmx"
#define BIN_TYPE "$"
#define FOR_TYPE "$.for"
#define ENV_TYPE "$.env"
#define ANA_TYPE "$.ana"
#define FRQ_TYPE "$.frq"
#define BRK_TYPE "$.brk"


#define LUA_CDP_MULTI( name, defParams, optionalParams, func ) int name( lua_State * L ) \
	{ return lua_multi_proc( L, defParams, optionalParams, []( lua_State * L ){ func } ); }

#define LINEAR_MULTI_NPROC_TYPE_FUNC( name, module, process, params, flags, type, groupSize ) \
int name( lua_State * L ) \
	{ \
	return lua_multi_proc( L, params, flags, []( lua_State * L ) \
		{ \
		lua_pushpairs( L, { {module, 1}, {process, 2}, {type, 3 + groupSize} } ); \
		return cdp( L ); \
		}, groupSize ); \
	}

#define LINEAR_MULTI_NPROC_TYPE_FUNC_2( module, process, params, flags, type, groupSize ) \
int lua_cdp_ ## module ## _ ## process( lua_State * L ) \
	{ \
	return lua_multi_proc( L, params, flags, []( lua_State * L ) \
		{ \
		lua_pushpairs( L, { {#module, 1}, {#process, 2}, {type, 3 + groupSize} } ); \
		return cdp( L ); \
		}, groupSize ); \
	}

#define LINEAR_MULTI_PROC_FUNC( a, b, c, d, e ) LINEAR_MULTI_NPROC_TYPE_FUNC( a,b,c,d,e, WAV_TYPE, 1 )
#define LINEAR_MULTI_PROC_FUNC_2( module, process, params, flags ) \
	LINEAR_MULTI_NPROC_TYPE_FUNC_2( module, process, params, flags, WAV_TYPE, 1 )

#define NONLINEAR_PROC_FUNC_TYPE( module, process, params, flags, type ) \
int lua_cdp_ ## module ## _ ## process( lua_State * L )\
	{\
	return lua_nonlinear_proc( L, params, flags, []( lua_State * L, int gsize )	\
	{ lua_pushpairs(L, { {#module, 1}, {#process, 2}, {type, 3 + gsize} }); return cdp(L);} );\
	}
#define NONLINEAR_PROC_FUNC( a,b,c,d ) NONLINEAR_PROC_FUNC_TYPE( a,b,c,d, WAV_TYPE )

#define INFO_PROC_FUNC( module, proc, params, flags, groupSize ) int lua_cdp_ ## module ## _ ## proc( lua_State * L ) \
	{ \
	for( int i = 0; i < groupSize; ++i )\
		lua_insert( L, 1 );\
	lua_pushpairs( L, { {#module, 1}, {#proc, 2} } );\
	return cdp( L, {cmdInfo, 0} );\
	}


#define LUA_CDP_MODAL_MULTI( name, cases ) int name( lua_State * L ) \
	{ \
	int mode = lua_tonumber( L, 1 ); \
	lua_remove( L, 1 ); \
	switch( mode ) \
		{ \
		cases \
		default: return luaL_error( L, ( std::string( #name ) + " has no mode " + std::to_string( mode ) ).c_str() ); \
		} \
	}

//=============================================================
#define LINEAR_MULTI_NPROC_TYPE( module, processAndMode, params, flags, type, groupSize ) \
	return lua_multi_proc( L, params, flags, []( lua_State * L )\
		{ \
		lua_pushpairs( L, { {module, 1}, {processAndMode, 2}, {type, 3 + groupSize} } ); \
		return cdp( L ); \
		}, \
		groupSize )

#define LINEAR_MULTI_NPROC_TYPE_2( mode, module, process, params, flags, type, groupSize ) \
	case mode: return lua_multi_proc( L, params, flags, []( lua_State * L )\
		{ \
		lua_pushpairs( L, { {#module, 1}, {#process" "#mode, 2}, {type, 3 + groupSize} } ); \
		return cdp( L ); \
		}, \
		groupSize )

#define LINEAR_MULTI_PROC_TYPE( a, b, c, d, e )		LINEAR_MULTI_NPROC_TYPE( a, b, c, d, e, 1 )
#define LINEAR_MULTI_NPROC( a, b, c, d, e )			LINEAR_MULTI_NPROC_TYPE( a, b, c, d, WAV_TYPE, e )
#define LINEAR_MULTI_PROC( a, b, c, d )				LINEAR_MULTI_NPROC_TYPE( a, b, c, d, WAV_TYPE, 1 )

#define NONLINEAR_PROC( module, processAndMode, params, flags, type )		\
	return lua_nonlinear_proc( L, params, flags, []( lua_State * L, int gsize )		\
	{ lua_pushpairs(L, { {#module, 1}, {#processAndMode, 2}, {type, 3 + gsize} }); return cdp(L);} );

#define LINEAR_MULTI_INFO_PROC( module, procAndMode, params, flags ) return lua_multi_proc( L, params, flags, []( lua_State * L )\
		{\
		lua_pushpairs( L, { {module, 1}, {procAndMode, 2} } );\
		return cdp( L, {cmdInfo, 0} );\
		});
//=============================================================

#define LUA_CDP_UNSUPPORTED( name ) \
static int name( lua_State * L ) \
	{ \
	return luaL_error( L, ( std::string(#name) + " is unsupported until requested" ).c_str() ); \
	}

#define LUA_CDP_UNSUPPORTED_CONST( name ) \
static int name( lua_State * L ) \
	{ \
	return luaL_error( L, ( std::string(#name) + " is permanently unsupported" ).c_str() ); \
	}

#define LUA_ERROR_FUNC( mode_proc, err ) int lua_cdp_ ## mode_proc( lua_State * L ) { return luaL_error( L, err ); }