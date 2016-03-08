// =============================================================
//
// ProjectManager (LGN.cpp)
// Copyright Raffael Holz aka. LeGone. All rights reserved.
// http://www.legone.name
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License, version 3.0, as published by the
// Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
// =============================================================

#include <dlib/iosockstream.h>
#include <iostream>
#include "extension.h"

namespace LGN
{
	std::string get_most_recent_version()
	{
		try
		{
			dlib::iosockstream stream("bypass.legone.name:5000");

			stream << "get|entcontrol|version\r\n";

			std::string response;
			while (stream.peek() != EOF)
			{
				response += (unsigned char)stream.get();
			}

			return (response);
		}
		//catch (std::exception &e)
		catch (...)
		{
			// Just ignore the exception
			// smutils->LogMessage(myself, e.what());
		}

		return ("");
	}

	std::string get_ip_address()
	{
		try
		{
			dlib::iosockstream stream("bypass.legone.name:5000");

			stream << "myip\r\n";

			std::string response;
			while (stream.peek() != EOF)
			{
				response += (unsigned char)stream.get();
			}

			return (response);
		}
		//catch (std::exception &e)
		catch (...)
		{
			// Just ignore the exception
			// smutils->LogMessage(myself, e.what());
		}

		return ("");
	}
}
