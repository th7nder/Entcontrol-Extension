// =============================================================
//
// Entcontrol (HTTP.hpp)
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

#undef COMPILE_TIME_ASSERT
#include <dlib/server.h>
#include <dlib/md5.h>
#include <dlib/dir_nav.h>

namespace HTTP
{
	class Webserver : public dlib::server::http_1a_c
	{
		const std::string on_request(const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing);
	};

	extern Webserver webserver;
	extern std::string ip_address;

	extern std::string lastFilePath;
	std::string ReadFile(std::string filename, const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing);
	void Start(unsigned short port);
	void Stop();
	void CreateForwards();
	void ReleaseForwards();

	inline int GetPort()
	{
		return (webserver.get_listening_port());
	}

	inline const char *GetIP()
	{
		// webserver.get_listening_ip() is wrong!
		// we need to have our own ip-string
		return (ip_address.c_str());
	}

	inline void SetIP(std::string &ip)
	{
		ip_address = ip;
	}
}
