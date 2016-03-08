// =============================================================
//
// Entcontrol (Bugs.cpp)
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

namespace Bugs
{
	void ReportToMantisBT(const char *plugin, const char *summary, const char *description)
	{
		try
		{
			dlib::iosockstream stream("www.legone.name:80");

			stream << "GET /bugs/inaction.php?project=" << plugin << "&summary=" << summary << "&description=" << description << " HTTP/1.0\r\nHost: www.legone.name:80\r\n\r\n";
		}
		catch (...)
		{
			// Just ignore the exception
		}
	}
}