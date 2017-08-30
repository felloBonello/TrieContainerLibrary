#if !defined(GUARD_compiler_hpp20040413_)
#define GUARD_compiler_hpp20040413_

/** @file: compiler.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca
	@date 2004-04-13
	@version 11.0.0
	@note Target: Visual C++ 11.0

	@brief GatsLIB compiler configuration and extensions.
	*/

#include <cassert>

// Wide character macros
#define GATS_WIDEN2(x)	L ## x
#define GATS_WIDEN(x)	GATS_WIDEN2(x)

/** @def W__FILE__
	UNICODE version of __FILE__ macro. */
#define W__FILE__		GATS_WIDEN(__FILE__)
/** @def W__FUNCTION__
	UNICODE version of __FUNCTION__ macro. */
#define W__FUNCTION__	GATS_WIDEN(__FUNCTION__)


/**	@def VTEXT

	Macro that converts the string literal to Unicode if appropriate.
	*/
#if defined(_UNICODE)
#define VTEXT(txt) GATS_WIDEN(txt)
#else
#define VTEXT(txt) txt
#endif

#if defined(_UNICODE)
/** @def V__FILE__
	Macro that converts the __FILE__ macro to UNICODE if appropriate. */
#define V__FILE__		W__FILE__
/** @def V__FUNCTION__
	Macro that converts the __FUNCTION__ macro to UNICODE if appropriate. */
#define V__FUNCTION__	W__FUNCTION__
#else
#define V__FILE__		__FILE__
#define V__FUNCTION__	__FUNCTION__
#endif // _UNICODE



/** @def __GATS_BUILD_TYPE__
	Macro that represents the build type as a string. */
#if defined(_DEBUG) && defined(_DLL)
#if defined(_WIN64)
#define __GATS_BUILD_TYPE__ "Debug DLL Win64" 
#else
#define __GATS_BUILD_TYPE__ "Debug DLL Win32" 
#endif
#elif defined(_DEBUG) && !defined(_DLL)
#if defined(_WIN64)
#define __GATS_BUILD_TYPE__ "Debug static Win64"
#else
#define __GATS_BUILD_TYPE__ "Debug static Win32"
#endif
#elif !defined(_DEBUG) && defined(_DLL)
#if defined(_WIN64)
#define __GATS_BUILD_TYPE__ "Release DLL Win64"
#else
#define __GATS_BUILD_TYPE__ "Release DLL Win32"
#endif
#elif !defined(_DEBUG) && !defined(_DLL)
#if defined(_WIN64)
#define __GATS_BUILD_TYPE__ "Release static Win64"
#else
#define __GATS_BUILD_TYPE__ "Release static Win32"
#endif
#else
#error GATS compiler: unknown build type
#endif
/** @def W__GATS_BUILD_TYPE__
	Macro that represents the build type as a UNICODE string. */
#define W__GATS_BUILD_TYPE__ GATS_WIDEN(__GATS_BUILD_TYPE__)
/** @def V__GATS_BUILD_TYPE__
	Macro that represents the build type as an ASCII or UNICODE string as appropriate. */
#if defined(_UNICODE)
#define V__GATS_BUILD_TYPE__	W__GATS_BUILD_TYPE__
#else
#define V__GATS_BUILD_TYPE__	__GATS_BUILD_TYPE__
#endif





/**	@def GASSERT( cond, message )
	Adds a user defined message to the standard assert.
*/
#define GASSERT( cond, message ) assert( (cond) && message )



/*
	Conditional compilation macros
*/
/**	@def GATS_DEBUG_ONLY
	The following statement or block only appears in the debug version. */
#ifndef NDEBUG
#define GATS_DEBUG_ONLY if(1)
#else
#define GATS_DEBUG_ONLY if(0)
#endif


/*=============================================================

Revision History

Version 11.0.0: 2012-08-06
Validated for VC++ 11

Version 1.0.0: 2010-09-23
Validated for VC++ 10

Version 0.04: 2006-10-15
Removed all character macros.

Version 0.03: 2005-02-02
Added W__FILE__ and W__FUNCTION__

Version 0.02: 2005-01-22
Renamed: Assert() macro to GASSERT()

Version 0.01: 2004-04-13
Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/
#endif // GUARD_compiler_hpp20040413_
