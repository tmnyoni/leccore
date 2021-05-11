//
// leccore.h - leccore interface
//
// leccore library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#pragma once

#if defined(LECCORE_EXPORTS)
	#define leccore_api __declspec(dllexport)
#else
	#define leccore_api __declspec(dllimport)

	#if defined(_WIN64)
		#if defined(_DEBUG)
			#pragma comment(lib, "leccore64d.lib")
		#else
			#pragma comment(lib, "leccore64.lib")
		#endif
	#else
		#if defined(_DEBUG)
			#pragma comment(lib, "leccore32d.lib")
		#else
			#pragma comment(lib, "leccore32.lib")
		#endif
	#endif
#endif

#include <string>
#include <vector>

namespace liblec {
	namespace leccore {
		/// <summary>Get the version of the leccore library.</summary>
		/// <returns>Returns the version number as a string in the form
		/// "leccore 1.0.0 11 May 2021".</returns>
		std::string leccore_api version();
	}
}
