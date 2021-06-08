//
// system.h - system interface
//
// leccore library, part of the liblec library
// Copyright (c) 2019 Alec Musasa (alecmus at live dot com)
//
// Released under the CC-BY-NC 2.0 license. For full details see the file
// LICENSE.txt or go to https://github.com/alecmus/liblec/blob/master/LICENSE.md
//

#pragma once

#if defined(LECCORE_EXPORTS)
#include "leccore.h"
#else
#include <liblec/leccore.h>
#endif

#include <string>

namespace liblec {
	namespace leccore {
		/// <summary>Class for getting the path to known user folders.</summary>
		/// <remarks>If the path doesn't exist, an attempt will be made to create it.
		/// An empty string is returned if there is an error.
		/// </remarks>
		class leccore_api user_folder {
		public:
			/// <summary>Get the user's home directory.</summary>
			/// <returns>The home directory.</returns>
			static const std::string home();

			/// <summary>Get the user's document directory.</summary>
			/// <returns>The documents directory.</returns>
			static const std::string documents();

			/// <summary>Get the user's downloads directory.</summary>
			/// <returns>The downloads directory.</returns>
			static const std::string downloads();

			/// <summary>Get the user's desktop directory.</summary>
			/// <returns>The desktop directory.</returns>
			static const std::string desktop();

			/// <summary>Get the user's music directory.</summary>
			/// <returns>The music directory.</returns>
			static const std::string music();

			/// <summary>Get the user's videos directory.</summary>
			/// <returns>The videos directory.</returns>
			static const std::string videos();

			/// <summary>Get the user's pictures directory.</summary>
			/// <returns>The pictures directory.</returns>
			static const std::string pictures();

			/// <summary>Get the user's local appdata directory.</summary>
			/// <returns>The appdata directory.</returns>
			static const std::string local_appdata();

			/// <summary>Get the path to the folder designated for temporary files.</summary>
			/// <returns>The temporary files directory.</returns>
			static const std::string temp();
		};
	}
}
