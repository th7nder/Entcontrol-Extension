// =============================================================
//
// Entcontrol (HTTP.cpp)
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

#include "HTTP.hpp"
#include "extension.h"
#include "Parser.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "Helper.hpp"

namespace HTTP
{
	std::string page404, wwwPath, lastFilePath, ip_address;

	std::string ReadFileHTML(std::string &filename, const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
	{
#if defined _WIN32
		std::ifstream file(filename);
#else
		std::ifstream file(filename.c_str());
#endif
		if (file.is_open())
		{
			std::string sOutput;
			std::string line;

			if (file.good())
			{
				getline (file, line);

				if (line.length() > 3)
				{
					if (line[0] == '{' && line[2] == '}')
					{
						// Admin-Flag-Check
						AdminId adminID = Helper::FindInGameAdminIDByClientIP(incoming.foreign_ip);

						if (adminID != INVALID_ADMIN_ID)
						{
							AdminFlag flag;
							if (adminsys->FindFlag(line[1], &flag))
							{
								if (!adminsys->GetAdminFlag(adminID, flag, Access_Effective))
									return ("You don´t have access to this file.");
							}
							else
							{
								return ("Flag-Access: Flag not found.");
							}
						}
						else
						{
							return ("You need to be ingame and an admin to have access to this file.");
						}

						// Skip admin-flag
						sOutput = &line[3];
						sOutput += "\r\n";
					}
					else
					{
						HTTP::Parser::Line(line, incoming, outgoing);
						sOutput += line + "\r\n";
					}
				}
				else
				{
					HTTP::Parser::Line(line, incoming, outgoing);
					sOutput += line + "\r\n";
				}
			}

			while (file.good())
			{
				getline (file, line);

				HTTP::Parser::Line(line, incoming, outgoing);

				sOutput += line + "\r\n";
			}
			file.close();

			return (sOutput);
		}
		else 
		{
			return (page404); 
		}		
	}

	std::string LoadCriticalFile(std::string filename)
	{
		std::string sOutput;
		std::string line;

#if defined _WIN32 || defined _WIN64
		std::ifstream file(wwwPath + filename);
#else
		std::ifstream file((wwwPath + filename).c_str());
#endif
		if (file.is_open())
		{
			while (file.good())
			{
				getline (file, line);
				sOutput += line;
			}
			file.close();
		}
		else
		{
			Helper::Log::Error(__FILE__, __FUNCTION__, __LINE__, std::string(filename) + " not found?!");
		}

		return (sOutput);
	}

	std::string ReadFilePlain(std::string filename)
	{
#if defined _WIN32 || defined _WIN64
		std::ifstream file(filename);
#else
		std::ifstream file(filename.c_str());
#endif
		if (file.is_open())
		{
			std::string sOutput;
			std::string line;

			while (file.good())
			{
				getline (file, line);
				sOutput += line + "<br/>";
			}
			file.close();

			return (sOutput);
		}
		else 
		{
			return (page404); 
		}
	}

	std::string jQuerySuccess(std::string sOutput)
	{
		sOutput = "<div class='ui-widget'><div class='ui-state-highlight ui-corner-all' style='margin-top: 20px; padding: 0 .7em;'><p><span class='ui-icon ui-icon-info' style='float: left; margin-right: .3em;'></span><strong>Success:</strong>"
				 + sOutput + "</p></div></div>";

		return (sOutput);
	}

	std::string jQueryAlert(std::string sOutput)
	{
		sOutput = "<div class='ui-widget'><div class='ui-state-error ui-corner-all' style='padding: 0 .7em;'><p><span class='ui-icon ui-icon-alert' style='float: left; margin-right: .3em;'></span><strong>Alert:</strong>"
				 + sOutput + "</p></div></div>";

		return (sOutput);
	}
	
	bool CheckLogin(const dlib::incoming_things &incoming, dlib::outgoing_things &outgoing, std::string &username)
	{
		std::string sIncomingQueryPassword = incoming.queries["pass"], sIncomingCookiePassword = incoming.cookies["pass"];
		std::string sIncomingQueryUser = incoming.queries["user"], sIncomingCookieUser = incoming.cookies["user"];

//#if defined _WIN32 || defined _WIN64
		if (!sIncomingQueryPassword.empty())
			Helper::GetCleanString(sIncomingQueryPassword);
		if (!sIncomingCookiePassword.empty())
			Helper::GetCleanString(sIncomingCookiePassword);
		if (!sIncomingQueryUser.empty())
			Helper::GetCleanString(sIncomingQueryUser);
		if (!sIncomingCookieUser.empty())
			Helper::GetCleanString(sIncomingCookieUser);
//#endif
		std::string user_Name, user_Pwd;

		if (sIncomingCookieUser.empty() || !sIncomingQueryUser.empty())
		{
			user_Name = sIncomingQueryUser;
		}
		else
		{
			user_Name = sIncomingCookieUser;
		}

		outgoing.cookies["user"] = user_Name;

		if (sIncomingCookiePassword.empty() || !sIncomingQueryPassword.empty())
		{
			user_Pwd = sIncomingQueryPassword;
		}
		else
		{
			user_Pwd = sIncomingCookiePassword;
		}

		std::string adminPwd = dlib::md5("asdf");
		if (adminPwd.empty() || adminPwd != dlib::md5(user_Pwd))
			return (false);

		outgoing.cookies["pass"] = user_Pwd;

		username = user_Name;

		return (true);
	}

	std::string RealFunction(std::string function, std::string username, const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
	{
		std::ostringstream sOutput;

		int positionOfExtendedCharacter = function.find('?');
		if (positionOfExtendedCharacter)
			function = function.substr(0, positionOfExtendedCharacter);

		if (function.size() >= 2)
		{
			if (function == "cmd")
			{
				sOutput << "Server #1 Bandar Desert!";
			}
			else
			{
				sOutput << "Unknown Function:" << function;
			}
		}

		return (sOutput.str());
	}

	std::string ReadDirectory(const std::string &pathAbsolute, std::string pathRelative)
	{
		std::string output;
		dlib::directory test(pathAbsolute);

		if (pathRelative.back() != '/')
			pathRelative += '/';

		std::vector<dlib::directory> dirs;
		std::vector<dlib::file> files;

		output = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html><head><title>Index of /" + test.name() + "</title></head><body>";
		output += "<h1>Index of " + test.name() + "</h1>";
		output += "<table><tr><th><img src=\"/icons/blank.gif\" alt=\"[ICO]\"></th><th><a href=\"?C=N;O=D\">Name</a></th><th><a href=\"?C=S;O=A\">Size</a></th></tr><tr><th colspan=\"5\"><hr></th></tr>";

		// get all directories and files in test
		test.get_dirs(dirs);
		test.get_files(files);

		// sort the files and directories
		std::sort(files.begin(), files.end());
		std::sort(dirs.begin(), dirs.end());

		// print all the subdirectories
		for (unsigned long i = 0; i < dirs.size(); ++i)
			output += "<tr><td valign=\"top\"><img src=\"/icons/dir.gif\" alt=\"[DIR]\"></td><td><a href=\"" + pathRelative + dirs[i].name() + "\">" + dirs[i].name() + "</a></td><td align=\"right\">&nbsp;</td></tr>";

		// print all the subfiles
		for (unsigned long i = 0; i < files.size(); ++i)
			output += "<tr><td valign=\"top\"><img src=\"/icons/file.gif\" alt=\"[FILE]\"></td><td><a href=\"" + pathRelative + files[i].name() + "\">" + files[i].name() + "</a></td><td align=\"right\">" + dlib::cast_to_string(files[i].size()) + " Bytes</td></tr>";

		output += "<tr><th colspan=\"5\"><hr></th></tr></table>";

		output += "<address>Entcontrol Server running at Port ";
		output += dlib::cast_to_string(GetPort());
		output += "</address></body></html>";

		return (output);
	}

	std::string ReadFile(std::string filename, const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
	{
		std::string filetype;
		size_t filetypePos = filename.find_last_of('.');

		// Directory?
		if (filetypePos == std::string::npos)
		{
			try
			{
				return (ReadDirectory(filename, incoming.path));
			}
			catch (...)
			{
			}
		}
		else
		{
			filetype = filename.substr(filetypePos+1);
		}

		lastFilePath = filename;

		// Todo: not the same if twice
		if (filetypePos == std::string::npos)
		{
			return (ReadFilePlain(filename));
		}
		else if (filetype == "jpg")
		{
			std::string sBinary;
#if defined _WIN32
			std::ifstream file(filename, std::ios::binary);
#else
			std::ifstream file(filename.c_str(), std::ios::binary);
#endif
			if (file.is_open())
			{
				outgoing.headers["Content-Type"] = "image/jpeg";
				outgoing.headers["Content-Length"] = file.tellg();

				char ch;
				while (file.get(ch), !file.eof())
				{
					sBinary += ch;
				}

				file.close();
				return (sBinary);
			}
		}
		else if (filetype == "gif")
		{
			std::string sBinary;
#if defined _WIN32
			std::ifstream file(filename, std::ios::binary);
#else
			std::ifstream file(filename.c_str(), std::ios::binary);
#endif
			if (file.is_open())
			{
				outgoing.headers["Content-Type"] = "image/gif";
				outgoing.headers["Content-Length"] = file.tellg();

				char ch;
				while (file.get(ch), !file.eof())
				{
					sBinary += ch;
				}

				file.close();
				return (sBinary);
			}
		}
		else if (filetype == "png")
		{
			std::string sBinary;
#if defined _WIN32
			std::ifstream file(filename, std::ios::binary);
#else
			std::ifstream file(filename.c_str(), std::ios::binary);
#endif
			if (file.is_open())
			{
				outgoing.headers["Content-Type"] = "image/png";
				outgoing.headers["Content-Length"] = file.tellg();

				char ch;
				while (file.get(ch), !file.eof())
				{
					sBinary += ch;
				}

				file.close();
				return (sBinary);
			}
		}
		else if (filetype == "html" || filetype == "htm")
		{
			return (ReadFileHTML(filename, incoming, outgoing));
		}
		else if (filetype == "css")
		{
			outgoing.headers["Content-Type"] = "text/css";
			return (ReadFileHTML(filename, incoming, outgoing));
		}
		else if (filetype == "js")
		{
			outgoing.headers["Content-Type"] = "text/javascript";
			return (ReadFileHTML(filename, incoming, outgoing));
		}
		else
		{
			return (ReadFilePlain(filename));
		}

		return (page404);
	}

	const std::string Webserver::on_request(const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
	{
		try
		{
			if (incoming.request_type == "GET" || incoming.request_type == "POST")
			{
				std::string sPath = incoming.path;
				if (sPath.length() > 2)
				{
					if (sPath.find("..") != std::string::npos)
						return ("This is not okay!");

					std::string username;
					if (sPath[1] == '!')
					{
						if (CheckLogin(incoming, outgoing, username) || true)
							return (RealFunction(&sPath[2], username, incoming, outgoing));
					}

					size_t extendinChar = sPath.find('?');
					if (extendinChar != std::string::npos)
						sPath = sPath.substr(0, extendinChar);

					return (ReadFile(wwwPath + sPath, incoming, outgoing));
				}
			}

			try
			{
				return (ReadDirectory(wwwPath, ""));
			}
			catch (...)
			{
				return (page404);
			}
		}
		catch (std::exception& e)
		{
			return (e.what());
		}
	}

	Webserver webserver;
	void webServerThread(void*) // web_server& the_server
	{
		try
		{
			webserver.start();
		}
		catch (dlib::socket_error& e)
		{
			Helper::Log::Error(__FILE__, __FUNCTION__, __LINE__, std::string("Socket error while starting server: ") + e.what());
		}
		catch (std::exception& e)
		{
			Helper::Log::Error(__FILE__, __FUNCTION__, __LINE__, std::string("Error while starting server: ") + e.what());
		}
	}

	void Start(const unsigned short port)
	{
		try
		{
			if (webserver.is_running())
			{
				// Port Changed?
				if (port != webserver.get_listening_port())
					Stop();
				else
					return;
			}

			webserver.set_listening_port(port); // boost::lexical_cast<unsigned char>(incoming.queries["level"])
			// Get Path to www
			char path[1024];
			g_pSM->BuildPath(SourceMod::Path_SM, path, PLATFORM_MAX_PATH, "configs/www/");
			wwwPath = path;

			// Load default html files
			page404 = LoadCriticalFile("404.html");

			// create a thread that will start the server.   The ref() here allows us to pass 
			// our_web_server into the threaded function by reference.
			//thread_function t(thread, dlib::ref(our_web_server));
			dlib::create_new_thread(webServerThread, 0);
		}
		catch (std::exception& e)
		{
			Helper::Log::Error(__FILE__, __FUNCTION__, __LINE__, e.what());
		}
	}

	void Stop()
	{
		try
		{
			// this will cause the server to shut down 
			webserver.clear();
		}
		catch (std::exception& e)
		{
			Helper::Log::Error(__FILE__, __FUNCTION__, __LINE__, e.what());
		}
	}

	void CreateForwards()
	{
		Parser::gForwardFunction = forwards->CreateForward("EC_OnWebserverCallFunction", ET_Hook, 4, NULL, Param_Cell, Param_String, Param_String, Param_String);
	}

	void ReleaseForwards()
	{
		forwards->ReleaseForward(Parser::gForwardFunction);
	}
}
